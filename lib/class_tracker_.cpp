#include "class_tracker_.h"


using namespace std;
using namespace cv;

static double GetIOU(Rect_<float> bb_test, Rect_<float> bb_gt)
{
	float in = (bb_test & bb_gt).area();
	float un = bb_test.area() + bb_gt.area() - in;

	if (un < DBL_EPSILON)
		return 0;

	return (double)(in / un);
}

_Tracker::_Tracker() 
{
	_frame_count = 0;
	KalmanTracker::kf_count = 0;

}
_Tracker::~_Tracker() 
{
   
}

bool _Tracker::run(const std::vector<cv::Rect> &rects_, 
             std::vector<TrackedBox> &rects_tracked_)
{
	//
	if (_frame_count < 100)
	{
		_frame_count++;
	}

    // 
    vector<TrackingBox> detFrameData;

    for (int i = 0; i < rects_.size(); i++)
    {
        TrackingBox tb;
        float tpx = rects_[i].tl().x;
        float tpy = rects_[i].tl().y;
        float tpw = rects_[i].width;
        float tph = rects_[i].height;
        tb.box = Rect_<float>(Point_<float>(tpx, tpy), Point_<float>(tpx + tpw, tpy + tph));
		detFrameData.push_back(tb);
    }
    
	//
	if (_trackers.size() == 0) // the first frame met
	{
		// initialize kalman trackers using first detections.
		for (unsigned int i = 0; i < detFrameData.size(); i++)
		{
			KalmanTracker trk = KalmanTracker(detFrameData[i].box);
			_trackers.push_back(trk);
		}

		// output
		for (int i = 0; i < rects_.size(); i++)
		{
			TrackedBox rect_tracked;
			rect_tracked.id = i+1;
			rect_tracked.rect = rects_[i];
			rects_tracked_.push_back(rect_tracked);
		}
		
		return true;
	}

	// get predicted locations from existing trackers.
	vector<Rect_<float> > predictedBoxes;
	for (auto it = _trackers.begin(); it != _trackers.end();)
	{
		Rect_<float> pBox = (*it).predict();
		if (pBox.x >= 0 && pBox.y >= 0)
		{
			predictedBoxes.push_back(pBox);
			it++;
		}
		else
		{
			it = _trackers.erase(it);
		}
	}

	// associate detections to tracked object
	unsigned int trkNum = predictedBoxes.size();
	unsigned int detNum = detFrameData.size();
	vector<vector<double> > iouMatrix;
	iouMatrix.resize(trkNum, vector<double>(detNum, 0));
	for (unsigned int i = 0; i < trkNum; i++) // compute iou matrix as a distance matrix
	{
		for (unsigned int j = 0; j < detNum; j++)
		{
			// use 1-iou because the hungarian algorithm computes a minimum-cost assignment.
			iouMatrix[i][j] = 1 - GetIOU(predictedBoxes[i], detFrameData[j].box);
		}
	}

	// solve the assignment problem using hungarian algorithm
	HungarianAlgorithm HungAlgo;
	vector<int> assignment;
	HungAlgo.Solve(iouMatrix, assignment);

	// find matches, unmatched_detections and unmatched_predictions
	set<int> unmatchedDetections;
	set<int> unmatchedTrajectories;
	set<int> allItems;
	set<int> matchedItems;

	if (detNum > trkNum) //	there are unmatched detections
	{
		for (unsigned int n = 0; n < detNum; n++)
			allItems.insert(n);

		for (unsigned int i = 0; i < trkNum; ++i)
			matchedItems.insert(assignment[i]);

		set_difference(allItems.begin(), allItems.end(),
			matchedItems.begin(), matchedItems.end(),
			insert_iterator<set<int>>(unmatchedDetections, unmatchedDetections.begin()));
	}
	else if (detNum < trkNum) // there are unmatched trajectory/predictions
	{
		for (unsigned int i = 0; i < trkNum; ++i)
			if (assignment[i] == -1) // unassigned label will be set as -1 in the assignment algorithm
				unmatchedTrajectories.insert(i);
	}

	// filter out matched with low IOU
	double iouThreshold = 0.3;

	vector<cv::Point> matchedPairs;
	for (unsigned int i = 0; i < trkNum; ++i)
	{
		if (assignment[i] == -1) // pass over invalid values
			continue;
		if (1 - iouMatrix[i][assignment[i]] < iouThreshold)
		{
			unmatchedTrajectories.insert(i);
			unmatchedDetections.insert(assignment[i]);
		}
		else
			matchedPairs.push_back(cv::Point(i, assignment[i]));
	}

	// update matched trackers with assigned detections.
	// each prediction is corresponding to a tracker
	int detIdx, trkIdx;
	for (unsigned int i = 0; i < matchedPairs.size(); i++)
	{
		trkIdx = matchedPairs[i].x;
		detIdx = matchedPairs[i].y;
		_trackers[trkIdx].update(detFrameData[detIdx].box);
	}

	// create and initialise new trackers for unmatched detections
	for (auto umd : unmatchedDetections)
	{
		KalmanTracker tracker = KalmanTracker(detFrameData[umd].box);
		_trackers.push_back(tracker);
	}

	// get trackers' output
	int min_hits = 3;

	vector<TrackingBox> frameTrackingResult;
	for (auto it = _trackers.begin(); it != _trackers.end();)
	{
		if (((*it).m_time_since_update < 1) &&
			((*it).m_hit_streak >= min_hits || _frame_count <= min_hits))
		{
			TrackingBox res;
			res.box = (*it).get_state();
			res.id = (*it).m_id + 1;
			res.frame = _frame_count;
			frameTrackingResult.push_back(res);
			it++;
		}
		else
			it++;

		// remove dead tracklet
		int max_age = 1;
		if (it != _trackers.end() && (*it).m_time_since_update > max_age)
			it = _trackers.erase(it);
	}
    
	//
	for (int i = 0; i < frameTrackingResult.size(); i++)
	{
		TrackedBox rect_tracked;
		rect_tracked.id = frameTrackingResult[i].id;
		int x = frameTrackingResult[i].box.x;
		int y = frameTrackingResult[i].box.y;
		int width = frameTrackingResult[i].box.width;
		int height = frameTrackingResult[i].box.height;
		rect_tracked.rect = cv::Rect(x, y, width, height);
		rects_tracked_.push_back(rect_tracked);
	}

	return true;
}

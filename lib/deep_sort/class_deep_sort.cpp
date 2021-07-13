#include "class_deep_sort.h"


static float max_cosine_distance = 0.2;
static int nn_budget = 100;


DeepSort::DeepSort() 
{
	_tracker = new tracker(max_cosine_distance, nn_budget);
}

DeepSort::~DeepSort() 
{
   if (_tracker)
   {
	   delete _tracker;
	   _tracker = nullptr;
   }
   
}

bool DeepSort::run(const std::vector<cv::Rect> &rects_, 
             	   const std::vector<cv::Mat> &features_,
                   std::vector<TrackedBox> &rects_tracked_)
{
	//
	DETECTIONS detections;
	cvt_to_detections(rects_, features_, detections);

	//
	_tracker->predict();
	_tracker->update(detections);

	std::vector<RESULT_DATA> result;
	for(Track& track : _tracker->tracks)
	{
		if(!track.is_confirmed() || track.time_since_update > 1) 
		{
			continue;
		}
		result.push_back(std::make_pair(track.track_id, track.to_tlwh()));
	}

	for(unsigned int k = 0; k < result.size(); k++) 
	{
		TrackedBox track_box;

		DETECTBOX tmp = result[k].second;
		track_box.rect = cv::Rect(tmp(0), tmp(1), tmp(2), tmp(3));
		track_box.id = result[k].first;

		rects_tracked_.push_back(track_box);
	}

	return true;
}

void DeepSort::cvt_to_detections(const std::vector<cv::Rect> &rects_, 
                                 const std::vector<cv::Mat> &features_, 
                                 DETECTIONS &detections_)
{
	for (int i = 0; i < rects_.size(); i++)
	{
		DETECTION_ROW detection;

		//
		int x = rects_[i].tl().x;
		int y = rects_[i].tl().y;
		int w = rects_[i].width;
		int h = rects_[i].height;
		detection.tlwh = DETECTBOX(x, y, w, h);

		//
		FEATURE feature;
		for (int j = 0; j < FEATURE_NUM; j++)
		{
			feature[j] = features_[i].at<float>(j, 0);
		}
		detection.feature = feature;

		//
		detections_.push_back(detection);
	}
}

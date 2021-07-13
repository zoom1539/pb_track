#include "class_tracker_.h"

_Tracker::_Tracker() 
{
}
_Tracker::~_Tracker() 
{
   
}

bool _Tracker::run(const std::vector<cv::Rect> &rects_, 
             std::vector<TrackedBox> &rects_tracked_)
{
	return _sort.run(rects_, rects_tracked_);
}

bool _Tracker::run(const std::vector<cv::Rect> &rects_, 
                   const std::vector<cv::Mat> &features_,
                   std::vector<TrackedBox> &rects_tracked_)
{
    return _deep_sort.run(rects_, features_, rects_tracked_);
}
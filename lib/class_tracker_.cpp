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

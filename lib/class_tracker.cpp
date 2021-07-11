#include "class_tracker.h"
#include "class_tracker_.h"

class Tracker::Impl
{
public:
    _Tracker _tracker;
};

Tracker::Tracker() : _impl(new Tracker::Impl())
{
}

Tracker::~Tracker()
{
    delete _impl;
    _impl = NULL;
}

bool Tracker::run(const std::vector<cv::Rect> &rects_, 
             std::vector<TrackedBox> &rects_tracked_)
{
    return _impl->_tracker.run(rects_, rects_tracked_);
}


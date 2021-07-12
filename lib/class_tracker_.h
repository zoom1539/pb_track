#pragma once

// std
#include <opencv2/opencv.hpp>
#include "class_tracker.h"
#include "class_sort.h"

class _Tracker
{
public:
    _Tracker();
    ~_Tracker();

public:
    // sort
    bool run(const std::vector<cv::Rect> &rects_, 
             std::vector<TrackedBox> &rects_tracked_);
    

private:
    Sort _sort;

};

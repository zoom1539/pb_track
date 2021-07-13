#pragma once

// std
#include <opencv2/opencv.hpp>
#include "class_tracker.h"
#include "class_sort.h"
#include "class_deep_sort.h"

class _Tracker
{
public:
    _Tracker();
    ~_Tracker();

public:
    // sort
    bool run(const std::vector<cv::Rect> &rects_, 
             std::vector<TrackedBox> &rects_tracked_);
    
    // deep sort
    bool run(const std::vector<cv::Rect> &rects_, 
             const std::vector<cv::Mat> &features_,
             std::vector<TrackedBox> &rects_tracked_);
    

private:
    Sort _sort;
    DeepSort _deep_sort;

};

#pragma once

// std
#include <opencv2/opencv.hpp>
#include "class_tracker.h"
#include "tracking/tracker.h"
#include "dataType.h"

// IMPORTANT: change Mahalanobis_threshold in linear_assignment.cpp for different applications
class DeepSort
{
public:
    DeepSort();
    ~DeepSort();

public:
    // deep sort
    bool run(const std::vector<cv::Rect> &rects_, 
             const std::vector<cv::Mat> &features_,
             std::vector<TrackedBox> &rects_tracked_);
    

private:
    void cvt_to_detections(const std::vector<cv::Rect> &rects_, 
                           const std::vector<cv::Mat> &features_, 
                           DETECTIONS &detections_);

private:
    tracker *_tracker;
    

};

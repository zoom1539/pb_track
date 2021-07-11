#pragma once

// std
#include <opencv2/opencv.hpp>
#include "class_tracker.h"
#include "Hungarian.h"
#include "KalmanTracker.h"

typedef struct TrackingBox
{
	int frame;
	int id;
	Rect_<float> box;
}TrackingBox;


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
    int _frame_count;
	std::vector<KalmanTracker> _trackers;

};

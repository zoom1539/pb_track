#include "class_tracker.h"
int main()
{
	Tracker tracker;

	{
		std::vector<cv::Rect> rects;
		{
			cv::Rect rect(10,10,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(250,250,100, 200);
			rects.push_back(rect);
		}
		
		std::vector<TrackedBox> rects_tracked;
		cv::Size img_size(1024, 760); //(width, height) 
		bool is_track = tracker.run(rects, img_size, rects_tracked);
		for (int i = 0; i < rects_tracked.size(); i++)
		{
			std::cout << rects_tracked[i].id << "," << rects_tracked[i].rect << std::endl;
		}
		std::cout << "-------------" << std::endl;

	}
	{
		std::vector<cv::Rect> rects;
		{
			cv::Rect rect(10,10,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(250,250,100, 200);
			rects.push_back(rect);
		}
		
		std::vector<TrackedBox> rects_tracked;
		cv::Size img_size(1024, 760); //(width, height) 
		bool is_track = tracker.run(rects, img_size, rects_tracked);
		for (int i = 0; i < rects_tracked.size(); i++)
		{
			std::cout << rects_tracked[i].id << "," << rects_tracked[i].rect << std::endl;
		}
			std::cout << "-------------" << std::endl;

	}
	{
		std::vector<cv::Rect> rects;
		{
			cv::Rect rect(10,10,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(250,250,100, 200);
			rects.push_back(rect);
		}
		
		std::vector<TrackedBox> rects_tracked;
		cv::Size img_size(1024, 760); //(width, height) 
		bool is_track = tracker.run(rects, img_size, rects_tracked);
		for (int i = 0; i < rects_tracked.size(); i++)
		{
			std::cout << rects_tracked[i].id << "," << rects_tracked[i].rect << std::endl;
		}
			std::cout << "-------------" << std::endl;

	}
	{
		std::vector<cv::Rect> rects;
		{
			cv::Rect rect(10,10,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(260,260,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(500,500,100, 200);
			rects.push_back(rect);
		}
		
		std::vector<TrackedBox> rects_tracked;
		cv::Size img_size(1024, 760); //(width, height) 
		bool is_track = tracker.run(rects, img_size, rects_tracked);
		for (int i = 0; i < rects_tracked.size(); i++)
		{
			std::cout << rects_tracked[i].id << "," << rects_tracked[i].rect << std::endl;
		}
			std::cout << "-------------" << std::endl;

	}
	{
		std::vector<cv::Rect> rects;
		{
			cv::Rect rect(10,10,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(250,250,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(500,500,100, 200);
			rects.push_back(rect);
		}
		
		std::vector<TrackedBox> rects_tracked;
		cv::Size img_size(1024, 760); //(width, height) 
		bool is_track = tracker.run(rects, img_size, rects_tracked);
		for (int i = 0; i < rects_tracked.size(); i++)
		{
			std::cout << rects_tracked[i].id << "," << rects_tracked[i].rect << std::endl;
		}
			std::cout << "-------------" << std::endl;
	}
	{
		std::vector<cv::Rect> rects;
		{
			cv::Rect rect(10,10,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(250,250,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(500,500,100, 200);
			rects.push_back(rect);
		}
		
		std::vector<TrackedBox> rects_tracked;
		cv::Size img_size(1024, 760); //(width, height) 
		bool is_track = tracker.run(rects, img_size, rects_tracked);
		for (int i = 0; i < rects_tracked.size(); i++)
		{
			std::cout << rects_tracked[i].id << "," << rects_tracked[i].rect << std::endl;
		}
			std::cout << "-------------" << std::endl;

	}
	{
		std::vector<cv::Rect> rects;
		{
			cv::Rect rect(10,10,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(250,250,100, 200);
			rects.push_back(rect);
		}
		{
			cv::Rect rect(500,500,100, 200);
			rects.push_back(rect);
		}
		
		std::vector<TrackedBox> rects_tracked;
		cv::Size img_size(1024, 760); //(width, height) 
		bool is_track = tracker.run(rects, img_size, rects_tracked);
		for (int i = 0; i < rects_tracked.size(); i++)
		{
			std::cout << rects_tracked[i].id << "," << rects_tracked[i].rect << std::endl;
		}
			std::cout << "-------------" << std::endl;

	}
	
	return 0;
}
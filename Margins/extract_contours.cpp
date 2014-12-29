#include <cassert>
#include <cstdint>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "rvolume.h"
#include "extract_contours.h"

std::list<std::vector<cv::Point>>* TOK::extract_contours(const TOK::rvolume* v, int iz)
{
	assert(iz >= 0);
	assert(v != 0);
	assert(iz < v->nz());

	const uint8_t* plane = v->plane(iz);

	cv::Mat src = cv::Mat::zeros(v->ny(), v->nx(), CV_8UC1); // exchange vx and vy?

	for (int r = 0; r != src.rows; ++r)
	{
		int ridx = r*src.cols;
		for (int c = 0; c != src.cols; ++c)
		{
			auto& color = src.at<uint8_t>(r, c);
			color = (plane[ridx + c] == 0) ? 0u : 1u;
		}
	}

	std::vector<std::vector<cv::Point>>  contours;
	std::vector<cv::Vec4i>               hierarchy;

	findContours(src, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

	if (contours.empty())
		return nullptr;

	auto r = new std::list<std::vector<cv::Point>>();
	for (auto i = contours.cbegin(); i != contours.cend(); ++i)
	{
		r->push_back(*i);
	}
	// src.deallocate();

	return r;
}

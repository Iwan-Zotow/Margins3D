#pragma once

#include <list>
#include <vector>

#include <opencv2/core/core.hpp>

namespace TOK
{
	class rvolume;

	std::list<std::vector<cv::Point> >* extract_contours(const rvolume* v, int iz);
}

#pragma once

#include <string>
#include <vector>

#include <opencv2/core/types.hpp>

struct DatasetItem
{
    std::string path;
    std::vector<cv::Rect> positiveRects;
    std::vector<cv::Rect> negativeRects;
};

using DatasetItems = std::vector<DatasetItem>;

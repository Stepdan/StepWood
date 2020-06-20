#pragma once

#include <string>
#include <vector>

#include <opencv2/core/types.hpp>

struct DatasetItem
{
    DatasetItem() = default;
    DatasetItem(const std::string& p, const std::vector<cv::Rect>& pos, const std::vector<cv::Rect>& neg)
        : path(p)
        , positiveRects(pos)
        , negativeRects(neg)
    {}

    std::string path;
    std::vector<cv::Rect> positiveRects;
    std::vector<cv::Rect> negativeRects;
};

using DatasetItems = std::vector<DatasetItem>;

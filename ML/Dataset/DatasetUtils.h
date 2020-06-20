#pragma once

#include <opencv2/core/mat.hpp>

#include "DatasetItem.h"

namespace ML::Utils {

std::vector<cv::Mat> FlipRotateAugmentation(const cv::Mat& mat);

DatasetItem FlipAugmentation(const DatasetItem& item, const std::string& saveDir,  const std::string& flipSuffix = "_flip");

void GenerateFakeNegative(DatasetItems& items);

}

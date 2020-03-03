#pragma once

#include <opencv2/core/mat.hpp>

class ISceneController
{
public:
    virtual ~ISceneController() = default;

    virtual void SetImage(const cv::Mat&, bool isNew = false) = 0;
    virtual const cv::Mat& GetImage() const = 0;
    virtual cv::Mat GetImage() = 0;
    virtual const cv::Mat& GetOrigImage() const = 0;
    virtual cv::Mat GetOrigImage() = 0;
};

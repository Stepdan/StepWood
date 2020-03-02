#pragma once

#include <memory>
#include <string>

#include "opencv2/imgproc.hpp"

namespace EyeFactive
{

class CVWrapper
{
public:
    CVWrapper();
    ~CVWrapper();

    void LoadImage(const std::string& path);
    void SaveImage(const std::string& path) const;
    void SetImage(const cv::Mat& mat);
    cv::Mat GetImage() const;
    cv::Mat GetOriginalImage() const;
    cv::Mat GetImageWithData() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

}

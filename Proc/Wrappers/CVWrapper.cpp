#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "CVWrapper.h"

namespace EyeFactive
{

class CVWrapper::Impl
{
public:
    void LoadImage(const std::string& path)
    {
        m_image = cv::imread(path);
        m_originalImage = m_image.clone();
    }

    void SaveImage(const std::string& path) const
    {
        cv::imwrite(path, m_image);
    }

    cv::Mat GetImage() const
    {
        return m_image.clone();
    }

    cv::Mat GetOriginalImage() const
    {
        return m_originalImage.clone();
    }

    cv::Mat GetImageWithData() const
    {
        return DrawData();
    }

    void SetImage(const cv::Mat& mat)
    {
        m_image = mat.clone();
    }

private:
    cv::Mat DrawData() const
    {
        return m_image;
    }

private:
    cv::Mat m_image;
    cv::Mat m_originalImage;
};

//.....................................................................................

CVWrapper::CVWrapper()
    : m_impl(std::make_unique<Impl>())
{}

//.....................................................................................

CVWrapper::~CVWrapper() = default;

//.....................................................................................

void CVWrapper::LoadImage(const std::string& path)
{
    m_impl->LoadImage(path);
}

//.....................................................................................

void CVWrapper::SaveImage(const std::string& path) const
{
    m_impl->SaveImage(path);
}

//.....................................................................................

void CVWrapper::SetImage(const cv::Mat& mat)
{
    m_impl->SetImage(mat);
}

//.....................................................................................

cv::Mat CVWrapper::GetImage() const
{
    return m_impl->GetImage();
}

//.....................................................................................

cv::Mat CVWrapper::GetOriginalImage() const
{
    return m_impl->GetOriginalImage();
}

//.....................................................................................

cv::Mat CVWrapper::GetImageWithData() const
{
    return m_impl->GetImageWithData();
}

}

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "CVWrapper.h"

namespace EyeFactive
{

class CVWrapper::Impl
{

};

//.....................................................................................

CVWrapper::CVWrapper()
    : m_impl(std::make_unique<Impl>())
{}

//.....................................................................................

CVWrapper::~CVWrapper() = default;

}

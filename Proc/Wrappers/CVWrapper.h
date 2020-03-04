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



private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

}

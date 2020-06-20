#pragma once

#include "Proc/Settings/DetectorSettings/BaseSettingsDetector.h"

namespace cv {
class Mat;
}

namespace Proc::Interfaces {

class IDetector
{
public:
    virtual ~IDetector() = default;

    virtual const BaseSettingsDetector& GetBaseSettings() const noexcept = 0;
    virtual void SetSettings(const BaseSettingsDetector& settings) = 0;
    virtual void Reset() = 0;

    virtual void Detect(const cv::Mat&) = 0;
};

}

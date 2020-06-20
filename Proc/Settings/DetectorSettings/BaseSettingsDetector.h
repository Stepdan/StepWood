#pragma once

#include <string>

namespace Proc {

class BaseSettingsDetector
{
public:
    virtual ~BaseSettingsDetector() = default;
    virtual const std::string & GetSettingsID() const noexcept { return "BaseSettingsDetector"; }

protected:
    BaseSettingsDetector() = default;
};

#define PROC_DETECTOR_SETTINGS(SettingsID) \
    static const std::string SETTINGS_ID;\
    const std::string & GetSettingsID() const noexcept { return SETTINGS_ID; }

}

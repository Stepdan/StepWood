#pragma once

#include "Proc/Interfaces/IDetector.h"

#include "Proc/Settings/DetectorSettings/BaseSettingsDetector.h"

namespace Proc {

template <typename SettingsTypeT>
class BaseDetector : public Interfaces::IDetector
{
protected:
    using SettingsType = SettingsTypeT;

protected:
    BaseDetector() = default;
    ~BaseDetector() = default;

    const BaseSettingsDetector & GetBaseSettings() const noexcept override
    {
        return m_typedSettings;
    }

    virtual void SetSettings(const BaseSettingsDetector & settings) override
    {
        const SettingsType & typedSettings = dynamic_cast<const SettingsType &>(settings);
        this->SetSettings(typedSettings);
    }

    void Reset() override
    {
        this->m_typedSettings = SettingsType();
    }

    void SetSettings(const SettingsType & settings)
    {
       if (this->m_typedSettings == settings)
            return;

        this->Reset();
        this->m_typedSettings = settings;
    }

    virtual void Detect(const cv::Mat&) override {}

protected:
    SettingsType m_typedSettings;
};

}

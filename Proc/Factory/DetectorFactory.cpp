#include "Proc/Settings/DetectorSettings/SettingsDetectorCircle.h"

#include "Utils/FindPair.h"

#include "DetectorFactory.h"

namespace Proc {

#define CREATE_DETECTOR(NAME) std::unique_ptr<Interfaces::IDetector> Create##NAME()

CREATE_DETECTOR(CircleDetector);

//.....................................................................................

std::pair<std::string, std::function<std::unique_ptr<Interfaces::IDetector>()>> g_creators[] = {
    { SettingsDetectorCircle::SETTINGS_ID, &CreateCircleDetector },
};

//.....................................................................................

std::unique_ptr<Interfaces::IDetector> CreateDetector(const std::string& id)
{
    const auto creator = Utils::FindSecond(std::cbegin(g_creators), std::cend(g_creators), id);
    return creator ? creator() : nullptr;
};

}

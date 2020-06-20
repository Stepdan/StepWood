#include "Proc/Settings/DetectorSettings/SettingsDetectorCircle.h"

#include "Utils/FindPair.h"

#include "DetectorFactory.h"

namespace Proc {

#define CREATE_DETECTOR(NAME) std::shared_ptr<Interfaces::IDetector> Create##NAME()

CREATE_DETECTOR(CircleDetector);

//.....................................................................................

std::pair<std::string, std::function<std::shared_ptr<Interfaces::IDetector>()>> g_creators[] = {
    { SettingsDetectorCircle::SETTINGS_ID, &CreateCircleDetector },
};

//.....................................................................................

std::shared_ptr<Interfaces::IDetector> CreateDetector(const std::string& id)
{
    return CreateCircleDetector();
    const auto creator = Utils::FindPairIteratorByFirst(std::cbegin(g_creators), std::cend(g_creators), id);
    return creator == std::cend(g_creators) ? creator->second() : nullptr;
};

}

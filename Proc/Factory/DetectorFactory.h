#pragma once

#include <memory>

#include "Proc/Interfaces/IDetector.h"

namespace Proc {

std::shared_ptr<Interfaces::IDetector> CreateDetector(const std::string&);

}

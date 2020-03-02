#pragma once

#include <memory>

#include "Proc/Interfaces/IDetector.h"

namespace Proc {

std::unique_ptr<Interfaces::IDetector> CreateDetector(const std::string&);

}

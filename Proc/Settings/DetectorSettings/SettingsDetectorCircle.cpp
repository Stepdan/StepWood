#include <cmath>

#include "SettingsDetectorCircle.h"

namespace Proc {

bool SettingsDetectorCircle::operator==(const SettingsDetectorCircle& rhs) const noexcept
{
    return true
        && m_algorithm   == rhs.m_algorithm
        && m_houghMethod == rhs.m_houghMethod
        && std::fabs(m_dp      - rhs.m_dp     ) < 1e-7
        && std::fabs(m_minDist - rhs.m_minDist) < 1e-7
        && std::fabs(m_param1  - rhs.m_param1 ) < 1e-7
        && std::fabs(m_param2  - rhs.m_param2 ) < 1e-7
        && m_minRadius   == rhs.m_minRadius
        && m_maxRadius     == rhs.m_maxRadius
    ;
}

}

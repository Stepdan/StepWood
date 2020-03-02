#pragma once

#include <vector>

namespace Proc {

struct Circle
{
    Circle() = default;
    Circle(int r, int cx, int cy) : radius(r), x(cx), y(cy) {}

    bool operator==(const Circle& rhs) { return radius == rhs.radius && x == rhs.x && y == rhs.y; }
    bool operator!=(const Circle& rhs) { return !(*this == rhs); }

    int x, y;
    int radius;
};

using Circles = std::vector<Circle>;

}

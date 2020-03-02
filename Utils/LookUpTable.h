#pragma once

#include <algorithm>

namespace Utils
{

template<typename T>
T Saturate(const T& value, const T& min, const T& max)
{
	return (value < min) ? min : (value > max) ? max : value;
}

template<typename X, typename Y>
class LUT
{
public:
	explicit LUT(const X& x0, const Y& y0, const X& x1, const Y& y1) : m_x0(x0), m_y0(y0), m_x1(x1), m_y1(y1) {}

	constexpr Y operator()(const X &value) const
	{
		return static_cast<Y>(m_y0 + (m_y1 - m_y0) * (value - m_x0) / (m_x1 - m_x0));
	}

	constexpr X X0() const { return m_x0; }
	constexpr X X1() const { return m_x1; }
	constexpr Y Y0() const { return m_y0; }
	constexpr Y Y1() const { return m_y1; }

private:
	X m_x0, m_x1;
	Y m_y0, m_y1;
};

}

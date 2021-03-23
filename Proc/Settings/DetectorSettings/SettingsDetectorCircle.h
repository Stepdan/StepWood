#pragma once

#include "Proc/Types/Circle.h"

#include "BaseSettingsDetector.h"

namespace Proc {

class SettingsDetectorCircle : public BaseSettingsDetector
{
public:
	enum class Algorithm
	{
		ED,
		Hough,
		HOG,
	};

	enum class HoughMethod
	{
		Standart      = 0,
		Probabilistic = 1,
		MultiScale    = 2,
		Gradient      = 3,
		GradientAlt   = 4,
	};

public:
	PROC_DETECTOR_SETTINGS(SettingsDetectorCircle)

	SettingsDetectorCircle() = default;

	bool operator==(const SettingsDetectorCircle& rhs) const noexcept;
	bool operator!=(const SettingsDetectorCircle& rhs) const noexcept { return !(*this == rhs); }

	void SetAlgorithm      (Algorithm value)   { m_algorithm      = value; }
	void SetHoughMethod    (HoughMethod value) { m_houghMethod    = value; }
	void SetDP             (double value)      { m_dp             = value; }
	void SetMinDist        (double value)      { m_minDist        = value; }
	void SetParam1         (double value)      { m_param1         = value; }
	void SetParam2         (double value)      { m_param2         = value; }
	void SetMinRadius      (int value)         { m_minRadius      = value; }
	void SetMaxRadius      (int value)         { m_maxRadius      = value; }
	void SetKernelSize     (int value)         { m_kernelSize = value; }
	void SetSigmaX		(double value)         { m_sigmaX = value; }
	void SetSigmaY		(double value)         { m_sigmaY = value; }

	Algorithm GetAlgorithm      () const noexcept { return m_algorithm      ; }
	HoughMethod GetHoughMethod  () const noexcept { return m_houghMethod    ; }
	double GetDP                () const noexcept { return m_dp             ; }
	double GetMinDist           () const noexcept { return m_minDist        ; }
	double GetParam1            () const noexcept { return m_param1         ; }
	double GetParam2            () const noexcept { return m_param2         ; }
	int GetMinRadius            () const noexcept { return m_minRadius      ; }
	int GetMaxRadius            () const noexcept { return m_maxRadius      ; }
	void SetCircles(const Circles& value) { m_circles = value; }
	const Circles& GetCircles() const noexcept { return m_circles; }

	int GetKernelSize() const noexcept { return m_kernelSize; }
	double GetSigmaX() const noexcept { return m_sigmaX; }
	double GetSigmaY() const noexcept { return m_sigmaY; }

private:
	Algorithm m_algorithm       { Algorithm::Hough };
	HoughMethod m_houghMethod   { HoughMethod::GradientAlt };
	double m_dp                 { 1.5 };
	double m_minDist            { 0.01 };
	double m_param1             { 300 }; // Canny threshold (look at HoughCirclesAlt int Opencv's hough.cpp)
	double m_param2             { 0.9 }; // minCos2
	int m_minRadius             { 10 };
	int m_maxRadius             { 90 };

	int m_kernelSize = 7;
	double m_sigmaX = 1.5;
	double m_sigmaY = 1.5;

	Circles m_circles;
};

}

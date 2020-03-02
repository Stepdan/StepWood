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
    };

public:
    PROC_DETECTOR_SETTINGS(SettingsDetectorCircle)

    SettingsDetectorCircle() = default;

    void SetAlgorithm   (Algorithm value)   { m_algorithm   = value; }
    void SetHoughMethod (HoughMethod value) { m_houghMethod = value; }
    void SetDP          (double value)      { m_dp          = value; }
    void SetMinDist     (double value)      { m_minDist     = value; }
    void SetParam1      (double value)      { m_param1      = value; }
    void SetParam2      (double value)      { m_param2      = value; }
    void SetMinRadius   (double value)      { m_minRadius   = value; }
    void SetMaxRadius   (double value)      { maxRadius     = value; }

    Algorithm GetAlgorithm      () const noexcept { return m_algorithm  ; }
    HoughMethod GetHoughMethod  () const noexcept { return m_houghMethod; }
    double GetDP                () const noexcept { return m_dp         ; }
    double GetMinDist           () const noexcept { return m_minDist    ; }
    double GetParam1            () const noexcept { return m_param1     ; }
    double GetParam2            () const noexcept { return m_param2     ; }
    int GetMinRadius            () const noexcept { return m_minRadius  ; }
    int GetMaxRadius            () const noexcept { return maxRadius    ; }

    void SetCircles(const Circles& value) { m_circles = value; }
    const Circles& GetCircles() const noexcept { return m_circles; }

private:
    Algorithm m_algorithm       { Algorithm::ED };
    HoughMethod m_houghMethod   { HoughMethod::Gradient };
    double m_dp                 { 1 };
    double m_minDist            { 10 };
    double m_param1             { 50 };
    double m_param2             { 20 };
    int m_minRadius             { 5 };
    int maxRadius               { 50 };

    Circles m_circles;
};

}

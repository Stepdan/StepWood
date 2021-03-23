#include <algorithm>
#include <memory>

#include <opencv2/imgproc.hpp>

#include "Thirdparty/EDLib/EDLib.h"

#include "Proc/Settings/DetectorSettings/SettingsDetectorCircle.h"

#include "Utils/FindPair.h"

#include "BaseDetector.h"

namespace Proc {

namespace Hough {

std::pair<SettingsDetectorCircle::HoughMethod, cv::HoughModes> g_cvHoughMethodMap[] = {
	{ SettingsDetectorCircle::HoughMethod::Standart     , cv::HOUGH_STANDARD        },
	{ SettingsDetectorCircle::HoughMethod::Probabilistic, cv::HOUGH_PROBABILISTIC   },
	{ SettingsDetectorCircle::HoughMethod::MultiScale   , cv::HOUGH_MULTI_SCALE     },
	{ SettingsDetectorCircle::HoughMethod::Gradient     , cv::HOUGH_GRADIENT        },
	{ SettingsDetectorCircle::HoughMethod::GradientAlt  , cv::HOUGH_GRADIENT_ALT    },
};

}

class CircleDetector : public BaseDetector<SettingsDetectorCircle>
{
public:
	~CircleDetector() = default;

	void Detect(const cv::Mat& frame) override
	{
		switch(m_typedSettings.GetAlgorithm())
		{
		case SettingsDetectorCircle::Algorithm::ED:
			m_typedSettings.SetCircles(ProcessED(frame));
			break;
		case SettingsDetectorCircle::Algorithm::Hough:
			m_typedSettings.SetCircles(ProcessHough(frame));
			break;
		case SettingsDetectorCircle::Algorithm::HOG:
			m_typedSettings.SetCircles(ProcessHOG(frame));
			break;
		default:
			assert(false);
		}
	}

private:
	Circles ProcessED(const cv::Mat& frame)
	{
		auto procFrame = frame.clone();
		cv::cvtColor(procFrame, procFrame, cv::COLOR_BGR2GRAY);
		EDCircles detector = EDCircles(procFrame);
		const auto circles = detector.getCircles();

		Circles result;
		result.reserve(circles.size());
		std::transform(circles.cbegin(), circles.cend(), std::back_inserter(result), [](const mCircle& c) { return Circle(static_cast<int>(c.center.x), static_cast<int>(c.center.y), static_cast<int>(c.r)); });

		return result;
	}

	Circles ProcessHough(const cv::Mat& frame)
	{
		auto procFrame = frame.clone();
		cv::cvtColor(procFrame, procFrame, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(procFrame, procFrame, cv::Size(m_typedSettings.GetKernelSize(), m_typedSettings.GetKernelSize()), m_typedSettings.GetSigmaX(), m_typedSettings.GetSigmaY());

		std::vector<cv::Vec3f> circles;
		cv::HoughCircles(
			procFrame,
			circles,
			Utils::FindSecond(std::cbegin(Hough::g_cvHoughMethodMap), std::cend(Hough::g_cvHoughMethodMap), m_typedSettings.GetHoughMethod()),
			m_typedSettings.GetDP(),
			m_typedSettings.GetMinDist(),
			m_typedSettings.GetParam1(),
			m_typedSettings.GetParam2(),
			m_typedSettings.GetMinRadius(),
			m_typedSettings.GetMaxRadius()
		);

		Circles result;
		result.reserve(circles.size());
		std::transform(circles.cbegin(), circles.cend(), std::back_inserter(result), [](const cv::Vec3f& c) { return Circle(c[2], c[0], c[1]); });

		return result;
	}

	Circles ProcessHOG(const cv::Mat& frame)
	{
		return Circles();
	}
};

//.....................................................................................

std::shared_ptr<Interfaces::IDetector> CreateCircleDetector()
{
	return std::shared_ptr<Interfaces::IDetector>(new CircleDetector());
}

}

#include <QFileInfo>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "DatasetUtils.h"

namespace ML::Utils {

std::vector<cv::Mat> FlipRotateAugmentation(const cv::Mat& mat)
{
    std::vector<cv::Mat> result;
    result.reserve(8);

    auto frame = mat.clone();

    const auto ProcessRotate = [&frame, &result]()
    {
        for(size_t i = 0; i < 4; ++i)
        {
            result.push_back(frame.clone());
            cv::rotate(frame, frame, cv::ROTATE_90_CLOCKWISE);
        }
    };

    ProcessRotate();
    cv::flip(frame, frame, 1);
    ProcessRotate();

    return result;
}

//.....................................................................................

DatasetItem FlipAugmentation(const DatasetItem& item, const std::string& flipSuffix /*= "_flip"*/)
{
    DatasetItem flippedItem;
    int w, h;
    {
        auto frame = cv::imread(item.path);
        w = frame.cols;
        h = frame.rows;
        cv::flip(frame, frame, 1);
        const auto fileInfo = QFileInfo(item.path.data());
        flippedItem.path = fileInfo.baseName().toStdString() + flipSuffix + "." + fileInfo.suffix().toStdString();
        cv::imwrite(flippedItem.path, frame);
    }

    flippedItem.positiveRects.reserve(item.positiveRects.size());
    std::transform(item.positiveRects.cbegin(), item.positiveRects.cend(), std::back_inserter(flippedItem.positiveRects), [&w, &h](const cv::Rect& rect)
    {
        return cv::Rect(w - rect.x - rect.width, h - rect.y - rect.height, rect.width, rect.height);
    });

    flippedItem.negativeRects.reserve(item.negativeRects.size());
    std::transform(item.negativeRects.cbegin(), item.negativeRects.cend(), std::back_inserter(flippedItem.negativeRects), [&w, &h](const cv::Rect& rect)
    {
        return cv::Rect(w - rect.x - rect.width, h - rect.y - rect.height, rect.width, rect.height);
    });

    return flippedItem;
}

//.....................................................................................

void GenerateFakeNegative(DatasetItems& items)
{
    for(auto& item : items)
    {
        item.negativeRects.clear();
        item.negativeRects.reserve(item.positiveRects.size());
        std::transform(item.positiveRects.cbegin(), item.positiveRects.cend(), std::back_inserter(item.negativeRects), [](const cv::Rect& rect)
        {
            return cv::Rect(rect.x + rect.width / 2, rect.y + rect.height / 2, rect.width, rect.height);
        });
    }
}

}

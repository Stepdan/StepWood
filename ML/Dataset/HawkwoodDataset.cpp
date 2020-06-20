#include <fstream>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include <QDir>
#include <QStringList>
#include <QTextStream>

#include "HawkwoodDataset.h"

namespace {

const std::string IMAGE_FILES_MASK      = "IMG_*.JPG";
const std::string POSITIVE_FILES_MASK   = "woodlogs_*.txt";
const std::string NEGATIVE_FILES_MASK   = "antiwoodlogs_*.txt";
const std::string HAWKWOOD_IMAGES_DIR   = "/Single Image Benchmark/S.1 and S.2 real";

}

class HawkwoodDataset::Impl
{
public:
    DatasetItems GetData() const
    {
        return m_items;
    }

    void Parse(const std::string& path)
    {
        QString dirPath = QString::fromStdString(path + HAWKWOOD_IMAGES_DIR);
        QDir directory(dirPath);
        QStringList imageFiles = directory.entryList(QStringList(IMAGE_FILES_MASK.data()));
        QStringList positiveFiles = directory.entryList(QStringList(POSITIVE_FILES_MASK.data()));
        QStringList negativeFiles = directory.entryList(QStringList(NEGATIVE_FILES_MASK.data()));

        assert(positiveFiles.size() == negativeFiles.size() && imageFiles.size() == positiveFiles.size());
        m_items.clear();
        for(size_t i = 0, size = positiveFiles.size(); i <size; ++i)
            m_items.emplace_back(dirPath.toStdString() + "/" + imageFiles[i].toStdString(), ParseFile(dirPath + "/" + positiveFiles[i]), ParseFile(dirPath + "/" + negativeFiles[i]));
    }

private:
    std::vector<cv::Rect> ParseFile(const QString& path) const
    {
        std::vector<cv::Rect> rects;
        QFile file(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd())
            {
                const auto dataList = in.readLine().split(";");
                rects.emplace_back(dataList[0].toInt(), dataList[1].toInt(), dataList[2].toInt(), dataList[3].toInt());
            }
        }

        return rects;
    }

private:
    DatasetItems m_items;
};

//.....................................................................................

HawkwoodDataset::HawkwoodDataset()
    : m_impl(std::make_unique<Impl>())
{}

//.....................................................................................

HawkwoodDataset::~HawkwoodDataset() = default;

//.....................................................................................

void HawkwoodDataset::Parse(const std::string& path)
{
    m_impl->Parse(path);
}

//.....................................................................................

DatasetItems HawkwoodDataset::GetHawkwoodData() const
{
    return m_impl->GetData();
}

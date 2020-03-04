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

const std::string IMAGE_FILES_MASK      = "IMG_*";
const std::string POSITIVE_FILES_MASK   = "woodlogs_*.txt";
const std::string NEGATIVE_FILES_MASK   = "antiwoodlogs_*.txt";
const std::string HAWKWOOD_IMAGES_DIR   = "/HAWKwood/Single Image Benchmark/S.1 and S.2 real";

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
        QDir directory(QString::fromStdString(path + HAWKWOOD_IMAGES_DIR));
        QStringList imageFiles = directory.entryList(QStringList(IMAGE_FILES_MASK.data()));
        QStringList positiveFiles = directory.entryList(QStringList(POSITIVE_FILES_MASK.data()));
        QStringList negativeFiles = directory.entryList(QStringList(NEGATIVE_FILES_MASK.data()));

        assert(positiveFiles.size() == negativeFiles.size() && positiveFiles.size() == imageFiles.size());
        m_items.clear();
        for(size_t i = 0, size = positiveFiles.size(); i <size; ++i)
            m_items.emplace_back(imageFiles[i].toStdString(), ParseFile(positiveFiles[i]), ParseFile(negativeFiles[i]));
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
                rects.emplace_back(dataList[0], dataList[1], dataList[2], dataList[3]);
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

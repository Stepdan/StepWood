#include <fstream>

#include <QDir>
#include <QTextStream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "DatasetUtils.h"
#include "HawkwoodDataset.h"

#include "DatasetWrapper.h"

namespace {

constexpr size_t START_VALUE = 1;
const std::string SEPARATOR = "/";

bool IsRectInsideImage(const cv::Rect& rect, int rows, int cols)
{
    return (rect.x >= 0 && rect.y >= 0 && rect.x + rect.width <= cols && rect.y + rect.height <= rows);
}

}

namespace ML {

class DatasetWrapper::Impl
{
public:
    explicit Impl(DatasetDescription&& datasetDesc)
        : m_desc(std::move(datasetDesc))
    {}

    void SetDescription(DatasetDescription&& datasetDesc)
    {
        m_desc = std::move(datasetDesc);
    }

    void CreateDataset()
    {
        if(m_desc.needHawkwoodParse && !m_desc.hawkwoodPath.empty())
            ParseHawkwood();

        auto hawkwoodData = m_hawkwoodDataset->GetHawkwoodData();
        //SaveXML(hawkwoodData);
        SaveSliced(hawkwoodData);
    }

private:
    void ParseHawkwood()
    {
        if(!m_hawkwoodDataset)
            m_hawkwoodDataset = std::make_unique<HawkwoodDataset>();
        m_hawkwoodDataset->Parse(m_desc.hawkwoodPath);
    }

    void SaveXML(const DatasetItems& hawkwoodItems)
    {
        const auto dirPath = m_desc.outputDir + SEPARATOR + m_desc.xmlDesc.dirName;
        if(!QDir(QString::fromStdString(dirPath)).exists())
            QDir().mkdir(QString::fromStdString(dirPath));

        const auto flipDirPath = m_desc.outputDir + SEPARATOR + m_desc.xmlDesc.flipDirName;
        if(!QDir(QString::fromStdString(flipDirPath)).exists())
            QDir().mkdir(QString::fromStdString(flipDirPath));

        auto items = hawkwoodItems;
        if(m_desc.xmlDesc.withFlipAugmentation)
        {
            DatasetItems flippedItems;
            flippedItems.reserve(items.size());
            std::transform(items.cbegin(), items.cend(), std::back_inserter(flippedItems), [&desc = m_desc, &flipDirPath](const auto& item) { return Utils::FlipAugmentation(item, flipDirPath); });
            items.insert(items.cend(), flippedItems.cbegin(), flippedItems.cend());
        }

        size_t counter = START_VALUE;
        const auto getName = [this, &counter]() { return m_desc.xmlDesc.filename + std::to_string(counter++) + "." + m_desc.extension; };

        // @todo use normal xml-library
        std::string xmlPath = dirPath + SEPARATOR + m_desc.xmlDesc.xmlFilename;
        auto file = QFile(QString::fromStdString(xmlPath));
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            assert(false);

        QTextStream xmlStream(&file);
        //std::fstream xmlStream(m_desc.xmlDesc.dirName + SEPARATOR + m_desc.xmlDesc.xmlFilename);
        xmlStream << "<?xml version='1.0' encoding='ISO-8859-1'?>" << "\n";
        xmlStream << "<dataset>" << "\n";
        xmlStream << "<images>" << "\n";
        for(const auto& item : items)
        {
            const auto name = getName();
            auto image = cv::imread(item.path);
            const auto origRows = image.rows;
            const auto origCols = image.cols;
            const auto scaleFactor = 1.0 * m_desc.maxSize / std::max(image.rows, image.cols);
            cv::resize(image, image, cv::Size(static_cast<int>(scaleFactor * image.cols), static_cast<int>(scaleFactor * image.rows)), 0, 0, cv::INTER_CUBIC);
            cv::imwrite(m_desc.outputDir + SEPARATOR + m_desc.xmlDesc.dirName + SEPARATOR + name, image);
            xmlStream << "\t<image file='" << QString::fromStdString(name) << "'>" << "\n";
            for(const auto& rect : item.positiveRects)
            {
                if(IsRectInsideImage(rect, origRows, origCols))
                    xmlStream << "\t\t"
                    << "<box top='"     << static_cast<int>(scaleFactor * rect.x)
                    << "' left='"       << static_cast<int>(scaleFactor * rect.y)
                    << "' width='"      << static_cast<int>(scaleFactor * rect.width)
                    << "' height='"     << static_cast<int>(scaleFactor * rect.height)
                    <<"'/>" << "\n";
            }
            xmlStream << "\t</image>" << "\n";
        }
        xmlStream << "</images>" << "\n";
        xmlStream << "</dataset>" << "\n";
    }

    void SaveSliced(const DatasetItems& hawkwoodItems)
    {
        const auto CreateDirIfNotExist = [](const std::string& path)
        {
            if(!QDir(QString::fromStdString(path)).exists())
                QDir().mkdir(QString::fromStdString(path));
        };

        const auto dirPath = m_desc.outputDir + SEPARATOR + m_desc.slicedDesc.dirName;
        const auto positivePath = dirPath + SEPARATOR + m_desc.slicedDesc.positiveDir;
        const auto negativePath = dirPath + SEPARATOR + m_desc.slicedDesc.negativeDir;

        CreateDirIfNotExist(dirPath);
        CreateDirIfNotExist(positivePath);
        CreateDirIfNotExist(negativePath);

        auto items = hawkwoodItems;
        Utils::GenerateFakeNegative(items);

        size_t posCounter = START_VALUE;
        size_t negCounter = START_VALUE;
        const auto getName = [this](const std::string& name, size_t& counter) { return name + std::to_string(counter++) + "." + m_desc.extension; };

        for(const auto& item : items)
        {
            const auto image = cv::imread(item.path);

            for(const auto& rect : item.positiveRects)
            {
                if(!IsRectInsideImage(rect, image.rows, image.cols))
                    continue;

                const auto roiImages = Utils::FlipRotateAugmentation(image(rect));
                for(const auto roiImage : roiImages)
                    cv::imwrite(positivePath + SEPARATOR + getName(m_desc.slicedDesc.positiveName, posCounter), roiImage);
            }

            for(const auto& rect : item.negativeRects)
            {
                if(!IsRectInsideImage(rect, image.rows, image.cols))
                    continue;

                const auto roiImages = Utils::FlipRotateAugmentation(image(rect));
                for(const auto roiImage : roiImages)
                    cv::imwrite(negativePath + SEPARATOR + getName(m_desc.slicedDesc.negativeName, negCounter), roiImage);
            }
        }
    }

private:
    DatasetDescription m_desc;
    std::unique_ptr<HawkwoodDataset> m_hawkwoodDataset;
};

//.....................................................................................

DatasetWrapper::DatasetWrapper()
    : m_impl(nullptr)
{}

//.....................................................................................

DatasetWrapper::~DatasetWrapper() = default;

//.....................................................................................

void DatasetWrapper::CreateDataset(DatasetDescription&& datasetDesc)
{
    if(!m_impl)
        m_impl = std::make_unique<Impl>(std::move(datasetDesc));
    else
        m_impl->SetDescription(std::move(datasetDesc));

    m_impl->CreateDataset();
}

}

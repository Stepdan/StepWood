#include <fstream>

#include <opencv2/imgcodecs.hpp>

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


    }

private:
    void ParseHawkwood()
    {
        if(!m_hawkwoodDataset)
            m_hawkwoodDataset = std::make_unique<HawkwoodDataset>();
        m_hawkwoodDataset->Parse(m_desc.hawkwoodPath);
    }

    void FlipRotateAugmentation(const DatasetItems& items)
    {
        for(const auto & item : items)
        {
            Utils::FlipRotateAugmentation()
        }
    }

    void SaveXML(const DatasetItems& hawkwoodItems)
    {
        auto items = hawkwoodItems;
        if(m_desc.xmlDesc.withFlipAugmentation)
        {
            DatasetItems flippedItems;
            flippedItems.reserve(items.size());
            std::transform(items.cbegin(), items.cend(), std::back_inserter(flippedItems), std::bind(&Utils::FlipAugmentation, std::placeholders::_1));
        }

        size_t counter = START_VALUE;
        const auto getName = [this, &counter]() { return m_desc.xmlDesc.filename + std::to_string(counter++) + "." + m_desc.extension; };

        // @todo use normal xml-library
        std::fstream xmlStream(m_desc.xmlDesc.dirName + SEPARATOR + m_desc.xmlDesc.xmlFilename);
        xmlStream << "<?xml version='1.0' encoding='ISO-8859-1'?>" << std::endl;
        xmlStream << "<dataset>" << std::endl;
        xmlStream << "<images>" << std::endl;
        for(const auto& item : items)
        {
            const auto name = getName();
            auto image = cv::imread(item.path);
            cv::imwrite(m_desc.xmlDesc.dirName + SEPARATOR + name, image);
            xmlStream << "\t<image file='" << name << "'>" << std::endl;
            for(const auto& rect : item.positiveRects)
            {
                if(IsRectInsideImage(rect, image.rows, image.cols))
                    xmlStream << "\t\t<box top='" << rect.x << "' left='" << rect.y << "' width='" << rect.width << "' height='" << rect.height <<"'/>" << std::endl;
            }
            xmlStream << "\t</image>" << std::endl;
        }
        xmlStream << "</images>" << std::endl;
        xmlStream << "</dataset>" << std::endl;
        xmlStream.close();
    }

    void SaveSliced(const DatasetItems& items)
    {
        size_t counter = START_VALUE;
        for(const auto& item : items)
        {
            if(m_desc.xmlDesc.)
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

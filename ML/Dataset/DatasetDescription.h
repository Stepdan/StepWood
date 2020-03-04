#pragma once

#include <string>

struct XMLDescription
{
    bool withFlipAugmentation;
    std::string dirName;
    std::string filename;
    std::string flipPrefix;
    std::string xmlFilename;
};

struct SlicedDescription
{
    bool withFlipRotateaugmentation;

    std::string dirName;

    std::string positiveDir;
    std::string positiveName;
    std::string positivePrefix;

    std::string negativeDir;
    std::string negativeName;
    std::string negativePrefix;
};

struct DatasetDescription
{
    bool needHawkwoodParse;
    std::string hawkwoodPath;

    std::string outputDir;
    std::string extension;

    XMLDescription xmlDesc;
    SlicedDescription slicedDesc;
};

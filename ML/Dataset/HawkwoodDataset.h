#pragma once

#include <memory>
#include <string>

#include "DatasetItem.h"

class HawkwoodDataset
{
public:
    HawkwoodDataset();
    ~HawkwoodDataset();

    void Parse(const std::string& path);
    DatasetItems GetHawkwoodData() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

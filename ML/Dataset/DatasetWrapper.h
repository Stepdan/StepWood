#pragma once

#include <memory>

#include "DatasetDescription.h"

namespace ML {

class DatasetWrapper
{
public:
    DatasetWrapper();
    ~DatasetWrapper();

    void CreateDataset(DatasetDescription&&);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

}

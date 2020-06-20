#pragma once

#include <memory>
#include <string>

namespace ML {

class SVMTrainer
{
public:
    SVMTrainer();
    ~SVMTrainer();

    void Train(const std::string& path);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

}

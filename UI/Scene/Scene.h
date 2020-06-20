#pragma once

#include <memory>

#include <QGraphicsView>

#include "Engine/Interfaces/ISceneController.h"

class Scene
    : public QGraphicsView
    , public ISceneController
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = nullptr);
    ~Scene();

/// ISceneController
public:
    void SetImage(const cv::Mat&, bool isNew = false) override;
    const cv::Mat& GetImage() const override;
    cv::Mat GetImage() override;
    const cv::Mat& GetOrigImage() const override;
    cv::Mat GetOrigImage() override;

protected:
    void wheelEvent(QWheelEvent* event) override;

private:
    void UpdateImage();

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

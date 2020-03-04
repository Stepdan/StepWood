#pragma once

#include <memory>

#include <QObject>

#include "UI/MainWindow.h"

class Mediator : public QObject
{
    Q_OBJECT

public:
    Mediator(const std::shared_ptr<MainWindow>& mainWindow);
    ~Mediator();

private slots:
    void OnLoad();
    void OnSave();
    void OnProcess();
    void OnDatasetProcess();

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;

    std::shared_ptr<MainWindow> m_mainWindow;
};

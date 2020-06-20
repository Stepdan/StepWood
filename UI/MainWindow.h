#pragma once

#include <memory>

#include <QMainWindow>

#include "Engine/Interfaces/ISceneController.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    ISceneController* GetSceneController() const;

signals:
    void loadFile();
    void saveFile();
    void process();
    void createDataset();
    void svmTrain();

private slots:
    void OnBeforeAfter(bool isActiveBefore);

private:
    void UpdateImage();


private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

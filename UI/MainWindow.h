#pragma once

#include <memory>

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void stop();

private slots:
    void OnLoad();
    void OnSave();
    void OnProcess();
    void OnBeforeAfter(bool isActiveBefore);
    void OnHOG();

private:
    void UpdateImage();


private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

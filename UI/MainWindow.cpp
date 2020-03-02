#include <fstream>

#include <QAbstractTableModel>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QStandardPaths>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Proc/CVWrapper.h"

#include "Utils/ImageUtils.h"

#include "Proc/Detector/CircleDetector.h"

#include "Proc/HOG/HOGEstimator.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

using namespace EyeFactive;

struct MainWindow::Impl
{
    Impl()
        : ui(Ui::MainWindow())
    {}

    Ui::MainWindow ui;
    CVWrapper cvWrapper;
    CircleDetector detector;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_impl(new Impl())
{
    m_impl->ui.setupUi(this);

    connect(m_impl->ui.loadButton, &QAbstractButton::clicked, this, &MainWindow::OnLoad);
    connect(m_impl->ui.saveButton, &QAbstractButton::clicked, this, &MainWindow::OnSave);
    connect(m_impl->ui.processButton, &QAbstractButton::clicked, this, &MainWindow::OnProcess);
    connect(m_impl->ui.hogButton, &QAbstractButton::clicked, this, &MainWindow::OnHOG);
    connect(m_impl->ui.beforeAfterButton, &QAbstractButton::pressed, this, std::bind(&MainWindow::OnBeforeAfter, this, true));
    connect(m_impl->ui.beforeAfterButton, &QAbstractButton::released, this, std::bind(&MainWindow::OnBeforeAfter, this, false));
}

//.....................................................................................

MainWindow::~MainWindow() = default;

//.....................................................................................

void MainWindow::OnLoad()
{
    const auto filename = QFileDialog::getOpenFileName(this, "Open file", QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).front(), "All Files (*.*)");

    if(filename.isEmpty())
        return;

    m_impl->cvWrapper.LoadImage(filename.toStdString());
    UpdateImage();
}

//.....................................................................................

void MainWindow::OnSave()
{
    const auto filename = QFileDialog::getSaveFileName(this, "Save file", QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).front(), "Images (*.png, *.bmp, *.jpg)");

    if(filename.isEmpty())
        return;

    m_impl->cvWrapper.SaveImage(filename.toStdString());
}

//.....................................................................................

void MainWindow::OnProcess()
{
    m_impl->cvWrapper.SetImage(m_impl->detector.Process(m_impl->cvWrapper.GetImage()));
    UpdateImage();
}

//.....................................................................................

void MainWindow::OnBeforeAfter(bool isActiveBefore)
{
    m_impl->ui.graphicsView->SetImage(Utils::cvMat2QImage(isActiveBefore ? m_impl->cvWrapper.GetOriginalImage() : m_impl->cvWrapper.GetImage()));
}

//.....................................................................................

void MainWindow::UpdateImage()
{
    m_impl->ui.graphicsView->SetImage(Utils::cvMat2QImage(m_impl->cvWrapper.GetImage()));
}

void MainWindow::OnHOG()
{
    //HOGEstimator estimator("B:/Work/Dataset/HAWKWood/HAWKwood/Single Image Benchmark/S.1 and S.2 real");
    HOGEstimator estimator("B:/Work/Dataset/HAWKWood/HAWKwood/Generated/all");
}

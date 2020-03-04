#include <QFileDialog>
#include <QStandardPaths>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Utils/ImageUtils.h"

#include "Interfaces/ISceneController.h"

#include "Mediator.h"

//.....................................................................................

struct Mediator::Impl
{
    Impl(ISceneController* controller)
        : sceneController(controller)
    {}

    ISceneController* sceneController;
};

//.....................................................................................

Mediator::Mediator(const std::shared_ptr<MainWindow>& mainWindow)
    : m_impl(std::make_unique<Impl>(mainWindow->GetSceneController()))
    , m_mainWindow(mainWindow)
{
}

//.....................................................................................

Mediator::~Mediator() = default;

//.....................................................................................

void Mediator::OnLoad()
{
    const auto filepath = QFileDialog::getOpenFileName(m_mainWindow.get(), "Open file", QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).front(), "All Files (*.*)");

    if(filepath.isEmpty())
        return;

    m_impl->sceneController->SetImage(cv::imread(filepath.toStdString()));
}

//.....................................................................................

void Mediator::OnSave()
{
    const auto filepath = QFileDialog::getSaveFileName(m_mainWindow.get(), "Save file", QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).front(), "Images (*.png, *.bmp, *.jpg)");

    if(filepath.isEmpty())
        return;

    cv::imwrite(filepath.toStdString(), m_impl->sceneController->GetImage());
}

//.....................................................................................

void Mediator::OnProcess()
{

}

//.....................................................................................

void Mediator::OnDatasetProcess()
{

}

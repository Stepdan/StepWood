#include "MainWindow.h"
#include "ui_MainWindow.h"


struct MainWindow::Impl
{
    Impl()
        : ui(Ui::MainWindow())
    {}

    Ui::MainWindow ui;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_impl(new Impl())
{
    m_impl->ui.setupUi(this);

    connect(m_impl->ui.loadButton, &QAbstractButton::clicked, this, &MainWindow::loadFile);
    connect(m_impl->ui.saveButton, &QAbstractButton::clicked, this, &MainWindow::saveFile);
    connect(m_impl->ui.processButton, &QAbstractButton::clicked, this, &MainWindow::process);
    connect(m_impl->ui.createDatasetButton, &QAbstractButton::clicked, this, &MainWindow::createDataset);

    connect(m_impl->ui.beforeAfterButton, &QAbstractButton::pressed, this, std::bind(&MainWindow::OnBeforeAfter, this, true));
    connect(m_impl->ui.beforeAfterButton, &QAbstractButton::released, this, std::bind(&MainWindow::OnBeforeAfter, this, false));
}

//.....................................................................................

MainWindow::~MainWindow() = default;

//.....................................................................................

ISceneController* MainWindow::GetSceneController() const
{
    return m_impl->ui.graphicsView;
}

//.....................................................................................

void MainWindow::OnBeforeAfter(bool isActiveBefore)
{
    m_impl->ui.graphicsView->SetImage(isActiveBefore ? m_impl->ui.graphicsView->GetOrigImage() : m_impl->ui.graphicsView->GetImage());
}

//.....................................................................................

void MainWindow::UpdateImage()
{
    m_impl->ui.graphicsView->SetImage(m_impl->ui.graphicsView->GetImage());
}

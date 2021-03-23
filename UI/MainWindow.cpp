#include "MainWindow.h"
#include "ui_MainWindow.h"


struct MainWindow::Impl
{
	Impl()
		: ui(Ui::MainWindow())
	{}

	Ui::MainWindow ui;

	Proc::SettingsDetectorCircle circleDetectionSettings;
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
	connect(m_impl->ui.svmTrainButton, &QAbstractButton::clicked, this, &MainWindow::svmTrain);

	connect(m_impl->ui.beforeAfterButton, &QAbstractButton::pressed, this, std::bind(&MainWindow::OnBeforeAfter, this, true));
	connect(m_impl->ui.beforeAfterButton, &QAbstractButton::released, this, std::bind(&MainWindow::OnBeforeAfter, this, false));

	connect(m_impl->ui.DPSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::OnSetDP);
	connect(m_impl->ui.minDistSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::OnSetMinDist);
	connect(m_impl->ui.param1SpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::OnSetParam1);
	connect(m_impl->ui.param2SpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::OnSetParam2);
	connect(m_impl->ui.minRadiusSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::OnSetMinRadius);
	connect(m_impl->ui.maxRadiusSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::OnSetMaxRadius);

	connect(m_impl->ui.sigmaXSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::OnSetSigmaX);
	connect(m_impl->ui.sigmaYSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::OnSetSigmaY);
	connect(m_impl->ui.kernelSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::OnSetKernelSize);

	connect(m_impl->ui.houghRadioButton, &QRadioButton::clicked, this, [this](){ OnAlgorithmChanged(Proc::SettingsDetectorCircle::Algorithm::Hough); });
	connect(m_impl->ui.EDRadioButton, &QRadioButton::clicked, this, [this](){ OnAlgorithmChanged(Proc::SettingsDetectorCircle::Algorithm::ED); });

	connect(m_impl->ui.StandartRadioButton, &QRadioButton::clicked, this, [this](){ OnHoughMethodChanged(Proc::SettingsDetectorCircle::HoughMethod::Standart); });
	connect(m_impl->ui.ProbRadioButton, &QRadioButton::clicked, this, [this](){ OnHoughMethodChanged(Proc::SettingsDetectorCircle::HoughMethod::Probabilistic); });
	connect(m_impl->ui.MultiScaleRadioButton, &QRadioButton::clicked, this, [this](){ OnHoughMethodChanged(Proc::SettingsDetectorCircle::HoughMethod::MultiScale); });
	connect(m_impl->ui.GradientRadioButton, &QRadioButton::clicked, this, [this](){ OnHoughMethodChanged(Proc::SettingsDetectorCircle::HoughMethod::Gradient); });
	connect(m_impl->ui.GradientAltRadioButton, &QRadioButton::clicked, this, [this](){ OnHoughMethodChanged(Proc::SettingsDetectorCircle::HoughMethod::GradientAlt); });

}

//.....................................................................................

MainWindow::~MainWindow() = default;

//.....................................................................................

Proc::SettingsDetectorCircle MainWindow::GetSettings()
{
	return m_impl->circleDetectionSettings;
}

//.....................................................................................

ISceneController* MainWindow::GetSceneController() const
{
	return m_impl->ui.graphicsView;
}

//.....................................................................................

void MainWindow::OnBeforeAfter(bool isActiveBefore)
{
	if(isActiveBefore)
		m_impl->ui.graphicsView->SetBefore();
	else
		m_impl->ui.graphicsView->SetAfter();
}

//.....................................................................................

void MainWindow::OnSetKernelSize(int value)
{
	m_impl->circleDetectionSettings.SetKernelSize(value);
}

//.....................................................................................

void MainWindow::OnSetSigmaX(double value)
{
	m_impl->circleDetectionSettings.SetSigmaX(value);
}

//.....................................................................................

void MainWindow::OnSetSigmaY(double value)
{
	m_impl->circleDetectionSettings.SetSigmaY(value);
}

//.....................................................................................

void MainWindow::OnSetDP(double value)
{
	m_impl->circleDetectionSettings.SetDP(value);
}

//.....................................................................................

void MainWindow::OnSetMinDist(double value)
{
	m_impl->circleDetectionSettings.SetMinDist(value);
}

//.....................................................................................

void MainWindow::OnSetParam1(double value)
{
	m_impl->circleDetectionSettings.SetParam1(value);
}

//.....................................................................................

void MainWindow::OnSetParam2(double value)
{
	m_impl->circleDetectionSettings.SetParam2(value);
}

//.....................................................................................

void MainWindow::OnSetMinRadius(int value)
{
	m_impl->circleDetectionSettings.SetMinRadius(value);
}

//.....................................................................................

void MainWindow::OnSetMaxRadius(int value)
{
	m_impl->circleDetectionSettings.SetMaxRadius(value);
}

//.....................................................................................

void MainWindow::OnHoughMethodChanged(Proc::SettingsDetectorCircle::HoughMethod value)
{
	m_impl->circleDetectionSettings.SetHoughMethod(value);
}

//.....................................................................................

void MainWindow::OnAlgorithmChanged(Proc::SettingsDetectorCircle::Algorithm value)
{
	m_impl->circleDetectionSettings.SetAlgorithm(value);
}

//.....................................................................................

void MainWindow::UpdateImage()
{
	m_impl->ui.graphicsView->SetImage(m_impl->ui.graphicsView->GetImage());
}

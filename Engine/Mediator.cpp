#include <QFileDialog>
#include <QStandardPaths>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Utils/ImageUtils.h"

#include "Interfaces/ISceneController.h"

#include "ML/Dataset/DatasetWrapper.h"
//#include "ML/Trainer/SVMTrainer.h"

#include "Proc/Factory/DetectorFactory.h"
#include "Proc/Settings/DetectorSettings/SettingsDetectorCircle.h"

#include "Mediator.h"

#include "Thirdparty/EDLib/EDLines.h"

//.....................................................................................

struct Mediator::Impl
{
	Impl(ISceneController* controller)
		: sceneController(controller)
	{}

	ISceneController* sceneController;
	ML::DatasetWrapper dataset;
};

//.....................................................................................

Mediator::Mediator(const std::shared_ptr<MainWindow>& mainWindow)
	: m_impl(std::make_unique<Impl>(mainWindow->GetSceneController()))
	, m_mainWindow(mainWindow)
{
	connect(m_mainWindow.get(), &MainWindow::loadFile       , this, &Mediator::OnLoad);
	connect(m_mainWindow.get(), &MainWindow::saveFile       , this, &Mediator::OnSave);
	connect(m_mainWindow.get(), &MainWindow::process        , this, &Mediator::OnProcess);
	connect(m_mainWindow.get(), &MainWindow::createDataset  , this, &Mediator::OnDatasetProcess);
	connect(m_mainWindow.get(), &MainWindow::svmTrain       , this, &Mediator::OnSVMTrain);
}

//.....................................................................................

Mediator::~Mediator() = default;

//.....................................................................................

void Mediator::OnLoad()
{
	const auto filepath = QFileDialog::getOpenFileName(m_mainWindow.get(), "Open file", QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).front(), "All Files (*.*)");

	if(filepath.isEmpty())
		return;

	m_impl->sceneController->SetImage(cv::imread(filepath.toStdString()), true);
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

	Proc::SettingsDetectorCircle settings;
	settings.SetAlgorithm(Proc::SettingsDetectorCircle::Algorithm::Hough);
	settings.SetHoughMethod(Proc::SettingsDetectorCircle::HoughMethod::Gradient);
	settings.SetDP(1.5);
	settings.SetMinDist(30);
	settings.SetParam1(300);
	settings.SetParam2(0.9);
	settings.SetMinRadius(22);
	settings.SetMaxRadius(22);

	const auto detector = Proc::CreateDetector(Proc::SettingsDetectorCircle::SETTINGS_ID);
	//detector->SetSettings(settings);
	detector->SetSettings(m_mainWindow->GetSettings());

	//auto orig = m_impl->sceneController->GetOrigImage();
	//cv::cvtColor(orig, orig, cv::COLOR_BGR2GRAY);
	//auto ed = EDLines(orig).drawOnImage();

	detector->Detect(m_impl->sceneController->GetOrigImage());
	const auto circles = dynamic_cast<const Proc::SettingsDetectorCircle&>(detector->GetBaseSettings()).GetCircles();

	auto image = m_impl->sceneController->GetOrigImage();
	for(const auto& circle : circles)
	{
		cv::circle(image, cv::Point(circle.x, circle.y), circle.radius, cv::Scalar(0, 255, 0), 1);
	}

	m_impl->sceneController->SetImage(image);
}

//.....................................................................................

void Mediator::OnDatasetProcess()
{
	DatasetDescription description;
	description.needHawkwoodParse = true;
	description.hawkwoodPath    = "B:/Work/Dataset/HAWKWood/HAWKwood";
	description.outputDir       = "B:/Work/Dataset/HAWKWood/Output";
	description.extension       = "bmp";

	description.xmlDesc.dirName     = "XmlData";
	description.xmlDesc.filename    = "Image";
	description.xmlDesc.xmlFilename = "Data.xml";
	description.xmlDesc.flipDirName = "Flip";
	description.xmlDesc.flipPrefix  = "_flip";
	description.xmlDesc.withFlipAugmentation = true;

	description.slicedDesc.dirName      = "SlicedData";
	description.slicedDesc.positiveDir  = "Good";
	description.slicedDesc.positiveName = "Good";
	description.slicedDesc.negativeDir  = "Bad";
	description.slicedDesc.negativeName = "Bad";
	description.slicedDesc.withFlipRotateAugmentation = true;

	m_impl->dataset.CreateDataset(std::move(description));
}

//.....................................................................................

void Mediator::OnSVMTrain()
{
	//ML::SVMTrainer trainer;
	//trainer.Train("B:/Work/Dataset/HAWKWood/Output/XmlData");
}

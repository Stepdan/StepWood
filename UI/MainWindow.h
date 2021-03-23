#pragma once

#include <memory>

#include <QMainWindow>

#include "Engine/Interfaces/ISceneController.h"

#include "Proc/Settings/DetectorSettings/SettingsDetectorCircle.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public:
	ISceneController* GetSceneController() const;

	Proc::SettingsDetectorCircle GetSettings();

signals:
	void loadFile();
	void saveFile();
	void process();
	void createDataset();
	void svmTrain();

private slots:
	void OnBeforeAfter(bool isActiveBefore);

	void OnSetKernelSize(int);
	void OnSetSigmaX(double);
	void OnSetSigmaY(double);

	void OnSetDP(double);
	void OnSetMinDist(double);
	void OnSetParam1(double);
	void OnSetParam2(double);
	void OnSetMinRadius(int);
	void OnSetMaxRadius(int);
	void OnHoughMethodChanged(Proc::SettingsDetectorCircle::HoughMethod);
	void OnAlgorithmChanged(Proc::SettingsDetectorCircle::Algorithm);

private:
	void UpdateImage();


private:
	struct Impl;
	std::unique_ptr<Impl> m_impl;
};

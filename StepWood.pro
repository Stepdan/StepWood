QT += core gui widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	Dataset/DatasetWrapper.cpp \
	Engine/Application.cpp \
	Engine/Mediator.cpp \
	Proc/Detector/CircleDetector.cpp \
	Proc/Factory/DetectorFactory.cpp \
	Proc/HOG/HOGEstimator.cpp \
	Proc/HOG/HOGTrainer.cpp \
	Proc/Settings/DetectorSettings/Stub.cpp \
	Proc/Settings/DetectorSettings/stub.cpp \
	Proc/Wrappers/CVWrapper.cpp \
	Thirdparty/EDLib/ED.cpp \
	Thirdparty/EDLib/EDCircles.cpp \
	Thirdparty/EDLib/EDColor.cpp \
	Thirdparty/EDLib/EDLines.cpp \
	Thirdparty/EDLib/EDPF.cpp \
	Thirdparty/EDLib/NFA.cpp \
	Thirdparty/EDLib/test.cpp \
	UI/MainWindow.cpp \
	UI/Scene/Scene.cpp \
	Utils/Forwarder.cpp \
	Utils/ImageUtils.cpp \
	Utils/ThreadWorker.cpp \
	main.cpp

HEADERS += \
	Dataset/DatasetWrapper.h \
	Engine/Application.h \
	Engine/Mediator.h \
	Proc/Detector/BaseDetector.h \
	Proc/Enums/DetectorType.h \
	Proc/Factory/DetectorFactory.h \
	Proc/HOG/HOGEstimator.h \
	Proc/HOG/HOGTrainer.h \
	Proc/Interfaces/IDetector.h \
	Proc/Settings/DetectorSettings/BaseSettingsDetector.h \
	Proc/Settings/DetectorSettings/SettingsDetectorCircle.h \
	Proc/Types/Circle.h \
	Proc/Wrappers/CVWrapper.h \
	Thirdparty/EDLib/ED.h \
	Thirdparty/EDLib/EDCircles.h \
	Thirdparty/EDLib/EDColor.h \
	Thirdparty/EDLib/EDLib.h \
	Thirdparty/EDLib/EDLines.h \
	Thirdparty/EDLib/EDPF.h \
	Thirdparty/EDLib/NFA.h \
	UI/MainWindow.h \
	UI/Scene/Scene.h \
	Utils/FindPair.h \
	Utils/Forwarder.h \
	Utils/ImageUtils.h \
	Utils/LookUpTable.h \
	Utils/RAII/PainterGuard.h \
	Utils/ThreadWorker.h

FORMS += \
	UI/MainWindow.ui

INCLUDEPATH += \
"C:/StepTech/SDK/OpenCV/include"


win32:CONFIG(release, debug|release): LIBS += \
C:/StepTech/SDK/OpenCV/static/release/zlib.lib \
C:/StepTech/SDK/OpenCV/static/release/IlmImf.lib \
C:/StepTech/SDK/OpenCV/static/release/ittnotify.lib \
C:/StepTech/SDK/OpenCV/static/release/libjasper.lib \
C:/StepTech/SDK/OpenCV/static/release/libjpeg-turbo.lib \
C:/StepTech/SDK/OpenCV/static/release/libpng.lib \
C:/StepTech/SDK/OpenCV/static/release/libprotobuf.lib \
C:/StepTech/SDK/OpenCV/static/release/libtiff.lib \
C:/StepTech/SDK/OpenCV/static/release/libwebp.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_calib3d420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_core420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_dnn420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_features2d420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_flann420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_imgcodecs420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_imgproc420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_ml420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_objdetect420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_photo420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_stitching420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_video420.lib \
C:/StepTech/SDK/OpenCV/static/release/opencv_videoio420.lib

else:win32:CONFIG(debug, debug|release): LIBS += \
C:/StepTech/SDK/OpenCV/static/debug/zlibd.lib \
C:/StepTech/SDK/OpenCV/static/debug/IlmImfd.lib \
C:/StepTech/SDK/OpenCV/static/debug/ittnotifyd.lib \
C:/StepTech/SDK/OpenCV/static/debug/libjasperd.lib \
C:/StepTech/SDK/OpenCV/static/debug/libjpeg-turbod.lib \
C:/StepTech/SDK/OpenCV/static/debug/libpngd.lib \
C:/StepTech/SDK/OpenCV/static/debug/libprotobufd.lib \
C:/StepTech/SDK/OpenCV/static/debug/libtiffd.lib \
C:/StepTech/SDK/OpenCV/static/debug/libwebpd.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_calib3d420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_core420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_imgcodecs420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_imgproc420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_dnn420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_features2d420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_flann420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_ml420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_objdetect420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_photo420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_stitching420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_video420d.lib \
C:/StepTech/SDK/OpenCV/static/debug/opencv_videoio420d.lib


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += core gui widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	Engine/Application.cpp \
	Engine/Mediator.cpp \
	ML/Dataset/DatasetUtils.cpp \
	ML/Dataset/DatasetWrapper.cpp \
	ML/Dataset/HawkwoodDataset.cpp \
	ML/Trainer/HOGTrainer.cpp \
	#ML/Trainer/SVMTrainer.cpp \
	Proc/Detector/CircleDetector.cpp \
	Proc/Factory/DetectorFactory.cpp \
	Proc/HOG/HOGEstimator.cpp \
	Proc/HOG/HOGTrainer.cpp \
	Proc/Settings/DetectorSettings/SettingsDetectorCircle.cpp \
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
	#Thirdparty/HOGTrainer/oldmain.cpp \
	UI/MainWindow.cpp \
	UI/Scene/Scene.cpp \
	Utils/Forwarder.cpp \
	Utils/ImageUtils.cpp \
	main.cpp

HEADERS += \
	DeclareMetatype.h \
	Engine/Application.h \
	Engine/Interfaces/ISceneController.h \
	Engine/Mediator.h \
	ML/Dataset/DatasetDescription.h \
	ML/Dataset/DatasetItem.h \
	ML/Dataset/DatasetUtils.h \
	ML/Dataset/DatasetWrapper.h \
	ML/Dataset/HawkwoodDataset.h \
	ML/Trainer/HOGTrainer.h \
	#ML/Trainer/SVMTrainer.h \
	Proc/Detector/BaseDetector.h \
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
	#Thirdparty/HOGTrainer/libsvm/libsvm.h \
	#Thirdparty/HOGTrainer/svmlight/svmlight.h \
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
"C:/Projects/SDK/opencv/include"

win32:CONFIG(release, debug|release): LIBS += \
C:/Projects/SDK/opencv/lib/release/zlib.lib \
C:/Projects/SDK/opencv/lib/release/IlmImf.lib \
#C:/Projects/SDK/opencv/lib/release/ittnotify.lib \
C:/Projects/SDK/opencv/lib/release/libjasper.lib \
C:/Projects/SDK/opencv/lib/release/libjpeg-turbo.lib \
C:/Projects/SDK/opencv/lib/release/libpng.lib \
C:/Projects/SDK/opencv/lib/release/libprotobuf.lib \
#C:/Projects/SDK/opencv/lib/release/libtiff.lib \
C:/Projects/SDK/opencv/lib/release/libwebp.lib \
C:/Projects/SDK/opencv/lib/release/opencv_calib3d430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_core430.lib \
#C:/Projects/SDK/opencv/lib/release/opencv_dnn430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_features2d430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_flann430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_imgcodecs430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_imgproc430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_ml430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_objdetect430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_photo430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_stitching430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_video430.lib \
C:/Projects/SDK/opencv/lib/release/opencv_videoio430.lib

else:win32:CONFIG(debug, debug|release): LIBS += \
C:/Projects/SDK/opencv/lib/debug/zlibd.lib \
C:/Projects/SDK/opencv/lib/debug/IlmImfd.lib \
C:/Projects/SDK/opencv/lib/debug/ittnotifyd.lib \
C:/Projects/SDK/opencv/lib/debug/libjasperd.lib \
C:/Projects/SDK/opencv/lib/debug/libjpeg-turbod.lib \
C:/Projects/SDK/opencv/lib/debug/libpngd.lib \
C:/Projects/SDK/opencv/lib/debug/libprotobufd.lib \
#C:/Projects/SDK/opencv/lib/debug/libtiffd.lib \
C:/Projects/SDK/opencv/lib/debug/libwebpd.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_calib3d430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_core430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_imgcodecs430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_imgproc430d.lib \
#C:/Projects/SDK/opencv/lib/debug/opencv_dnn430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_features2d430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_flann430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_ml430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_objdetect430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_photo430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_stitching430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_video430d.lib \
C:/Projects/SDK/opencv/lib/debug/opencv_videoio430d.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

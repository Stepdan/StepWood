#include "UI/MainWindow.h"

#include "Engine/Application.h"
#include "Engine/Mediator.h"

int main(int argc, char *argv[])
{
    Application application(argc, argv);

    std::shared_ptr<MainWindow> mainWindow(new MainWindow());
    Mediator mediator(mainWindow);

    stepWoodApp->installEventFilter(&mediator);
    stepWoodApp->installEventFilter(mainWindow.get());
    //stepWoodApp->SetStyle();
    mainWindow->show();

    return application.exec();
}

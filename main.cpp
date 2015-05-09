
//#include "Network.hpp"
#include "MainWindow.hpp"
#include <iostream>
#include <QtGui\QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	MainWindow mainWin;
    //Q_INIT_RESOURCE(dockwidgets);
	mainWin.resize(1200, 800);
    mainWin.show();

    return app.exec();

}
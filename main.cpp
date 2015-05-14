#include "MainWindow.hpp"
#include <iostream>
#include <QtGui\QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	MainWindow mainWin;
	mainWin.resize(1200, 800);
    mainWin.show();

    return app.exec();

}
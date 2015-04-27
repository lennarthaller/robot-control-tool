#include "syncNetwork.hpp"
#include "Network.hpp"
#include "MainWindow.hpp"
#include <iostream>
#include <QtGui\QApplication>
#include "GlobalState.hpp"

int main(int argc, char *argv[])
{
  CNetwork Network;
  Worker UpdateData;
  GlobalState State;

	if (Network.NetworkInit () == 1) {
		std::cout << "Netzwerkfehler." << std::endl;
	}

    QApplication app(argc, argv);
    //Q_INIT_RESOURCE(dockwidgets);
	MainWindow& mainWin = GlobalState::GetMainWindow ();
	mainWin.resize(800, 600);
    mainWin.show();

    return app.exec();

}
#include "menu.hpp"
#include <Qt\QMenu.h>
#include <Qt\QMenuBar.h>


SimpleMenu::SimpleMenu(QWidget *parent)
    : QMainWindow(parent)
{
  QAction *quit = new QAction("&Quit", this);
  QAction *Info = new QAction("Info", this);

  QAction *ShowScan = new QAction ("&Show Scan", this);
  QAction *ShowMotorData = new QAction ("&Show motor data", this);
  QAction *ShowOverallInformation = new QAction ("&Show overall information", this);

  QMenu *General;
  QMenu *ShowSensorData;

  ShowSensorData = menuBar()->addMenu("&Show sensor data");
  ShowSensorData->addAction (ShowScan);
  ShowSensorData->addAction (ShowMotorData);
  ShowSensorData->addAction (ShowOverallInformation);

  General = menuBar()->addMenu("&General");
  General->addAction(quit);
  General->addAction(Info);

  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}
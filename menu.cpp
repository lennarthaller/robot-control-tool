#include "menu.hpp"
#include <Qt\QMenu.h>
#include <Qt\QMenuBar.h>


SimpleMenu::SimpleMenu(QWidget *parent)
    : QMainWindow(parent)
{
  QAction *quit = new QAction("&Quit", this);
  QAction *open = new QAction("&Open", this);

  QMenu *file;
  file = menuBar()->addMenu("&File");
  file->addAction(quit);
  file->addAction(open);

  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
}
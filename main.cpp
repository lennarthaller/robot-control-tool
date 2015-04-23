#include "menu.hpp"
#include "syncNetwork.hpp"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);  
    
  SimpleMenu window;

  window.resize(800, 600);
  window.move(300, 100);
  window.setWindowTitle("Test menu");
  window.show();

  return app.exec();
}

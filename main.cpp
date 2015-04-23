#include "menu.hpp"
#include "syncNetwork.hpp"
#include "Network.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);  
    
  SimpleMenu window;

  CNetwork Network;

	if (Network.NetworkInit () == 1) {
		std::cout << "Netzwerkfehler." << std::endl;
	}

  window.resize(800, 600);
  window.move(300, 100);
  window.setWindowTitle("Robot Control  Tool");
  window.show();

  return app.exec();
}

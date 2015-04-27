#ifndef GLOBAL_STATE_HPP
#define GLOBAL_STATE_HPP

#include "MainWindow.hpp"

class GlobalState {

public:
	static MainWindow& GetMainWindow ();

private: 
	static std::shared_ptr <MainWindow> MainWindow_;

};

#endif
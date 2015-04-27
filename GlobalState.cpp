#include "GlobalState.hpp"

std::shared_ptr <MainWindow> GlobalState::MainWindow_;

MainWindow& GlobalState::GetMainWindow () {
	if (!MainWindow_) {
		MainWindow_.reset (new MainWindow());
	}
	return *MainWindow_;
}
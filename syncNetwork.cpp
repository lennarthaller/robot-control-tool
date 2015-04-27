#include "syncNetwork.hpp"

Worker::Worker() {
 mainWin = GlobalState::GetMainWindow ();
 connect(&timer, SIGNAL (timeout()), this, SLOT (doWork()));
 timer.start(500);
 }
 
 void Worker::doWork() {
 //Hier der auszuf�hrende quellcode
	//qDebug () << "Test";
	mainWin.SetText ("Test");
 }
#include "syncNetwork.hpp"

Worker::Worker() {
 connect(&timer, SIGNAL (timeout()), this, SLOT (doWork()));
 timer.start(500);
 }
 
 void Worker::doWork() {
 //Hier der auszuf�hrende quellcode
	 qDebug () << "Test";
 }
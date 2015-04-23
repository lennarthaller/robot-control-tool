#include "syncNetwork.hpp"

Worker::Worker() {
 connect(&timer, SIGNAL (timeout()), this, SLOT (doWork()));
 timer.start(10);
 }
 
 void Worker::doWork() {
 //Hier der auszuführende quellcode
 }
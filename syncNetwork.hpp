#ifndef SYNC_NETWORK_HPP
#define SYNC_NETWORK_HPP

#include <QtCore\QObject>
#include <QtCore\qtimer.h>
#include <iostream>
#include <QtCore\QtDebug>;

class Worker : public QObject
{
 Q_OBJECT
 
public:
	Worker(); 
 
private slots:
	void doWork();
 
private:
	QTimer timer;
};

#endif


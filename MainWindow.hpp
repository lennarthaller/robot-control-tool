#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui\QtGui>
#include <QPainter>
#include "SyncNetwork.hpp"
#include <math.h>
#define  UPDATEFREQUENCY 20

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
	void SetText (const QString text);

private slots:
    void Info();
	void ConnectToRobot ();
	void ShowScan();
	void ShowMotorData ();
	void ShowGeneralData ();
	void DisplayScan ();
	void DisplayMotorData ();
	void DisplayGeneralData ();

private:
    void createActions();
    void createMenus();
    void createDockWindow();

	double sind (double angle);
	double cosd (double angle);

	bool bConnected;

	QTimer timer;

	QLabel *label;
	//QPixmap *pixmap;
	QDockWidget *dock;

    QTextEdit *textEdit;

	QMenu *GeneralMenu;
	QAction *qconnectAct;
    QAction *aboutAct;
    QAction *quitAct;

	QMenu *Settings;
	QAction *qshowCDDAct;

	QMenu *ShowData;
	QAction *qshowScanAct;
	QAction *qshowMotorDataAct;
	QAction *qshowGeneralAct;

	SyncNetwork Network;
};

#endif
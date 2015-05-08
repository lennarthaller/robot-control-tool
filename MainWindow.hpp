#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui\QtGui>
#include <QPainter>
#include "SyncNetwork.hpp"
//#include "Render.hpp"
#define  UPDATEFREQUENCY 100

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

	bool bConnected;

	QTimer timer;

	QLabel *label;
	QPixmap pixmap;
	QDockWidget *dock;

    QTextEdit *textEdit;

	QMenu *GeneralMenu;
	QAction *qconnectAct;
    QAction *aboutAct;
    QAction *quitAct;

	QMenu *ShowData;
	QAction *qshowScanAct;
	QAction *qshowMotorDataAct;
	QAction *qshowGeneralAct;

	SyncNetwork Network;
};

#endif
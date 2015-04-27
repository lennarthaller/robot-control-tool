#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui\QtGui>
#include "SyncNetwork.hpp"

#define  UPDATEFREQUENCY 500

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
	void SetText (const QString text);

private slots:
    void Info();
	void ConnectToRobot ();
	void doWork();
	void ShowScan();
	void ShowMotorData ();
	void ShowGeneralData ();
	void DisplayScan ();
	void DisplayMotorData ();
	void DisplayGeneralData ();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createDockWindows();

	bool bConnected;

	QTimer timer;

    QTextEdit *textEdit;
    QListWidget *customerList;
    QListWidget *paragraphsList;

	QMenu *GeneralMenu;
	QAction *qconnectAct;
    QAction *aboutAct;
    QAction *quitAct;

	QMenu *ShowData;
	QAction *qshowScanAct;
	QAction *qshowMotorDataAct;
	QAction *qshowGeneralAct;

	QString msg;

	SyncNetwork Network;
};

#endif
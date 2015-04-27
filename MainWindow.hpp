#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui\QtGui>
#include "SyncNetwork.hpp"

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
    QAction *aboutAct;
    QAction *quitAct;
	QAction *qconnectAct;

	QString msg;

	SyncNetwork Network;
};

#endif
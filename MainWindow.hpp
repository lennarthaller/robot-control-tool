#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui\QtGui>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
	void SetText (const QString text);
	//QTextEdit* GetTextEdit () {return textEdit;}

private slots:
    void Info();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createDockWindows();

    QTextEdit *textEdit;
    QListWidget *customerList;
    QListWidget *paragraphsList;

    QMenu *GeneralMenu;
    QAction *aboutAct;
    QAction *quitAct;
};

#endif
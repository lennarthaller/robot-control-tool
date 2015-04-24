#include <QtGui\QtGui>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

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
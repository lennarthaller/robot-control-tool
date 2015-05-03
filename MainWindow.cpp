#include <QtGui\QtGui>

#include "mainwindow.hpp"

MainWindow::MainWindow()
{	
	bConnected = false;

    textEdit = new QTextEdit;
	textEdit->setReadOnly (true);
    setCentralWidget(textEdit);

    createActions();
	createMenus();

	if (Network.InitNetwork () == 1) {
		QMessageBox::critical(this, tr("System error"), tr("Failed to initialize the Network ressources!"));
	}

    setWindowTitle(tr("Robot Control Tool"));
}

void MainWindow::SetText (const QString text) {
	textEdit->setText (text);
}

void MainWindow::Info()
{
   QMessageBox::about(this, tr("About this program"),
				tr("This tool was programmed by "
				"<b> Lennart Haller </b> to control and debug "
                "the robot. "));
}

void MainWindow::createActions()
{
	qshowScanAct = new QAction(tr("&Show scan"), this);
	qshowScanAct->setStatusTip(tr("Show the LiDAR scan"));
	connect(qshowScanAct, SIGNAL(triggered()), this, SLOT(ShowScan()));

	qshowMotorDataAct = new QAction(tr("&Show motor data"), this);
	qshowMotorDataAct->setStatusTip(tr("Show motor data"));
	connect(qshowMotorDataAct, SIGNAL(triggered()), this, SLOT(ShowMotorData()));

	qshowGeneralAct = new QAction(tr("&Show general data"), this);
	qshowGeneralAct->setStatusTip(tr("Show general data"));
	connect(qshowGeneralAct, SIGNAL(triggered()), this, SLOT(ShowGeneralData()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&Info"), this);
    aboutAct->setStatusTip(tr("Show some information"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(Info()));

	qconnectAct = new QAction(tr("&Connect"), this);
	qconnectAct->setStatusTip(tr("Connect with the robot"));
	connect(qconnectAct, SIGNAL(triggered()), this, SLOT(ConnectToRobot()));
}

void MainWindow::createMenus()
{
	ShowData = menuBar()->addMenu(tr("&Show data"));
	ShowData->addAction (qshowScanAct);
	ShowData->addAction (qshowMotorDataAct);
	ShowData->addAction (qshowGeneralAct);

    GeneralMenu = menuBar()->addMenu(tr("&General"));
	GeneralMenu->addAction(qconnectAct);
    GeneralMenu->addAction(aboutAct);
    GeneralMenu->addAction(quitAct);
}

void MainWindow::ConnectToRobot () {
	if(bConnected == false) {
		if (Network.Connect () != 0) {
			QMessageBox::critical(this, tr("Network error"), tr("Failed to connect to the robot!"));
		}else{
			QMessageBox::information(this, tr("Connection status"), tr("You are now connected to the robot."));
				timer.start(UPDATEFREQUENCY);
				bConnected = true;
		}
	}else{
		QMessageBox::information(this, tr("Connection status"), tr("You are already connected to the robot."));
	}
}

void MainWindow::ShowScan () {
	if (bConnected == true) {
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayMotorData()));
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayGeneralData()));
		connect(&timer, SIGNAL (timeout()), this, SLOT (DisplayScan()));
	}else{
		QMessageBox::information(this, tr("Information"), tr("You need to connect to the robot first."));
	}
}

void MainWindow::ShowMotorData () {
		if (bConnected == true) {
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayScan()));
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayGeneralData()));
		connect(&timer, SIGNAL (timeout()), this, SLOT (DisplayMotorData()));
	}else{
		QMessageBox::information(this, tr("Information"), tr("You need to connect to the robot first."));
	}
}

void MainWindow::ShowGeneralData () {
		if (bConnected == true) {
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayScan()));
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayMotorData()));
		connect(&timer, SIGNAL (timeout()), this, SLOT (DisplayGeneralData()));
	}else{
		QMessageBox::information(this, tr("Information"), tr("You need to connect to the robot first."));
	}
}

void MainWindow::DisplayScan () {
	Network.UpdateData ();
	textEdit->clear();
}

void MainWindow::DisplayMotorData () {
	Network.UpdateData ();
	textEdit->clear();

	textEdit->setText ("Motor 3: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(*(Network.GetMotorPower()+2)));
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText ("          ||          Motor 2: "); //10 leerzeichen zwischen den | und Motor
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(*(Network.GetMotorPower()+1)));
	textEdit->moveCursor (QTextCursor::End);
	
	textEdit->append ("\n\n\n\n\n\n\n\n\n\n\n");

	textEdit->insertPlainText ("Motor 1: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(*(Network.GetMotorPower())));
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText ("                       Motor 4: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(*(Network.GetMotorPower()+3)));
	textEdit->moveCursor (QTextCursor::End);

	/*textEdit->setText ("Ticks 2 "); textEdit->append (QString::number(*(Network.GetOdometryTicks()+1)));
	textEdit->append ("\nMotor 2 "); textEdit->append (); */

}

void MainWindow::DisplayGeneralData () {
	Network.UpdateData ();
	textEdit->clear();

	textEdit->setText ("Operating Voltage "); 
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.GetVoltage()));
	textEdit->moveCursor (QTextCursor::End);
	
	textEdit->append ("\nMain loop ticks per second "); 
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.GetLoopTicks()));
	textEdit->moveCursor (QTextCursor::End);
}


/*void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customerList = new QListWidget(dock);
    customerList->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(customerList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("Paragraphs"), this);
    paragraphsList = new QListWidget(dock);
    paragraphsList->addItems(QStringList()
            << "Thank you for your payment which we have received today."
            << "Your order has been dispatched and should be with you "
               "within 28 days."
            << "We have dispatched those items that were in stock. The "
               "rest of your order will be dispatched once all the "
               "remaining items have arrived at our warehouse. No "
               "additional shipping charges will be made."
            << "You made a small overpayment (less than $5) which we "
               "will keep on account for you, or return at your request."
            << "You made a small underpayment (less than $1), but we have "
               "sent your order anyway. We'll add this underpayment to "
               "your next bill."
            << "Unfortunately you did not send enough money. Please remit "
               "an additional $. Your order will be dispatched as soon as "
               "the complete amount has been received."
            << "You made an overpayment (more than $5). Do you wish to "
               "buy more items, or should we return the excess to you?");
    dock->setWidget(paragraphsList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(customerList, SIGNAL(currentTextChanged(QString)),
            this, SLOT(insertCustomer(QString)));
    connect(paragraphsList, SIGNAL(currentTextChanged(QString)),
            this, SLOT(addParagraph(QString)));
} */
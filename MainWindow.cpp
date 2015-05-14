#include <QtGui\QtGui>

#include "mainwindow.hpp"

MainWindow::MainWindow()
{	
	bConnected = false;

    textEdit = new QTextEdit;
	textEdit->setReadOnly (true);
    setCentralWidget(textEdit);

	//pixmap = new QPixmap (800, 800);
	label = new QLabel(this);

	if (Network.InitNetwork () == 1) {
		QMessageBox::critical(this, tr("System error"), tr("Failed to initialize the Network ressources!"));
	}

	createActions();
	createMenus();
	createDockWindow ();

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

	qshowCDDAct = new QAction(tr("&Show CDD"), this);
	qshowCDDAct->setStatusTip(tr("Show Calculated driving direction"));
	qshowCDDAct->setCheckable(true);
	connect (qshowCDDAct, SIGNAL (changed()), this, SLOT (toggle()));

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

	Settings = menuBar()->addMenu (tr("&Settings"));
	Settings->addAction (qshowCDDAct);

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
		dock->show();
	}else{
		QMessageBox::information(this, tr("Information"), tr("You need to connect to the robot first."));
	}
}

void MainWindow::ShowMotorData () {
		if (bConnected == true) {
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayScan()));
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayGeneralData()));
		connect(&timer, SIGNAL (timeout()), this, SLOT (DisplayMotorData()));
		dock->hide();
	}else{
		QMessageBox::information(this, tr("Information"), tr("You need to connect to the robot first."));
	}
}

void MainWindow::ShowGeneralData () {
		if (bConnected == true) {
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayScan()));
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayMotorData()));
		connect(&timer, SIGNAL (timeout()), this, SLOT (DisplayGeneralData()));
		dock->hide();
	}else{
		QMessageBox::information(this, tr("Information"), tr("You need to connect to the robot first."));
	}
}

void MainWindow::DisplayScan () {
	Network.UpdateData ();

	if (Network.GetWasUpdated () == true) {

	textEdit->clear();

	for (int i=0; i<100; i++) {
		textEdit->insertPlainText ("Messung ");
		textEdit->moveCursor (QTextCursor::End);
		textEdit->insertPlainText (QString::number(i));
		textEdit->moveCursor (QTextCursor::End);
		textEdit->insertPlainText (":   ");
		textEdit->moveCursor (QTextCursor::End);
		textEdit->insertPlainText (QString::number(*(Network.GetScannerData()+i)));
		textEdit->moveCursor (QTextCursor::End);
		textEdit->insertPlainText ("\n");
		textEdit->moveCursor (QTextCursor::End);
	}

	QPixmap *pixmap = new QPixmap (800, 800);
	QPainter *paint = new QPainter (pixmap);
	QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);

	double x, y;

	for (int i=0; i<100;i++) {
		x = ((*(Network.GetScannerData()+i))/23 * cosd (1.8 * i))-4; //divide by 23
		y = ((*(Network.GetScannerData()+i))/23 * sind (1.8 * i))-4;
		paint->fillRect (400 + static_cast<int>(x), 600 - static_cast<int>(y), 8, 8, QColor (0,0,0)); 
	}

	if (qshowCDDAct->isChecked() == true) {//Draw calculated driving direction
	paint->setPen (pen);
	x = (cosd (Network.GetCalculatedDrivingDirection()+90) * 200) / 23;
	y = (sind (Network.GetCalculatedDrivingDirection()+90) * 200) / 23;
	paint->drawLine (400, 600, x+400, 600-y);
	}

	label->setPixmap(*pixmap);
	Network.SetWasUpdated (false);
	}
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
	
	textEdit->append ("Odometry 3: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(*(Network.GetOdometryTicks()+2)));
	textEdit->insertPlainText ("                 Odometry 4: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(*(Network.GetOdometryTicks()+3)));
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

	textEdit->append ("Odometry 2: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(*(Network.GetOdometryTicks()+1)));
	textEdit->insertPlainText ("                 Odometry 1: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(*(Network.GetOdometryTicks())));
	textEdit->moveCursor (QTextCursor::End);
}

void MainWindow::DisplayGeneralData () {
	Network.UpdateData ();
	textEdit->clear();

	textEdit->setText ("Operating Voltage "); 
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.GetVoltage()));
	textEdit->moveCursor (QTextCursor::End);
	
	textEdit->append ("Main loop ticks per second "); 
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.GetLoopTicks()));
	textEdit->moveCursor (QTextCursor::End);

	textEdit->append ("\n\nCalculated driving direction "); 
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.GetCalculatedDrivingDirection()));
	textEdit->moveCursor (QTextCursor::End);
}


void MainWindow::createDockWindow() {
    dock = new QDockWidget(tr("LiDAR scan"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(label);
    addDockWidget(Qt::RightDockWidgetArea, dock);
	
	dock->hide();
} 

double MainWindow::sind(double angle)
{
    double angleradians = angle * M_PI / 180.0f;
    return sin(angleradians) * 180.0f / M_PI;
}

double MainWindow::cosd(double angle)
{
    double angleradians = angle * M_PI / 180.0f;
    return cos(angleradians) * 180.0f / M_PI;
}
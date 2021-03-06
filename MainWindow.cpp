#include <QtGui\QtGui>

#include "mainwindow.hpp"

MainWindow::MainWindow()
{	
	bConnected = false;

    textEdit = new QTextEdit;
	textEdit->setReadOnly (true);
    setCentralWidget(textEdit);

	label = new QLabel(this);

	if (Network.InitNetwork () == 1) {
		QMessageBox::critical(this, tr("System error"), tr("Failed to initialize the Network ressources!"));
	}

	createActions();
	createMenus();
	createDockWindow ();

	pixmap = new QPixmap (1000, 1000);
	m_nNetworkUpdatesperSecond = 0;

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

	qshowOriginOfScanAct = new QAction(tr("&Show origin of scan"), this);
	qshowOriginOfScanAct->setStatusTip(tr("Display the origin of the laser scan"));
	qshowOriginOfScanAct->setCheckable(true);
	connect (qshowOriginOfScanAct, SIGNAL (changed()), this, SLOT (toggle()));

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
	Settings->addAction (qshowOriginOfScanAct);

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
				UpdateTimer.start(UPDATEFREQUENCY);
				NetworkUpdateCounterTimer.start(1000);
				connect(&UpdateTimer, SIGNAL (timeout()), this, SLOT (UpdateData()));
				connect(&NetworkUpdateCounterTimer, SIGNAL (timeout()), this, SLOT (CountNetworkUpdates()));
				bConnected = true;
		}
	}else{
		QMessageBox::information(this, tr("Connection status"), tr("You are already connected to the robot."));
	}
}

void MainWindow::ShowScan () {
	if (bConnected == true) {
		timer.start(50);
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
		timer.start(20);
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
		timer.start(20);
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayScan()));
		disconnect(&timer, SIGNAL (timeout()), this, SLOT (DisplayMotorData()));
		connect(&timer, SIGNAL (timeout()), this, SLOT (DisplayGeneralData()));
		dock->hide();
	}else{
		QMessageBox::information(this, tr("Information"), tr("You need to connect to the robot first."));
	}
}

void MainWindow::DisplayMotorData () {
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

	textEdit->append ("\n\n\n\n\n\n\n");

	textEdit->insertPlainText ("X Pos from Odometry: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.OdometryPosition()->nX));
	textEdit->moveCursor (QTextCursor::End);
	
	textEdit->append ("Y Pos from Odometry: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.OdometryPosition()->nY));
	textEdit->moveCursor (QTextCursor::End);
	
	textEdit->append ("Theta from Odometry: ");
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.OdometryPosition()->fTheta));
	textEdit->moveCursor (QTextCursor::End);
}

void MainWindow::DisplayGeneralData () {
	textEdit->clear();

	textEdit->setText ("Operating Voltage: "); 
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.GetVoltage()));
	textEdit->moveCursor (QTextCursor::End);
	
	textEdit->append ("Main loop ticks per second: "); 
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(Network.GetLoopTicks()));
	textEdit->moveCursor (QTextCursor::End);

	textEdit->append ("Network Updates per second: "); 
	textEdit->moveCursor (QTextCursor::End);
	textEdit->insertPlainText (QString::number(m_nNetworkUpdatesperSecond));
	textEdit->moveCursor (QTextCursor::End);

	textEdit->append ("\n\nCalculated driving direction: "); 
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

void MainWindow::DisplayScan () {
	if (Network.GetWasUpdated() == true) {

		textEdit->clear();
		/*
		for (int i=0; i<271; i++) {
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
		 */
		
		pixmap->fill (QColor (160, 160, 160, 255));
		QPainter *paint = new QPainter (pixmap);

		double x, y;

		for (int i=0; i<271;i++) { //draw data points
			if (*(Network.GetScannerData()+i) != 0) { //only draw the data point if its != 0
				x = (((*(Network.GetScannerData()+i)) * cosd (i-45)) / 23)-4; //divide by 23
				y = (((*(Network.GetScannerData()+i)) * sind (i-45)) / 23)-4;
				paint->fillRect (500 + static_cast<int>(x), 800 - static_cast<int>(y), 8, 8, QColor (0,0,0)); 
			}
		}

		if (qshowOriginOfScanAct->isChecked() == true) {//Draw origin if selected by the user
			paint->fillRect (500 -8, 800 - 8, 16, 16, QColor (255,0,0)); 
		}

		if (qshowCDDAct->isChecked() == true) {//Draw calculated driving direction if selected by the user
			QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);

			paint->setPen (pen);
			x = (cosd (Network.GetCalculatedDrivingDirection()+90) * 10); // * 8.7
			y = (sind (Network.GetCalculatedDrivingDirection()+90) * 10);
			paint->drawLine (500, 800, x+500, 800-y);
		}

		label->clear();
	    delete paint;
		label->setPixmap(*pixmap);
		Network.SetWasUpdated (false);

	}
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

void  MainWindow::UpdateData () {
	Network.UpdateData ();
}

void MainWindow::CountNetworkUpdates () {
	m_nNetworkUpdatesperSecond = Network.GetUpdateCounter ();
	Network.ResetUpdateCounter ();
}
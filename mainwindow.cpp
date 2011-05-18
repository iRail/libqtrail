//
// Configuration
//

// Includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), mUi(new Ui::MainWindow)
{
    // Construct UI
    mUi->setupUi(this);

    // API settings
    mSettings = new QSettings();
    mSettings->setValue("client/id", "libqtrail testing application");
    mSettings->setValue("client/version", "0.1");

    // Station model
    mStations = new StationList(this);
    connect(mStations, SIGNAL(success()), this, SLOT(success()));
    connect(mStations, SIGNAL(failure(Exception)), this, SLOT(failure(Exception)));
    mUi->lstStations->setModel(mStations);
}

MainWindow::~MainWindow()
{
    delete mUi;
}


//
// UI slots
//

void MainWindow::on_btnStationsClear_clicked()
{
    mStations->clear();
}

void MainWindow::on_btnStationsFetch_clicked()
{
    loadStations();
}

void MainWindow::on_btnDeparturesClear_clicked()
{
    mDepartures->clear();
}

void MainWindow::on_lstStations_activated(const QModelIndex &index)
{
    if (index.isValid())
        loadDepartures(mStations->object(index));
}


//
// Model interactions
//

void MainWindow::loadStations()
{
    // Fetch data
    mStations->fetch();
}

void MainWindow::loadDepartures(Station *iStation)
{
    // Set-up model
    mDepartures = new DepartureList(iStation->id());
    connect(mDepartures, SIGNAL(success()), this, SLOT(success()));
    connect(mDepartures, SIGNAL(failure(Exception)), this, SLOT(failure(Exception)));
    mUi->lstDepartures->setModel(mDepartures);

    // Fetch data
    mDepartures->fetch();
}


//
// Model slots
//


void MainWindow::success()
{
    qDebug() << "* Success";
}

void MainWindow::failure(const Exception& iException)
{
    qDebug() << "! Failure: " << iException.toString();
}

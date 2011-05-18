//
// Configuration
//

// Includes
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete mUi;
}


//
// UI slots
//

void MainWindow::on_btnClear_clicked()
{

}

void MainWindow::on_btnFetch_clicked()
{

}

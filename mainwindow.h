//
// Configuration
//

// Include guard
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Includes
#include <QMainWindow>

// UI handling
namespace Ui
{
    class MainWindow;
}

namespace iRail
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        // Construction and destruction
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        // UI slots

    private slots:
        void on_btnClear_clicked();

        void on_btnFetch_clicked();

    private:
        // UI members
        Ui::MainWindow *mUi;

        // List data

    };
}

#endif // MAINWINDOW_H

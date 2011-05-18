//
// Configuration
//

// Include guard
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Includes
#include <QMainWindow>
#include "api/data/station.h"
#include "api/data/departure.h"
#include "api/container/stationlist.h"
#include "api/container/departurelist.h"

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
        void on_btnStationsClear_clicked();
        void on_btnStationsFetch_clicked();
        void on_btnDeparturesClear_clicked();
        void on_lstStations_activated(const QModelIndex &index);

        // Functionality
    private:
        void loadStations();
        void loadDepartures(Station* iStation);

        // Model slots
    private slots:
        void success();
        void failure(const Exception& iException);

    private:
        // UI members
        Ui::MainWindow *mUi;

        // List data
        StationList* mStations;
        DepartureList* mDepartures;

        // Other
        QSettings* mSettings;
    };
}

#endif // MAINWINDOW_H

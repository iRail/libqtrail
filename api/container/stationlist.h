//
// Configuration
//

// Include guard
#ifndef STATIONLIST_H
#define STATIONLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QHash>
#include "api/exception.h"
#include "api/requesthelper.h"
#include "api/data/station.h"
#include "api/container.h"

namespace iRail
{
    class StationList : public Container<Station>, private RequestHelper
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StationList(QObject* iParent = 0);
        ~StationList();

    public:
        // Basic I/O
        Station const* get(const Station::Id& iId);

    public:
        // Data request methods
        void fetch();

    signals:
        // Data reply signals
        void success();
        void failure(const Exception& iException);

        // Data processing methods
    private slots:
        void process();

    private:
        // Member data
        QDateTime mTimestamp;
    };
}

#endif // STATIONLIST_H

//
// Configuration
//

// Include guard
#ifndef LIVEBOARD_H
#define LIVEBOARD_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QHash>
#include "api/exception.h"
#include "api/requesthelper.h"
#include "api/data/station.h"
#include "api/data/departure.h"
#include "api/container.h"

namespace iRail
{
    class DepartureList : public Container<Departure>
    {
    Q_OBJECT
    public:
        // Construction and destruction
        DepartureList(const Station::Id& iStationId, QObject* iParent = 0);
        ~DepartureList();

        // Basic I/O
    public:
        Station::Id const* stationId() const;

        // Data request methods
        void fetch();
        void fetch(const QDateTime& iDatetime);

    signals:
        // Data reply signals
        void success();
        void failure(const Exception& iException);

        // Data processing methods
    private slots:
        void process();

    private:
        // Member data
        RequestHelper mRequestHelper;
        QDateTime mTimestamp;
        Station::Id mStationId;
    };
}

#endif // LIVEBOARD_H

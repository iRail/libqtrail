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
#include <QAbstractItemModel>
#include "api/data/station.h"

namespace iRail
{
    class StationList : public QAbstractItemModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StationList();
        ~StationList();

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const StationList& iStationList);
        friend QDataStream &operator>>(QDataStream& iStream, StationList& iStationList);

    private:
        QDateTime mTimestamp;
        POI mDeparture, mArrival;
        QList<Journey> mConnections;
    };

    QDataStream &operator<<(QDataStream& iStream, const StationList& iStationList);
    QDataStream &operator>>(QDataStream& iStream, StationList& iStationList);
}

Q_DECLARE_METATYPE(iRail::StationList)

#endif // STATIONLIST_H

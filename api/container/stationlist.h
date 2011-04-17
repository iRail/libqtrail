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
#include <QAbstractListModel>
#include "api/data/station.h"

namespace iRail
{
    class StationList : public QAbstractListModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StationList(QObject* iParent = 0);
        ~StationList();

        // Model interface
        int rowCount(const QModelIndex& iParent = QModelIndex()) const;
        QVariant data(const QModelIndex& iIndex, int iRole = Qt::DisplayRole) const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const StationList& iStationList);
        friend QDataStream &operator>>(QDataStream& iStream, StationList& iStationList);

    private:
        Q_DISABLE_COPY(StationList);
        QDateTime mTimestamp;
        POI mDeparture, mArrival;
        QList<Station*> mStations;
    };

    QDataStream &operator<<(QDataStream& iStream, const StationList& iStationList);
    QDataStream &operator>>(QDataStream& iStream, StationList& iStationList);
}

Q_DECLARE_METATYPE(iRail::StationList)

#endif // STATIONLIST_H

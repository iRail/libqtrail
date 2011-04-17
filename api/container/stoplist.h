//
// Configuration
//

// Include guard
#ifndef STOPLIST_H
#define STOPLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QAbstractItemModel>
#include "api/data/vehicle.h"
#include "api/data/connection.h"
#include "api/data/poi.h"

namespace iRail
{
    class StopList : public QAbstractItemModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StopList(const Vehicle& iVehicle);
        StopList(const Connection& iConnection);
        ~StopList();

        // Basic I/O
        Vehicle vehicle() const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const StopList& iStopList);
        friend QDataStream &operator>>(QDataStream& iStream, StopList& iStopList);

    private:
        Vehicle mVehicle;
        Station mDeparture, mArrival;
        bool mLimited;
    };

    QDataStream &operator<<(QDataStream& iStream, const StopList& iStopList);
    QDataStream &operator>>(QDataStream& iStream, StopList& iStopList);
}

Q_DECLARE_METATYPE(iRail::StopList)

#endif // STOPLIST_H

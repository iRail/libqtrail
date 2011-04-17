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
#include <QAbstractItemModel>
#include "api/data/station.h"
#include "api/data/departure.h"

namespace iRail
{
    class DepartureList : public QAbstractItemModel
    {
    Q_OBJECT
    public:
        // Construction and destruction
        DepartureList(const Station& iStation);

        // Basic I/O
        QString station() const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const DepartureList& iDepartureList);
        friend QDataStream &operator>>(QDataStream& iStream, DepartureList& iDepartureList);

    private:
        QDateTime mTimestamp;
        Station mStation;
        QList<Departure> mDepartures;
    };

    QDataStream &operator<<(QDataStream& iStream, const DepartureList& iDepartureList);
    QDataStream &operator>>(QDataStream& iStream, DepartureList& iDepartureList);
}

Q_DECLARE_METATYPE(iRail::DepartureList)

#endif // LIVEBOARD_H

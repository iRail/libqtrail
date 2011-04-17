//
// Configuration
//

// Include guard
#ifndef DEPARTURE_H
#define DEPARTURE_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDebug>
#include "poi.h"

namespace iRail
{
    class Departure : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(QString vehicle READ vehicle CONSTANT)
    Q_PROPERTY(POI poi READ poi CONSTANT)
    public:
        // Construction and destruction
        Departure(const QString& iVehicle, const POI& iPOI);

        // Basic I/O
        QString vehicle() const;
        POI poi() const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const Departure& iDeparture);
        friend QDataStream &operator>>(QDataStream& iStream, Departure& iDeparture);

    private:
        QString mVehicle;
        POI mPOI;
    };

    QDataStream &operator<<(QDataStream& iStream, const Departure& iDeparture);
    QDataStream &operator>>(QDataStream& iStream, Departure& iDeparture);
}

Q_DECLARE_METATYPE(iRail::Departure)

#endif // DEPARTURE_H

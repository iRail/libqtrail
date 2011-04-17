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
#include "vehicle.h"

namespace iRail
{
    class Departure : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(QString vehicle READ vehicle CONSTANT)
    Q_PROPERTY(POI poi READ poi CONSTANT)
    public:
        // Construction and destruction
        Departure(Vehicle const* iVehicle, POI const* iPOI);

        // Auxiliary structures
        enum Roles {
          VehicleRole = Qt::UserRole+1,
          POIRole
        };

        // Basic I/O
        Vehicle const* vehicle() const;
        POI const* poi() const;

        // Operators
        friend bool operator==(const Departure& lhs, const Departure& rhs);
        friend bool operator||(const Departure& lhs, const Departure& rhs);
        friend QDataStream& operator<<(QDataStream& iStream, const Departure& iDeparture);
        friend QDataStream& operator>>(QDataStream& iStream, Departure& iDeparture);

    private:
        Q_DISABLE_COPY(Departure);
        Vehicle const* mVehicle;
        POI const* mPOI;
    };

    bool operator==(const Departure& lhs, const Departure& rhs);
    bool operator||(const Departure& lhs, const Departure& rhs);
    QDataStream& operator<<(QDataStream& iStream, const Departure& iDeparture);
    QDataStream& operator>>(QDataStream& iStream, Departure& iDeparture);
}

Q_DECLARE_METATYPE(iRail::Departure)

#endif // DEPARTURE_H

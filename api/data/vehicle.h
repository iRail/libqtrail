//
// Configuration
//

// Include guard
#ifndef VEHICLE_H
#define VEHICLE_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QPair>
#include <QDebug>
#include <QDateTime>
#include "station.h"
#include "auxiliary/location.h"

namespace iRail
{
    class Vehicle : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Id id READ id CONSTANT)
    Q_PROPERTY(Location location READ location WRITE setLocation)
    public:
        // Auxiliary structures
        typedef QString Id;
        enum Roles
        {
          IdRole = Qt::UserRole+1,
          LocationRole
        };

        // Construction and destruction
        Vehicle(Id iId);
        ~Vehicle();

        // Basic I/O
        Id id() const;
        Location const* location() const;
        void setLocation(Location const* iLocation);

        // Operators
        friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
        friend bool operator||(const Vehicle& lhs, const Vehicle& rhs);
        friend QDataStream& operator<<(QDataStream& iStream, const Vehicle& iVehicle);
        friend QDataStream& operator>>(QDataStream& iStream, Vehicle& iVehicle);

    private:
        Q_DISABLE_COPY(Vehicle);
        id mId;
        Location const* mLocation;
    };

    bool operator==(const Vehicle& lhs, const Vehicle& rhs);
    bool operator||(const Vehicle& lhs, const Vehicle& rhs);
    QDataStream& operator<<(QDataStream& iStream, const Vehicle& iVehicle);
    QDataStream& operator>>(QDataStream& iStream, Vehicle& iVehicle);
}

Q_DECLARE_METATYPE(iRail::Vehicle)
Q_DECLARE_METATYPE(iRail::Vehicle::Id)

#endif // STATION_H

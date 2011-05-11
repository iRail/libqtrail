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
#include <QVariant>
#include <QDateTime>
#include "station.h"
#include "auxiliary/location.h"

namespace iRail
{
    class Vehicle
    {
    Q_OBJECT
    Q_PROPERTY(Location location READ location WRITE setLocation)
    public:
        // Auxiliary structures
        struct Id
        {
            QString guid;

            // Operators
            friend inline unsigned int qHash(const Vehicle::Id& tVehicleId);
            friend bool operator==(const Vehicle::Id& lhs, const Vehicle::Id& rhs);
        };
        enum Roles
        {
            GUIDRole = Qt::UserRole+1,
            LocationRole
        };

        // Construction and destruction
        Vehicle(Id iId);
        ~Vehicle();

        // Basic I/O
        QVariant field(int iRole) const;
        Id const* id() const;
        Location const* location() const;
        void setLocation(const Location& iLocation);

        // Operators
        friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
        Vehicle& operator=(const Vehicle& other);

    private:
        Id mId;
        Location mLocation;
    };

    bool operator==(const Vehicle& lhs, const Vehicle& rhs);
    inline unsigned int qHash(const Vehicle::Id& tVehicleId);
    bool operator==(const Vehicle::Id& lhs, const Vehicle::Id& rhs);
}

Q_DECLARE_METATYPE(const iRail::Vehicle*)

#endif // STATION_H

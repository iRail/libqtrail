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
#include <QHash>
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
        const Location& location() const;
        void setLocation(const Location& iLocation);

        // Operators
        friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
        friend Vehicle& operator=(const Vehicle& other);

    private:
        Q_DISABLE_COPY(Vehicle);
        Id mId;
        Location mLocation;
    };

    bool operator==(const Vehicle& lhs, const Vehicle& rhs);
    Vehicle& operator=(const Vehicle& other);
}

Q_DECLARE_METATYPE(iRail::Vehicle)
Q_DECLARE_METATYPE(iRail::Vehicle::Id)

#endif // STATION_H

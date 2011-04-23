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
#include "api/data.h"
#include <QDateTime>
#include "station.h"
#include "auxiliary/location.h"

namespace iRail
{
    class Vehicle : public Data
    {
    Q_OBJECT
    Q_PROPERTY(Location location READ location WRITE setLocation)
    public:
        // Auxiliary structures
        struct Id : Data::Id
        {
            QString guid;
        };
        enum Roles
        {
            IdRole = Qt::UserRole+1,
            LocationRole
        };

        // Construction and destruction
        Vehicle(Id iId);
        ~Vehicle();

        // Basic I/O
        Id& id() const;
        const Location& location() const;
        void setLocation(const Location& iLocation);

        // Operators
        friend bool operator==(const Vehicle& lhs, const Vehicle& rhs);
        Vehicle& operator=(const Vehicle& other);

    private:
        Id mId;
        Location mLocation;
    };

    bool operator==(const Vehicle& lhs, const Vehicle& rhs);
}

Q_DECLARE_METATYPE(iRail::Vehicle::Id)

#endif // STATION_H

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
        struct Id : AbstractId
        {
            QString guid;

            // Operator implementation
            bool equals(const AbstractId& id) const;
            unsigned int hash() const;
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

        // Operator implementation
        bool equals(const Data& data) const;
        Data& assign(const Data& data);

    private:
        Id mId;
        Location mLocation;
    };
}

Q_DECLARE_METATYPE(const iRail::Vehicle*)

#endif // STATION_H

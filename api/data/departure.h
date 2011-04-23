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
#include "stop.h"
#include "vehicle.h"

namespace iRail
{
    class Departure : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Id id READ id CONSTANT)
    public:
        // Construction and destruction
        Departure(Id iId);

        // Auxiliary structure
        struct Id
        {
            Stop const* origin;
            Vehicle const* vehicle;
        };
        enum Roles
        {
          VehicleRole = Qt::UserRole+1,
          StopRole
        };

        // Basic I/O
        Id id() const;

        // Operators
        friend bool operator==(const Departure& lhs, const Departure& rhs);
        friend bool operator||(const Departure& lhs, const Departure& rhs);
        friend QDataStream& operator<<(QDataStream& iStream, const Departure& iDeparture);
        friend QDataStream& operator>>(QDataStream& iStream, Departure& iDeparture);

    private:
        Q_DISABLE_COPY(Departure);
        Id mId;
    };

    bool operator==(const Departure& lhs, const Departure& rhs);
    bool operator||(const Departure& lhs, const Departure& rhs);
    QDataStream& operator<<(QDataStream& iStream, const Departure& iDeparture);
    QDataStream& operator>>(QDataStream& iStream, Departure& iDeparture);
}

Q_DECLARE_METATYPE(iRail::Departure)
Q_DECLARE_METATYPE(iRail::Departure::Id)

#endif // DEPARTURE_H

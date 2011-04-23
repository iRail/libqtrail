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
#include <QHash>
#include "stop.h"
#include "vehicle.h"

namespace iRail
{
    class Departure : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Id id READ id CONSTANT)
    Q_PROPERTY(uint delay READ relay WRITE setDelay)
    public:
        // Construction and destruction
        Departure(Id iId);

        // Auxiliary structure
        struct Id
        {
            Stop const* origin;
            Vehicle const* vehicle;
            friend inline unsigned int qHash(const Departure::Id& iDepartureId);
            friend bool operator==(const Departure::Id& lhs, const Departure::Id& rhs);
        };
        enum Roles
        {
            VehicleRole = Qt::UserRole+1,
            StopRole,
            DelayRole
        };

        // Basic I/O
        Id id() const;
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);

        // Operators
        friend bool operator==(const Departure& lhs, const Departure& rhs);

    private:
        Q_DISABLE_COPY(Departure);
        Id mId;
        unsigned int mDelay;
    };

    bool operator==(const Departure& lhs, const Departure& rhs);
    inline unsigned int qHash(const Departure::Id& iDepartureId);
}

Q_DECLARE_METATYPE(iRail::Departure)
Q_DECLARE_METATYPE(iRail::Departure::Id)

#endif // DEPARTURE_H

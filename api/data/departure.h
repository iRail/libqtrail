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
#include <QVariant>
#include "stop.h"
#include "vehicle.h"

namespace iRail
{
    class Departure : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(uint delay READ delay WRITE setDelay)
    public:
        // Auxiliary structure
        struct Id
        {
            Stop const* origin;
            Vehicle const* vehicle;

            // Operators
            friend inline unsigned int qHash(const Departure::Id& iDepartureId);
            friend bool operator==(const Departure::Id& lhs, const Departure::Id& rhs);
        };
        enum Roles
        {
            VehicleRole = Qt::UserRole+1,
            OriginRole,
            DelayRole
        };

        // Construction and destruction
        Departure(Id iId);

        // Basic I/O
        QVariant field(int iRole) const;
        Id const* id() const;
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);

        // Operators
        friend bool operator==(const Departure& lhs, const Departure& rhs);
        Departure& operator=(const Departure& other);

    private:
        Id mId;
        unsigned int mDelay;
    };

    bool operator==(const Departure& lhs, const Departure& rhs);
    inline unsigned int qHash(const Departure::Id& iDepartureId)
    {
        return qHash(*iDepartureId.origin->id()) ^ qHash(*iDepartureId.vehicle->id());
    }
    bool operator==(const Departure::Id& lhs, const Departure::Id& rhs);
}

#endif // DEPARTURE_H

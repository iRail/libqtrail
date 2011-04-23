//
// Configuration
//

// Include guard
#ifndef CONNECTION_H
#define CONNECTION_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QHash>
#include "stop.h"
#include "station.h"
#include "vehicle.h"

namespace iRail
{
    class Connection : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Id id READ id CONSTANT)
    Q_PROPERTY(Station terminus READ terminus WRITE setTerminus)
    Q_PROPERTY(Vehicle vehicle READ vehicle WRITE setVehicle)
    Q_PROPERTY(uint delay READ relay WRITE setDelay)
    public:
        // Construction and destruction
        Connection(Id iId);

        // Auxiliary structures
        struct Id
        {
            Stop const* origin;
            Stop const* destination;
            friend inline unsigned int qHash(const Connection::Id& iConnection);
            friend bool operator==(const Connection::Id& lhs, const Connection::Id& rhs);
        };
        enum Roles
        {
            DepartureRole = Qt::UserRole+1,
            ArrivalRole,
            TerminusRole,
            VehicleRole,
            DelayRole
        };

        // Basic I/O
        Id id() const;
        Station const* terminus() const;
        void setTerminus(Station const* iTerminus);
        Vehicle const* vehicle() const;
        void setVehicle(Vehicle const* iVehicle);
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);

        // Operators
        friend bool operator==(const Connection& lhs, const Connection& rhs);

    private:
        Q_DISABLE_COPY(Connection);
        Id mId;
        Station const* mTerminus;
        Vehicle const* mVehicle;
        unsigned int mDelay;
    };

    bool operator==(const Connection& lhs, const Connection& rhs);
    inline unsigned int qHash(const Connection::Id& iConnection);
}

Q_DECLARE_METATYPE(iRail::Connection)
Q_DECLARE_METATYPE(iRail::Connection::Id)

#endif // CONNECTION_H

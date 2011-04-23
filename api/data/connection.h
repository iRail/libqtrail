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
#include "api/data.h"
#include "stop.h"
#include "station.h"
#include "vehicle.h"

namespace iRail
{
    class Connection : public Data
    {
    Q_OBJECT
    Q_PROPERTY(Station terminus READ terminus)
    Q_PROPERTY(Vehicle vehicle READ vehicle)
    Q_PROPERTY(uint delay READ delay WRITE setDelay)
    public:
        // Auxiliary structures
        struct Id : Data::Id
        {
            Stop const* origin;
            Stop const* destination;
            friend inline unsigned int qHash(const Connection::Id& iConnection);
            friend bool operator==(const Connection::Id& lhs, const Connection::Id& rhs);
        };
        enum Roles
        {
            OriginRole = Qt::UserRole+1,
            DestinationRole,
            TerminusRole,
            VehicleRole,
            DelayRole
        };

        // Construction and destruction
        Connection(Id iId);

        // Basic I/O
        Id& id() const;
        Station const* terminus() const;
        void setTerminus(Station const* iTerminus);
        Vehicle const* vehicle() const;
        void setVehicle(Vehicle const* iVehicle);
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);

        // Operators
        friend bool operator==(const Connection& lhs, const Connection& rhs);
        Connection& operator=(const Connection& other);

    private:
        Id mId;
        Station const* mTerminus;
        Vehicle const* mVehicle;
        unsigned int mDelay;
    };

    bool operator==(const Connection& lhs, const Connection& rhs);
    inline unsigned int qHash(const Connection::Id& iConnection);
    bool operator==(const Connection::Id& lhs, const Connection::Id& rhs);
}

Q_DECLARE_METATYPE(iRail::Connection::Id)

#endif // CONNECTION_H

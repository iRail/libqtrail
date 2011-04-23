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

            // Operator implementation
            bool equals(const Data::Id& id) const;
            unsigned int hash() const;
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

        // Operator implementation
        bool equals(const Data& data) const;
        Data& assign(const Data& data);

    private:
        Id mId;
        Station const* mTerminus;
        Vehicle const* mVehicle;
        unsigned int mDelay;
    };
}

Q_DECLARE_METATYPE(iRail::Connection::Id)

#endif // CONNECTION_H

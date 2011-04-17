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
#include "poi.h"
#include "station.h"
#include "vehicle.h"

namespace iRail
{
    class Connection : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(POI departure READ departure CONSTANT)
    Q_PROPERTY(POI arrival READ arrival CONSTANT)
    Q_PROPERTY(Station terminus READ terminus WRITE setTerminus)
    Q_PROPERTY(Vehicle vehicle READ vehicle WRITE setVehicle)
    public:
        // Construction and destruction
        Connection(POI const* iDeparture, POI const* iArrival);

        // Auxiliary structures
        enum Roles {
          DepartureRole = Qt::UserRole+1,
          ArrivalRole,
          TerminusRole,
          VehicleRole
        };

        // Basic I/O
        POI const* departure() const;
        POI const* arrival() const;
        Station const* terminus() const;
        void setTerminus(Station const* iTerminus);
        Vehicle const* vehicle() const;
        void setVehicle(Vehicle const* iVehicle);

        // Operators
        friend bool operator==(const Connection& lhs, const Connection& rhs);
        friend bool operator||(const Connection& lhs, const Connection& rhs);
        friend QDataStream& operator<<(QDataStream& iStream, const Connection& iConnection);
        friend QDataStream& operator>>(QDataStream& iStream, Connection& iConnection);

    private:
        Q_DISABLE_COPY(Connection);
        POI const* mDeparture;
        POI const* mArrival;
        Station const* mTerminus;
        Vehicle const* mVehicle;
    };

    bool operator==(const Connection& lhs, const Connection& rhs);
    bool operator||(const Connection& lhs, const Connection& rhs);
    QDataStream& operator<<(QDataStream& iStream, const Connection& iConnection);
    QDataStream& operator>>(QDataStream& iStream, Connection& iConnection);
}

Q_DECLARE_METATYPE(iRail::Connection)

#endif // CONNECTION_H

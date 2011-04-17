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
        Connection(const POI& iDeparture, const POI& iArrival);

        // Basic I/O
        POI departure() const;
        POI arrival() const;
        Station terminus() const;
        void setTerminus(const Station& iTerminus);
        Vehicle vehicle() const;
        void setVehicle(const Vehicl& iVehicle);

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const Connection& iConnection);
        friend QDataStream &operator>>(QDataStream& iStream, Connection& iConnection);

    private:
        POI mDeparture, mArrival;
        Station mTerminus;
        Vehicle mVehicle;
    };

    QDataStream &operator<<(QDataStream& iStream, const Connection& iConnection);
    QDataStream &operator>>(QDataStream& iStream, Connection& iConnection);
}

Q_DECLARE_METATYPE(iRail::Connection)

#endif // CONNECTION_H
//
// Configuration
//

// Include guard
#ifndef JOURNEY_H
#define JOURNEY_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include "stop.h"
#include "station.h"
#include "vehicle.h"

namespace iRail
{
    class Journey : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Stop departure READ departure CONSTANT)
    Q_PROPERTY(Stop arrival READ arrival CONSTANT)
    Q_PROPERTY(uint connections READ connections CONSTANT)
    public:
        // Construction and destruction
        Journey(Stop const* iDeparture, Stop const* iArrival);

        // Auxiliary structures
        struct Id
        {
            Stop const* departure;
            Stop const* arrival;
        };

        enum Roles
        {
          DepartureRole = Qt::UserRole+1,
          ArrivalRole
        };

        // Basic I/O
        Stop const* departure() const;
        Stop const* arrival() const;

        // Operators
        friend bool operator==(const Journey& lhs, const Journey& rhs);
        friend bool operator||(const Journey& lhs, const Journey& rhs);
        friend QDataStream &operator<<(QDataStream& iStream, const Journey& iJourney);
        friend QDataStream &operator>>(QDataStream& iStream, Journey& iJourney);

    private:
        Q_DISABLE_COPY(Journey);
        Id mId;
    };

    bool operator==(const Journey& lhs, const Journey& rhs);
    bool operator||(const Journey& lhs, const Journey& rhs);
    QDataStream &operator<<(QDataStream& iStream, const Journey& iJourney);
    QDataStream &operator>>(QDataStream& iStream, Journey& iJourney);
}

Q_DECLARE_METATYPE(iRail::Journey)
Q_DECLARE_METATYPE(iRail::Journey::Id)

#endif // JOURNEY_H

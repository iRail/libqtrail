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
#include <QHash>
#include "stop.h"
#include "station.h"
#include "vehicle.h"

namespace iRail
{
    class Journey : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Id id READ id CONSTANT)
    public:
        // Construction and destruction
        Journey(Stop const* iDeparture, Stop const* iArrival);

        // Auxiliary structures
        struct Id
        {
            Stop const* origin;
            Stop const* destination;
            friend inline unsigned int qHash(const Journey::Id& iJourneyId);
            bool operator==(const Journey::Id& lhs, const Journey::Id& rhs);
        };

        enum Roles
        {
          DepartureRole = Qt::UserRole+1,
          ArrivalRole
        };

        // Basic I/O
        Id id() const;

        // Operators
        friend bool operator==(const Journey& lhs, const Journey& rhs);

    private:
        Q_DISABLE_COPY(Journey);
        Id mId;
    };

    bool operator==(const Journey& lhs, const Journey& rhs);
    inline unsigned int qHash(const Journey::Id& iJourneyId);
}

Q_DECLARE_METATYPE(iRail::Journey)
Q_DECLARE_METATYPE(iRail::Journey::Id)

#endif // JOURNEY_H

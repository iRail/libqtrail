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
    Q_PROPERTY(uint delay READ relay WRITE setDelay)
    public:
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
            OriginRole = Qt::UserRole+1,
            DestinationRole,
            DelayRole
        };

        // Construction and destruction
        Journey(Stop const* iDeparture, Stop const* iArrival);

        // Basic I/O
        Id id() const;
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);

        // Operators
        friend bool operator==(const Journey& lhs, const Journey& rhs);
        friend Journey& operator=(const Journey& other);

    private:
        Q_DISABLE_COPY(Journey);
        Id mId;
        unsigned int mDelay;
    };

    bool operator==(const Journey& lhs, const Journey& rhs);
    Journey& operator=(const Journey& other);
    inline unsigned int qHash(const Journey::Id& iJourneyId);
}

Q_DECLARE_METATYPE(iRail::Journey)
Q_DECLARE_METATYPE(iRail::Journey::Id)

#endif // JOURNEY_H

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
#include <QVariant>
#include "api/data.h"
#include "stop.h"
#include "station.h"
#include "vehicle.h"

namespace iRail
{
    class Journey : public Data
    {
    Q_OBJECT
    Q_PROPERTY(uint delay READ delay WRITE setDelay)
    public:
        // Auxiliary structures
        struct Id
        {
            Stop const* origin;
            Stop const* destination;

            // Operators
            friend inline unsigned int qHash(const Journey::Id& iJourneyId);
            friend bool operator==(const Journey::Id& lhs, const Journey::Id& rhs);
        };

        enum Roles
        {
            OriginRole = Qt::UserRole+1,
            DestinationRole,
            DelayRole
        };

        // Construction and destruction
        Journey(Id iId);

        // Basic I/O
        QVariant field(int iRole) const;
        Id const* id() const;
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);

        // Operators
        friend bool operator==(const Journey& lhs, const Journey& rhs);
        Journey& operator=(const Journey& other);

    private:
        Id mId;
        unsigned int mDelay;
    };

    bool operator==(const Journey& lhs, const Journey& rhs);
    inline unsigned int qHash(const Journey::Id& iJourneyId);
    bool operator==(const Journey::Id& lhs, const Journey::Id& rhs);
}

#endif // JOURNEY_H

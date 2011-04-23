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
            DelayRole
        };

        // Construction and destruction
        Journey(Id iId);

        // Basic I/O
        Id& id() const;
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);

        // Operator implementation
        bool equals(const Data& data) const;
        Data& assign(const Data& data);

    private:
        Id mId;
        unsigned int mDelay;
    };
}

Q_DECLARE_METATYPE(iRail::Journey::Id)

#endif // JOURNEY_H

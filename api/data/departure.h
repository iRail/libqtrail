//
// Configuration
//

// Include guard
#ifndef DEPARTURE_H
#define DEPARTURE_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDebug>
#include <QHash>
#include "api/data.h"
#include "stop.h"
#include "vehicle.h"

namespace iRail
{
    class Departure : public Data
    {
    Q_OBJECT
    Q_PROPERTY(uint delay READ delay WRITE setDelay)
    public:
        // Auxiliary structure
        struct Id : Data::Id
        {
            Stop const* origin;
            Vehicle const* vehicle;

            // Operator implementation
            bool equals(const Data::Id& id) const;
            unsigned int hash() const;
        };
        enum Roles
        {
            VehicleRole = Qt::UserRole+1,
            OriginRole,
            DelayRole
        };

        // Construction and destruction
        Departure(Id iId);

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

Q_DECLARE_METATYPE(iRail::Departure::Id)

#endif // DEPARTURE_H

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
#include <QVariant>
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
        struct Id : AbstractId
        {
            Stop const* origin;
            Vehicle const* vehicle;

            // Operator implementation
            bool equals(const AbstractId& id) const;
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
        QVariant field(int iRole) const;
        Id const* id() const;
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

#endif // DEPARTURE_H

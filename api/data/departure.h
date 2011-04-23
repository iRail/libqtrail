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
        struct IId : Data::Id
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
        Departure(IId iId);

        // Basic I/O
        Data::Id& id() const;
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);

        // Operator implementation
        bool equals(const Data& data) const;
        Data& assign(const Data& data);

    private:
        IId mId;
        unsigned int mDelay;
    };
}

#endif // DEPARTURE_H

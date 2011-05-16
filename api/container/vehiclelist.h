//
// Configuration
//

// Include guard
#ifndef VEHICLELIST_H
#define VEHICLELIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QHash>
#include "api/exception.h"
#include "api/data/vehicle.h"
#include "api/container.h"

namespace iRail
{
    class VehicleList : public Container<Vehicle>
    {
    Q_OBJECT
    public:
        // Construction and destruction
        VehicleList(QObject* iParent = 0);
        ~VehicleList();

    public:
        // Basic I/O

    private:
        // Member data
        QDateTime mTimestamp;
    };
}

#endif // VEHICLELIST_H

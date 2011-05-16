//
// Configuration
//

// Include guard
#ifndef STOPLIST_H
#define STOPLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QHash>
#include "api/exception.h"
#include "api/data/vehicle.h"
#include "api/data/connection.h"
#include "api/data/stop.h"
#include "api/container.h"

namespace iRail
{
    class StopList : public Container<Stop>
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StopList(QObject* iParent = 0);
        StopList(const Vehicle::Id& iVehicleId, QObject* iParent = 0);
        ~StopList();

        // Basic I/O
    public:
        Vehicle::Id const* vehicleId() const;

    signals:
        // Data reply signals

        // Data processing methods
    private slots:

    private:
        // Member data
        Vehicle::Id mVehicleId;
    };
}

#endif // STOPLIST_H

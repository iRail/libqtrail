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
#include "api/requesthelper.h"
#include "api/data/vehicle.h"
#include "api/data/connection.h"
#include "api/data/stop.h"
#include "api/container.h"

namespace iRail
{
    class StopList : public Container<Stop>, private RequestHelper
    {
    Q_OBJECT
    public:
        // Construction and destruction
        StopList(QObject* iParent = 0);
        StopList(Vehicle::Id const* iVehicleId, QObject* iParent = 0);
        ~StopList();

        // Basic I/O
    public:
        Vehicle::Id const* vehicleId() const;

    public:
        // Data request methods
        void fetch();

    signals:
        // Data reply signals
        void success();
        void failure(const Exception& iException);

        // Data processing methods
    private slots:
        void process();

    private:
        // Member data
        Vehicle::Id const* mVehicleId;
    };
}

#endif // STOPLIST_H

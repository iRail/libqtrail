//
// Configuration
//

// Include guard
#ifndef CACHEDAPI_H
#define CACHEDAPI_H

// Includes
#include "asyncapi.h"
#include "api/storage.h"
#include "api/connectionrequest.h"
#include <QString>
#include <QMap>

// Definitions (TODO: move to Qt configuration objects)
#define STATIONS_REFRESH 3600

namespace iRail
{
    class CachedAPI : public AsyncAPI
    {
    Q_OBJECT
        // Construction and destruction
    public:
        CachedAPI(const QString& iClientID, const QString& iClientVersion, Storage* iStorage);

        // Request slots
    public slots:
        void requestStations();
        void requestConnections(const ConnectionRequestPointer& iConnectionRequest);
        void requestVehicle(const QString& iVehicleId);
        void requestLiveboard(const QString& iStationId);

        // Caching slots
    private slots:
        void cacheStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp);

        // Progress indicator signals
    signals:
        void miss();

        // Member data
    private:
        Storage* mStorage;
    };
}

#endif // CACHEDAPI_H

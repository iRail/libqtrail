//
// Configuration
//

// Include guard
#ifndef CACHEDAPI_H
#define CACHEDAPI_H

// Includes
#include "asyncapi.h"
#include "api/storage.h"
#include <QString>

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

        // Secondary stage request slots
    private slots:
        void requestConnectionsAfterStations(QList<StationPointer>* iStations);

        // Caching slots
    private slots:
        void cacheStations(QList<StationPointer>* iStations);

        // Progress indicator signals
    signals:
        void miss();

        // Member data
    private:
        Storage* mStorage;

        // Temporary data
        ConnectionRequestPointer tConnectionRequest;
    };
}

#endif // CACHEDAPI_H

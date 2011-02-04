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
#include "api/liveboardrequest.h"
#include <QString>
#include <QMap>

/*!
  \class CachedAPI

  \brief The CachedAPI is a more higher-level API wrapper, in that
  it provides a transparant and configurable caching layer. Essentially
  it works the same as the regular AsyncAPI, all data is passed back
  through signals, but all requesting methods are a tad different
  so the callee knows whether the request results in a cache hit
  or miss.
  */

// Definitions (TODO: move to Qt configuration objects)
#define STATIONS_REFRESH 3600*24*7

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
        void requestStations(bool& oCached);
        void requestConnections(const ConnectionRequestPointer& iConnectionRequest);
        void requestConnections(const ConnectionRequestPointer& iConnectionRequest, bool& oCached);
        void requestVehicle(const QString& iVehicleId);
        void requestVehicle(const QString& iVehicleId, bool& oCached);
        void requestLiveboard(const LiveboardRequestPointer& iLiveboardRequest);
        void requestLiveboard(const LiveboardRequestPointer& iLiveboardRequest, bool& oCached);

        // Caching slots
    private slots:
        void cacheStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp);

        // Member data
    private:
        Storage* mStorage;
    };
}

#endif // CACHEDAPI_H

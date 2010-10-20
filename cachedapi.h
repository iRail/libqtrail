//
// Configuration
//

// Include guard
#ifndef CACHEDAPI_H
#define CACHEDAPI_H

// Includes
#include <QList>
#include "api/station.h"
#include "api/connectionrequest.h"
#include "api/connection.h"
#include "api/storage.h"
#include "api/exception.h"
#include "asyncapi.h"

// TODO: document how asyncapi uses the hasError/error idiom, while the
// blocking cachedapi can use exceptions

namespace iRail
{
    class CachedAPI : public AsyncAPI
    {
    Q_OBJECT
        // Auxiliary types
        enum Status
        {
            IDLE,
            BUSY,
            INTERRUPTED
        };

        // Construction and destruction
    public:
        CachedAPI(const QString& iClientID, const QString& iClientVersion, Storage* iStorage);

        // API response handlers
    private slots:
        void receiveStations(QList<StationPointer> iStations);
        void receiveConnections(QList<ConnectionPointer> iConnections);

        // Slots
    public slots:
        //void cancel(); // TODO 1: handle this, and TODO 2: slot cancel() also in async, problem?

        // Getters
    public:
        QList<StationPointer> stations() throw(Exception);
        QList<ConnectionPointer> connections(ConnectionRequestPointer iConnectionRequest) throw(Exception);

        // Member data
    private:
        Storage* mStorage;
        Status mStatus;

        // Temporary data
    private:
        QList<StationPointer> mStations;
        QList<ConnectionPointer> mConnections;

        // Auxiliary methods
    private:
        void wait() throw(Exception);
    };
}

#endif // CACHEDAPI_H

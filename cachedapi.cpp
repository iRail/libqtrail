//
// Configuration
//

// Includes
#include "cachedapi.h"
#include "api/exception/interruptedexception.h"
#include <QApplication>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

CachedAPI::CachedAPI(const QString& iClientID, const QString& iClientVersion, Storage* iStorage) : AsyncAPI(iClientID, iClientVersion), mStorage(iStorage)
{
    mStatus = IDLE;

    // Connect the signal handler
    // As we privately inherit, we can safely assume no user will tamper with the
    // raw API, so we can connect everything now already
    connect(this, SIGNAL(replyStations(QList<StationPointer>)), this, SLOT(receiveStations(QList<StationPointer>)));
    connect(this, SIGNAL(replyConnections(QList<ConnectionPointer>)), this, SLOT(receiveConnections(QList<ConnectionPointer>)));
}


//
// Getters
//

QList<StationPointer> CachedAPI::stations() throw(Exception)
{
    // Try the cache
    QList<StationPointer>* tStations = mStorage->stations();
    if (tStations != 0)
        return *tStations;

    // Request a new object
    AsyncAPI::requestStations();

    // Wait and return
    wait();
    return mStations;
}

QList<ConnectionPointer> CachedAPI::connections(ConnectionRequestPointer iConnectionRequest) throw(Exception)
{
    // TODO: cache

    // Request a new object
    AsyncAPI::requestConnections(iConnectionRequest);

    // Wait and return
    wait();
    return mConnections;
}


//
// API response handlers
//

void CachedAPI::receiveStations(QList<StationPointer> iStations)
{
    if (mStatus == BUSY)
    {
        mStorage->setStations(iStations);
        mStations = iStations;  // TODO: pointer?
        mStatus = IDLE;
    }
    else
    {
        //warning("received unrequested data, is somebody tampering with the underlying API?");
    }
}

void CachedAPI::receiveConnections(QList<ConnectionPointer> iConnections)
{
    if (mStatus == BUSY)
    {
        // TODO: cache
        mConnections = iConnections;  // TODO: pointer?
        mStatus = IDLE;
    }
    else
    {
        //warning("received unrequested data, is somebody tampering with the underlying API?");
    }
}


//
// Auxiliary
//

void CachedAPI::wait() throw(Exception)
{
    // Set busy status
    mStatus = BUSY;

    // Wait for the result
    while (mStatus == BUSY && !AsyncAPI::hasError())
    {
        // Perform event loop iteration
        QApplication::processEvents();
    }

    // Problems...
    if (mStatus == INTERRUPTED)
    {
        mStatus = IDLE;
        throw new InterruptedException();
    }
    else if (AsyncAPI::hasError())
    {
        mStatus = IDLE;
        throw AsyncAPI::error();
    }
    else if (mStatus == IDLE)
    {
        return;
    }
    else
    {
        mStatus = IDLE;
        throw Exception("unknown problem");
    }
}

//
// Configuration
//

// Includes
#include "departurelist.h"
#include <QString>
#include "api/reader/liveboardreader.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

DepartureList::DepartureList(const Station::Id& iStationId, QObject* iParent) : mStationId(iStationId), QAbstractListModel(iParent), mContainer(this)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Departure::VehicleRole] = "vehicle";
    tRoleNames[Departure::OriginRole] = "origin";
    tRoleNames[Departure::DelayRole] = "delay";
    setRoleNames(tRoleNames);
}

DepartureList::~DepartureList()
{
}


//
// Basic I/O
//

Station::Id const* DepartureList::stationId() const
{
    return &mStationId;
}


//
// Data request methods
//

void DepartureList::fetch()
{
    // Construct URL
    QUrl tURL = mRequestHelper.createBaseURL();
    tURL.setPath("liveboard/");

    // Set the parameters
    tURL.addQueryItem("id", stationId()->guid);

    // Create a request
    try
    {
        mRequestHelper.networkRequest(mRequestHelper.getRequest(tURL), this, SLOT(process()));
    }
    catch (NetworkException& iException)
    {
        emit failure(iException);
    }
}

void DepartureList::fetch(const QDateTime& iDatetime)
{
    // Construct URL
    QUrl tURL = mRequestHelper.createBaseURL();
    tURL.setPath("liveboard/");

    // Set the parameters
    tURL.addQueryItem("id", stationId()->guid);
    tURL.addQueryItem("date", iDatetime.date().toString("ddMMyy"));
    tURL.addQueryItem("time", iDatetime.time().toString("hhmm"));

    // Create a request
    try
    {
        mRequestHelper.networkRequest(mRequestHelper.getRequest(tURL), this, SLOT(process()));
    }
    catch (NetworkException& iException)
    {
        emit failure(iException);
    }
}


//
// Data processing methods
//

void DepartureList::process()
{
    // Parse the data
    LiveboardReader tReader;
    try
    {
        tReader.read(mRequestHelper.networkReply());
        QList<Departure*> tDepartures = tReader.departures();
        mContainer.replaceData(tDepartures);
    }
    catch (ParserException& iException)
    {
        emit failure(iException);
    }

    // TODO

    // Clean up
    mRequestHelper.networkCleanup();
    emit success();
}

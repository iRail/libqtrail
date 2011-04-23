//
// Configuration
//

// Includes
#include "departurelist.h"
#include <QString>
#include "api/reader/departurereader.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

DepartureList::DepartureList(const Station::Id& iStationId, QObject* iParent) : mStationId(iStationId), QAbstractListModel(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Departure::VehicleRole] = "vehicle";
    tRoleNames[Departure::OriginRole] = "origin";
    tRoleNames[Departure::DelayRole] = "delay";
    setRoleNames(tRoleNames);
}

DepartureList::~DepartureList()
{
    qDeleteAll(mDepartures.values());
    mDepartures.clear();
}


//
// Basic I/O
//

const Station& DepartureList::stationId() const
{
    return mStationId;
}


//
// Model interface
//

int DepartureList::rowCount(const QModelIndex& iParent) const
{
    return mDepartures.size();
}

QVariant DepartureList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mDepartures.size()-1) )
        return QVariant();

    // TODO: sort through virtual mapping structure
    Departure* oDeparture = mDepartures.values().at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Departure::VehicleRole:
        return QVariant::fromValue(oDeparture->vehicle());
    case Departure::OriginRole:
        return QVariant::fromValue(oDeparture->stop());
    case Departure::DelayRole:
        return QVariant::fromValue(oDeparture->delay());
    default:
        return QVariant();
    }
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
    tURL.addQueryItem("id", stationId().id());

    // Create a request
    try
    {
        network_request(getRequest(tURL), this, SLOT(process()));
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
    tURL.addQueryItem("id", stationId().id());
    tURL.addQueryItem("date", iDatetime.date().toString("ddMMyy"));
    tURL.addQueryItem("time", iDatetime.time().toString("hhmm"));

    // Create a request
    try
    {
        network_request(getRequest(tURL), this, SLOT(process()));
    }
    catch (NetworkException& iException)
        emit failure(iException);
}


//
// Data processing methods
//

void DepartureList::process()
{
    // Parse the data
    DepartureReader tReader;
    try
    {
        tReader.read(mNetworkReply);
    }
    catch (ParserException& iException)
            emit failure(iException);
    QList<Departure> tDeparturesNew = tReader.departures();

    // TODO

    // Clean up
    mRequestHelper.networkCleanup();
    emit success();
}

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

DepartureList::DepartureList(const Station& iStation, QObject* iParent) : mStation(iStation), QAbstractListModel(iParent)
{
    qRegisterMetaType<DepartureList>("DepartureList");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Departure::VehicleRole] = "vehicle";
    tRoleNames[Departure::POIRole] = "poi";
    setRoleNames(tRoleNames);
}


//
// Basic I/O
//

const Station& DepartureList::station() const
{
    return mStation;
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

    Departure* oDeparture = mDepartures.at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Departure::VehicleRole:
        return QVariant::fromValue(oDeparture->vehicle());
    case Departure::POIRole:
        return QVariant::fromValue(oDeparture->poi());
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
    tURL.addQueryItem("id", station().id());

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
    tURL.addQueryItem("id", station().id());
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


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const DepartureList& iDepartureList)
{
    iStream << iDepartureList.mStation;

    iStream << iDepartureList.mDepartures.size();
    foreach (Departure* tDeparture, iDepartureList.mDepartures)
        iStream << *tDeparture;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, DepartureList& iDepartureList)
{
    iStream >> iDepartureList.mStation;

    int tDepartures;
    iStream >> tDepartures;
    Q_ASSERT(iDepartureList.mDepartures.size() == 0);
    for (int i = 0; i < tDepartures; i++)
    {
        Departure* tDeparture;
        iStream >> *tDeparture;
        iDepartureList.mDepartures << tDeparture;
    }

    return iStream;
}


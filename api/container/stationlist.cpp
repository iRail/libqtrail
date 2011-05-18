//
// Configuration
//

// Includes
#include "stationlist.h"
#include "api/reader/stationsreader.h"
#include <QString>
#include <QDebug>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StationList::StationList(QObject* iParent) : Container(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Station::GUIDRole] = "guid";
    tRoleNames[Station::NameRole] = "name";
    tRoleNames[Station::LocationRole] = "location";
    setRoleNames(tRoleNames);
}

StationList::~StationList()
{
}


//
// Data request methods
//

void StationList::fetch()
{
    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("stations/");

    // Create a request
    try
    {
        networkRequest(getRequest(tURL), this, SLOT(process()));
    }
    catch (NetworkException& iException)
    {
        emit failure(iException);
    }
}


//
// Data processing methods
//

void StationList::process()
{
    // Parse the data
    bool tSuccess = false;
    StationsReader tReader;
    try
    {
        tReader.read(networkReply());
        QList<Station*> tStations = tReader.stations();
        replaceData(tStations);
        tSuccess = true;
    }
    catch (ParserException& iException)
    {
        emit failure(iException);
    }

    // Clean up
    networkCleanup();
    if (tSuccess)
        emit success();
}

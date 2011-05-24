//
// Configuration
//

// Includes
#include "journeylist.h"
#include "api/reader/connectionsreader.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

JourneyList::JourneyList(Station::Id const* iOrigin, Station::Id const* iDestination, QObject* iParent) : Container(iParent), mOrigin(iOrigin), mDestination(iDestination)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Journey::OriginRole] = "origin";
    tRoleNames[Journey::DestinationRole] = "destination";
    tRoleNames[Journey::DelayRole] = "delay";
    setRoleNames(tRoleNames);
}

JourneyList::~JourneyList()
{
}


//
// Basic I/O
//


Station::Id const* JourneyList::origin() const
{
    return mOrigin;
}

Station::Id const* JourneyList::destination() const
{
    return mDestination;
}


//
// Data request methods
//

void JourneyList::fetch()
{
    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("connections/");

    // Set the parameters
    tURL.addQueryItem("from", origin()->guid);
    tURL.addQueryItem("to", destination()->guid);

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

void JourneyList::fetch(const QDateTime& iDatetime, JourneyList::Type iType)
{
    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("liveboard/");

    // Set the parameters
    tURL.addQueryItem("from", origin()->guid);
    tURL.addQueryItem("to", destination()->guid);
    tURL.addQueryItem("date", iDatetime.date().toString("ddMMyy"));
    tURL.addQueryItem("time", iDatetime.time().toString("hhmm"));
    tURL.addQueryItem("timeSel", iType == Arrival ? "arrive" : "depart");

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

void JourneyList::process()
{
    // Parse the data
    bool tSuccess = false;
    ConnectionsReader tReader;
    try
    {
        tReader.read(networkReply());
        QList<Journey*> tJourneys = tReader.journeys();
        replaceData(tJourneys);
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

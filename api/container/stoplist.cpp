//
// Configuration
//

// Includes
#include "stoplist.h"
#include "api/reader/vehiclereader.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StopList::StopList(QObject *iParent) : Container(iParent)
{
    mVehicleId = 0;

    // TODO: remove duplicate code
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Stop::StationRole] = "station";
    tRoleNames[Stop::DatetimeRole] = "datetime";
    tRoleNames[Stop::PlatformRole] = "platform";
    setRoleNames(tRoleNames);
}

StopList::StopList(Vehicle::Id const* iVehicleId, QObject* iParent) : Container(iParent), mVehicleId(iVehicleId)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Stop::StationRole] = "station";
    tRoleNames[Stop::DatetimeRole] = "datetime";
    tRoleNames[Stop::PlatformRole] = "platform";
    setRoleNames(tRoleNames);
}

StopList::~StopList()
{
}


//
// Basic I/O
//

Vehicle::Id const* StopList::vehicleId() const
{
    return mVehicleId;
}

Stop const* StopList::get(const Stop::Id& iId)
{
    foreach (Stop* tStop, mData)
    {
        if (*tStop->id() == iId)
            return tStop;
    }
    return 0;

}


//
// Data request methods
//

void StopList::fetch()
{
    // Construct URL
    QUrl tURL = createBaseURL();
    tURL.setPath("vehicle/");

    // Set the parameters
    tURL.addQueryItem("id", vehicleId()->guid);

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

void StopList::process()
{
    // Parse the data
    bool tSuccess = false;
    VehicleReader tReader;
    try
    {
        tReader.read(networkReply());
        QList<Stop*> tStops = tReader.stops();
        replaceData(tStops);
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

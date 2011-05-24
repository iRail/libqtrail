//
// Configuration
//

// Includes
#include "vehiclereader.h"
#include "api/containercache.h"
#include <QStringRef>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

VehicleReader::VehicleReader()
{
}


//
// Reader interface
//

void VehicleReader::readDocument()
{
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isStartElement())
        {
            if (mReader.name() == "vehicleinformation")
                readVehicleInformation();
            else if (mReader.name() == "error")
                readError();
            else
                mReader.raiseError("could not find vehicleinformation index");
        }
        else
            mReader.readNext();
    }
}


//
// Basic I/O
//


double VehicleReader::version() const
{
    return mVersion;
}

QDateTime VehicleReader::timestamp() const
{
    return mTimestamp;
}

Vehicle* VehicleReader::vehicle() const
{
    return mVehicle;
}

QList<Stop*> VehicleReader::stops() const
{
    return mStops;
}


//
// Tag readers
//

void VehicleReader::readVehicleInformation()
{
    // Process the attributes
    if (mReader.attributes().hasAttribute("timestamp"))
    {
        QStringRef tTimestampString = mReader.attributes().value("timestamp");

        mTimestamp.setTime_t(tTimestampString.toString().toLong());
    }
    else
        mReader.raiseError("could not find Vehicles timestamp attribute");
    if (mReader.attributes().hasAttribute("version"))
    {
        QStringRef tVersionString = mReader.attributes().value("version");

        mVersion = tVersionString.toString().toDouble();
    }
    else
        mReader.raiseError("could not find vehicles version attribute");

    // Process the tags
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isEndElement())
        {
            mReader.readNext();
            break;
        }

        if (mReader.isStartElement())
        {
            if (mReader.name() == "vehicle")
                mVehicle = readVehicle();
            else if (mReader.name() == "stops")
                mStops = readStops();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }
}

Vehicle* VehicleReader::readVehicle()
{
    // Process the attributes
    Location tLocation;
    if (mReader.attributes().hasAttribute("location"))
    {
        QStringRef tLocationString = mReader.attributes().value("location");

        int tSeparator = tLocationString.toString().indexOf(" ");

        // TODO: when Qt 4.8 gets released, QStringRef
        //       will natively implement these
        //       convenience functionality
        //       http://qt.gitorious.org/qt/qt/merge_requests/625
        qreal tLongitude = tLocationString.toString().midRef(0, tSeparator).toString().toDouble();
        qreal tLatitude = tLocationString.toString().midRef(tSeparator+1).toString().toDouble();
        tLocation.setLongitude(tLongitude);
        tLocation.setLatitude(tLatitude);
    }

    // Process the contents
    QString tVehicleGUID = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    Vehicle::Id tVehicleId;
    tVehicleId.guid = tVehicleGUID;
    Vehicle* oVehicle = new Vehicle(tVehicleId);
    oVehicle->setLocation(tLocation);

    return oVehicle;
}

QList<Stop*> VehicleReader::readStops()
{
    // Process the attributes
    QList<Stop*> oStops;
    if (mReader.attributes().hasAttribute("number"))
    {
        QStringRef tCountString = mReader.attributes().value("number");
        int tCount = tCountString.toString().toInt();
        if (tCount > 0)
            oStops.reserve(tCount);
    }

    // Process the tags
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isEndElement())
        {
            mReader.readNext();
            break;
        }

        if (mReader.isStartElement())
        {
            if (mReader.name() == "stop")
                oStops << readStop();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    return oStops;
}

Stop* VehicleReader::readStop()
{
    // Process the attributes
    double tDelay;
    if (mReader.attributes().hasAttribute("delay"))
    {
        tDelay = mReader.attributes().value("delay").toString().toDouble();
    }
    else
        mReader.raiseError("stop without delay attribute");

    // Process the tags
    Station* tStation;
    QDateTime tDatetime;
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isEndElement())
        {
            mReader.readNext();
            break;
        }

        if (mReader.isStartElement())
        {
            if (mReader.name() == "station")
                tStation = readStation();
            if (mReader.name() == "time")
                tDatetime = readDatetime();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    Stop::Id tStopId;
    tStopId.station = tStation;
    tStopId.datetime = tDatetime;
    return new Stop(tStopId);
}

Station* VehicleReader::readStation()
{
    // Process the attributes
    QString tStationGuid;
    if (mReader.attributes().hasAttribute("id"))
    {
        tStationGuid = mReader.attributes().value("id").toString();
    }
    else
        mReader.raiseError("station without id");

    // Process the contents
    mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    Station::Id tStationId;
    tStationId.guid = tStationGuid;
    Station* tStation = ContainerCache::instance().stationList()->get(tStationId);
    if (tStation == 0)
        tStation = new Station(tStationId);
    return tStation;
}

QDateTime VehicleReader::readDatetime()
{
    // Process the contents
    QString tUnixtime = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return QDateTime::fromTime_t(tUnixtime.toUInt());
}

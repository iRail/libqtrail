//
// Configuration
//

// Includes
#include "liveboardreader.h"
#include "api/containercache.h"
#include <QStringRef>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

LiveboardReader::LiveboardReader()
{
}


//
// Reader interface
//

void LiveboardReader::readDocument()
{
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isStartElement())
        {
            if (mReader.name() == "liveboard")
                readLiveboard();
            else if (mReader.name() == "error")
                readError();
            else
                mReader.raiseError("could not find liveboard index");
        }
        else
            mReader.readNext();
    }
}


//
// Basic I/O
//


double LiveboardReader::version() const
{
    return mVersion;
}

QDateTime LiveboardReader::timestamp() const
{
    return mTimestamp;
}

Station const* LiveboardReader::station() const
{
    return mStation;
}

QList<Departure*> LiveboardReader::departures() const
{
    return mDepartures;
}


//
// Tag readers
//

void LiveboardReader::readLiveboard()
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
            if (mReader.name() == "station")
                mStation = readStation();
            else if (mReader.name() == "departures")
                mDepartures = readDepartures();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }
}

Station const* LiveboardReader::readStation()
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
    Station const* oStation = ContainerCache::instance().stationList()->get(tStationId);
    if (oStation == 0)
    {
        Station* tStation = new Station(tStationId);
        ContainerCache::instance().stationList()->append(tStation);
        oStation = tStation;
    }
    return oStation;
}

QList<Departure*> LiveboardReader::readDepartures()
{
    // Process the attributes
    QList<Departure*> oDepartures;
    if (mReader.attributes().hasAttribute("number"))
    {
        QStringRef tCountString = mReader.attributes().value("number");
        int tCount = tCountString.toString().toInt();
        if (tCount > 0)
            oDepartures.reserve(tCount);
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
            if (mReader.name() == "departure")
                oDepartures << readDeparture();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    return oDepartures;
}

Departure* LiveboardReader::readDeparture()
{
    // Process the attributes
    unsigned int tDelay = 0;
    if (mReader.attributes().hasAttribute("delay"))
    {
        tDelay = mReader.attributes().value("delay").toString().toInt();
    }

    // Process the tags
    Station const* tStation = 0;
    Vehicle const* tVehicle = 0;
    QDateTime tDateTime;
    QString tPlatform;
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
            else if (mReader.name() == "vehicle")
                tVehicle = readVehicle();
            else if (mReader.name() == "time")
                tDateTime = readDatetime();
            else if (mReader.name() == "platform")
                tPlatform = readPlatform();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the stop
    // TODO: put in anonymous StopList
    Stop::Id tStopId;
    tStopId.station = tStation;
    tStopId.datetime = tDateTime;
    Stop* tStop = new Stop(tStopId);
    tStop->setPlatform(tPlatform);

    // Construct the id
    Departure::Id tDepartureId;
    tDepartureId.origin = tStop;
    tDepartureId.vehicle = tVehicle;
    Departure* oDeparture = new Departure(tDepartureId);
    oDeparture->setDelay(tDelay);

    return oDeparture;
}

Vehicle const* LiveboardReader::readVehicle()
{
    // Process the contents
    QString tVehicleGuid = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    Vehicle::Id tVehicleId;
    tVehicleId.guid = tVehicleGuid;
    Vehicle const* oVehicle = ContainerCache::instance().vehicleList()->get(tVehicleId);
    if (oVehicle == 0)
    {
        Vehicle* tVehicle = new Vehicle(tVehicleId);
        ContainerCache::instance().vehicleList()->append(tVehicle);
        oVehicle = tVehicle;
    }
    return oVehicle;
}

QDateTime LiveboardReader::readDatetime()
{
    // Process the contents
    QString tUnixtime = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return QDateTime::fromTime_t(tUnixtime.toUInt());
}

QString LiveboardReader::readPlatform()
{
    // Process the attributes
    bool *tNormal = 0;
    if (mReader.attributes().hasAttribute("normal"))
    {
        QStringRef tNormalString = mReader.attributes().value("normal");

        tNormal = new bool(tNormalString == "1");
    }

    // Process the contents
    QString oPlatform = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    if (*tNormal)
    {
        // TODO: do something with this
        delete tNormal;
    }
    return oPlatform;
}


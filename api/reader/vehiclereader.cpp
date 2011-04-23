//
// Configuration
//

// Includes
#include "vehiclereader.h"
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

QHash<Stop::Id&, Stop*> VehicleReader::stops() const
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
    QString tVehicleId = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    Vehicle* oVehicle = new Vehicle(tVehicleId);
    oVehicle->setLocation(tLocation);
    return oVehicle;
}

QHash<Stop::Id&, Stop*> VehicleReader::readStops()
{
    // Process the attributes
    QHash<Stop::Id&, Stop*> oStops;
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
            {
                Stop* tStop = readStop();
                oStops.insert(tStop->id(), tStop);
            }
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
    QDateTime tDateTime;
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
                tDateTime = readDatetime();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    Stop::Id& tStopId(tStation, tDatetime);
    Stop* oStop = new Stop(tStopId);
    return oStop;
}

Station* VehicleReader::readStation()   // TODO: fill station object
{
    // Process the attributes
    QString oStationId;
    if (mReader.attributes().hasAttribute("id"))
    {
        oStationId = mReader.attributes().value("id").toString();
    }
    else
        mReader.raiseError("station without id");

    // Process the contents
    mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    return Station(oStationId);
}

QDateTime VehicleReader::readDatetime()
{
    // Process the contents
    QString tUnixtime = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return QDateTime::fromTime_t(tUnixtime.toUInt());
}

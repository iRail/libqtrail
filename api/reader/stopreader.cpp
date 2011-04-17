//
// Configuration
//

// Includes
#include "stopreader.h"
#include <QStringRef>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StopReader::StopReader()
{
}


//
// Reader interface
//

void StopReader::readDocument()
{
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isStartElement())
        {
            if (mReader.name() == "vehicleinformation")
                mVehicle = new VehiclePointer(readVehicleInformation());
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


double StopReader::version() const
{
    return mVersion;
}

QDateTime StopReader::timestamp() const
{
    return mTimestamp;
}

Vehicle* StopReader::vehicle() const
{
    return mVehicle;
}

QList<POI*> StopReader::stops() const
{
    return mStops;
}


//
// Tag readers
//

void StopReader::readVehicleInformation()
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

Vehicle* StopReader::readVehicle()
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

QList<POI*> StopReader::readStops()
{
    // Process the tags
    QList<POI*> oStops;
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

    // Construct the object
    return oStops;
}

POI* StopReader::readStop()
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
    POI* oStop = new POI(tStation, tDatetime);
    oStop->setDelay(tDelay);
    return oStop;
}

Station StopReader::readStation()   // TODO: fill station object
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

QDateTime StopReader::readDatetime()
{
    // Process the contents
    QString tUnixtime = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return QDateTime::fromTime_t(tUnixtime.toUInt());
}

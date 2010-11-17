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
    mVehicle = 0;
}

VehiclePointer* VehicleReader::vehicle()
{
    return mVehicle;
}


//
// Tag readers
//

void VehicleReader::readDocument()
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

Vehicle* VehicleReader::readVehicleInformation()
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
    Vehicle* tVehicle;
    QList<Vehicle::Stop> tStops;
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
                tVehicle = readVehicle();
            else if (mReader.name() == "stops")
                tStops = readStops();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    tVehicle->setStops(tStops);
    return tVehicle;
}

Vehicle* VehicleReader::readVehicle()
{
    // Process the attributes
    double tLocationX, tLocationY;
    if (mReader.attributes().hasAttribute("locationX"))
    {
        QStringRef tLocationXString = mReader.attributes().value("locationX");

        tLocationX = tLocationXString.toString().toDouble();
    }
    else
        mReader.raiseError("could not find vehicle x-location attribute");
    if (mReader.attributes().hasAttribute("locationY"))
    {
        QStringRef tLocationYString = mReader.attributes().value("locationY");

        tLocationY = tLocationYString.toString().toDouble();
    }
    else
        mReader.raiseError("could not find vehicle y-location attribute");

    // Process the contents
    QString tVehicleId = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    Vehicle* oVehicle = new Vehicle(tVehicleId);
    oVehicle->setLocation(Vehicle::Location(tLocationX, tLocationY));
    return oVehicle;
}

QList<Vehicle::Stop> VehicleReader::readStops()
{
    // Process the tags
    QList<Vehicle::Stop> oStops;
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

Vehicle::Stop VehicleReader::readStop()
{
    // Process the tags
    QString tStationId;
    double tDelay;
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
                tStationId = readStation();
            if (mReader.name() == "delay")
                tDelay = readDelay();
            if (mReader.name() == "time")
                tDateTime = readDatetime();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    Vehicle::Stop oStop;
    oStop.datetime = tDateTime;
    oStop.station = tStationId;
    oStop.delay = tDelay;
    return oStop;
}

QString VehicleReader::readStation()
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
    return oStationId;
}

double VehicleReader::readDelay()
{
    // Process the contents
    QString tDelayString = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return tDelayString.toDouble();
}

QDateTime VehicleReader::readDatetime()
{
    // Process the contents
    QString tUnixtime = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return QDateTime::fromTime_t(tUnixtime.toUInt());
}



//
// Auxiliary
//

void VehicleReader::allocate()
{
}

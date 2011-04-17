//
// Configuration
//

// Includes
#include "departurereader.h"
#include <QStringRef>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

DepartureReader::DepartureReader()
{
}


//
// Reader interface
//

void DepartureReader::readDocument()
{
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isStartElement())
        {
            if (mReader.name() == "liveboard")
                mLiveboard = new LiveboardPointer(readLiveboard());
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


double DepartureReader::version() const
{
    return mVersion;
}

QDateTime DepartureReader::timestamp() const
{
    return mTimestamp;
}

Station DepartureReader::station() const
{
    return mStation;
}

QList<Departure> DepartureReader::departures() const
{
    return mDepartures;
}


//
// Tag readers
//

void DepartureReader::readLiveboard()
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

Station DepartureReader::readStation()
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
    // TODO: load from cache? do request? hmm
}

QList<Liveboard::Departure> DepartureReader::readDepartures()
{
    // Process the attributes
    int tNumber;
    if (mReader.attributes().hasAttribute("number"))
    {
        QStringRef tNumberString = mReader.attributes().value("number");

        tNumber = tNumberString.toString().toInt();
    }
    else
        mReader.raiseError("could not find departures count attribute");

    // Process the tags
    QList<Liveboard::Departure> oDepartures;
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

    if (oDepartures.size() != tNumber)
        mReader.raiseError("advertised nubmer of departures did not match the actual amount");
    return oDepartures;
}

Liveboard::Departure DepartureReader::readDeparture()
{
    // Process the attributes
    unsigned int tDelay = 0;
    if (mReader.attributes().hasAttribute("delay"))
    {
        tDelay = mReader.attributes().value("delay").toString().toInt();
    }

    // Process the tags
    QString tStation, tVehicle;
    QDateTime tDateTime;
    int tPlatform = 0;
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

    // Construct the object
    Liveboard::Departure tDeparture;
    tDeparture.station = tStation;
    tDeparture.vehicle = tVehicle;
    tDeparture.datetime = tDateTime;
    tDeparture.delay = tDelay;
    tDeparture.platform = tPlatform;
    return tDeparture;
}

QString DepartureReader::readVehicle()
{
    // Process the contents
    QString oVehicle = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return oVehicle;
}

QDateTime DepartureReader::readDatetime()
{
    // Process the contents
    QString tUnixtime = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return QDateTime::fromTime_t(tUnixtime.toUInt());
}

int DepartureReader::readPlatform()
{
    // Process the contents
    QString tPlatformString = mReader.readElementText();
    unsigned int oPlatform = tPlatformString.toInt();
    if (mReader.isEndElement())
        mReader.readNext();

    return oPlatform;
}


//
// Auxiliary
//

void DepartureReader::allocate()
{
}

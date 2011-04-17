//
// Configuration
//

// Includes
#include "journeyreader.h"
#include <QStringRef>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

JourneyReader::JourneyReader()
{
}


//
// Reader interface
//

void JourneyReader::readDocument()
{
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isStartElement())
        {
            if (mReader.name() == "connections")
                readConnections();
            else if (mReader.name() == "error")
                readError();
            else
                mReader.raiseError("could not find connections index");
        }
        else
            mReader.readNext();
    }
}


//
// Basic I/O
//


double JourneyReader::version() const
{
    return mVersion;
}

QDateTime JourneyReader::timestamp() const
{
    return mTimestamp;
}

QList<Journey> JourneyReader::journeys() const
{
    return mJourneys;
}


//
// Tag readers
//

void JourneyReader::readConnections()
{
    // Process the attributes
    if (mReader.attributes().hasAttribute("timestamp"))
    {
        QStringRef tTimestampString = mReader.attributes().value("timestamp");

        mTimestamp.setTime_t(tTimestampString.toString().toLong());
    }
    else
        mReader.raiseError("could not find connections timestamp attribute");
    if (mReader.attributes().hasAttribute("version"))
    {
        QStringRef tVersionString = mReader.attributes().value("version");

       mVersion = tVersionString.toString().toDouble();
    }
    else
        mReader.raiseError("could not find connections version attribute");

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
            if (mReader.name() == "connection")
                mConnections << readConnection();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

}

Journey JourneyReader::readConnection()
{
    // Process the attributes
    unsigned int tId;
    if (mReader.attributes().hasAttribute("id"))
    {
        QStringRef tIdString = mReader.attributes().value("id");

        tId = tIdString.toString().toInt();
    }
    else
        mReader.raiseError("could not find connection id attribute");

    // Process the tags
    POI tDeparture, tArrival;
    QList<Connection> tLines;
    tLines << Connection();
    QString tVehicleDeparture, tVehicleArrival;     //  NOTE TO READER: the iRail API _really_ sucks
    QList<QString> tVehicles;                       //  when it comes to connections and via's...
    QString tDirectionDeparture, tDirectionArrival; //  Same applies to the directions.
    QList<QString> tDirections;                     //  Please bug Pieter about this.
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
                tDeparture = readPOI(tVehicleDeparture, tDirectionDeparture);
            else if (mReader.name() == "arrival")
                tArrival = readPOI(tVehicleArrival, tDirectionArrival);
            else if (mReader.name() == "vias")
                tLines = readVias(tVehicles, tDirections);
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Fix the via/connection vehicle counterintuitiveness
    tVehicles << tVehicleArrival;
    tDirections << tDirectionArrival;
    Q_ASSERT(tVehicles.size() == tLines.size());
    Q_ASSERT(tDirections.size() == tLines.size());
    for (int i = 0; i < tLines.size(); i++)
    {
        tLines[i].vehicle = tVehicles.at(i);        // Did I say I really
        tLines[i].terminus = tDirections.at(i);     // hate this mess?
    }

    // Construct the object
    Journey oJourney(tDeparture, tArrival);
    tLines.first().departure = tDeparture;
    tLines.last().arrival = tArrival;
    // TODO oJourney->setLines(tLines);
    return oJourney;
}

POI JourneyReader::readPOI(QString& iVehicle, Station& iTerminus)
{
    // Process the attributes
    int tDelay = 0;
    if (mReader.attributes().hasAttribute("delay"))
    {
        QStringRef tDelayString = mReader.attributes().value("delay");

        tDelay = tDelayString.toString().toInt();
    }

    // Process the tags
    QString tStation;
    int tPlatform;
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
            if (mReader.name() == "vehicle")            // These fields should _not_
                iVehicle = readVehicle();               // be present in a POI.
            else if (mReader.name() == "direction")     // Please bug Pieter as frequently
                iTerminus = readStation();              // ase possible about this.
            else if (mReader.name() == "platform")
                tPlatform = readPlatform();
            else if (mReader.name() == "time")
                tDatetime = readDatetime();
            else if (mReader.name() == "station")
                tStation = readStation();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    POI oPOI;
    oPOI.station = tStation;
    oPOI.datetime = tDatetime;
    oPOI.delay = tDelay;
    oPOI.platform = tPlatform;
    return oPOI;
}

Vehicle JourneyReader::readVehicle()    // TODO: fill with data
{
    // Process the contents
    QString tVehicleId = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return Vehicle(tVehicleId);
}

int JourneyReader::readPlatform()
{
    // Process the attributes
    bool *tNormal = 0;
    if (mReader.attributes().hasAttribute("normal"))
    {
        QStringRef tNormalString = mReader.attributes().value("normal");

        tNormal = new bool(tNormalString == "1");
    }

    // Process the contents
    QString tPlatformString = mReader.readElementText();
    int oPlatform = tPlatformString.toInt();
    if (mReader.isEndElement())
        mReader.readNext();

    if (tNormal)
    {
        // TODO: do something with this
        delete tNormal;
    }
    return oPlatform;
}

QDateTime JourneyReader::readDatetime()
{
    // Process the contents
    QString tUnixtime = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return QDateTime::fromTime_t(tUnixtime.toUInt());
}

Station JourneyReader::readStation()        // TODO: fill with data
{
    // Process the attributes
    QString tStationId;
    if (mReader.attributes().hasAttribute("id"))
    {
        tStationId = mReader.attributes().value("id").toString();
    }
    else
        mReader.raiseError("station without id");

    // Process the contents
    mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    return Station(tStationId);
}

QList<Connection> JourneyReader::readVias(QList<QString>& iVehicles, QList<QString>& iDirections)
{
    // Process the attributes
    int tNumber;
    if (mReader.attributes().hasAttribute("number"))
    {
        QStringRef tNumberString = mReader.attributes().value("number");

        tNumber = tNumberString.toString().toInt();
    }
    else
        mReader.raiseError("could not find vias count attribute");

    // Process the tags
    QList<Connection> tLines;
    QString tVehicle, tDirection;
    tLines << Connection();
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
            if (mReader.name() == "via")
            {
                Connection tLine = readVia(tVehicle, tDirection);
                iVehicles << tVehicle;
                iDirections << tDirection;
                tLines.last().arrival = tLine.arrival;
                tLine.arrival = POI();
                tLines << tLine;
            }
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    if (tLines.size() != tNumber+1)
        mReader.raiseError("advertised nubmer of vias did not match the actual amount");
    return tLines;
}

Connection JourneyReader::readVia(QString& iVehicle, QString& iDirection)
{
    // Process the attributes
    unsigned int tId;   // TODO: do something with this
    if (mReader.attributes().hasAttribute("id"))
    {
        QStringRef tIdString = mReader.attributes().value("id");

        tId = tIdString.toString().toInt();
    }
    else
        mReader.raiseError("could not find via id attribute");

    // Process the tags
    POI tArrival, tDeparture, tTerminus;
    QString tVehicleDummy, tDepartureDummy;
    Station tStation, tTerminus;
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
                tDeparture = readPOI(tVehicleDummy, tDepartureDummy);
            else if (mReader.name() == "arrival")
                tArrival = readPOI(tVehicleDummy, tDepartureDummy);
            else if (mReader.name() == "vehicle")
                iVehicle = readVehicle();
            else if (mReader.name() == "station")
                tStation = readStation();
            else if (mReader.name() == "direction")
                iDirection = readStation();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    tArrival.station = tStation;
    tDeparture.station = tStation;
    tTerminus.station = tTerminus;
    Connection oLine;
    oLine.departure = tDeparture;
    oLine.arrival = tArrival;
    return oLine;
}

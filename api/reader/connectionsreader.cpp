//
// Configuration
//

// Includes
#include "connectionsreader.h"
#include <QStringRef>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

ConnectionsReader::ConnectionsReader()
{
}


//
// Reader interface
//

void ConnectionsReader::readDocument()
{
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isStartElement())
        {
            if (mReader.name() == "connections")
                mJourneys = readConnections();
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


double ConnectionsReader::version() const
{
    return mVersion;
}

QDateTime ConnectionsReader::timestamp() const
{
    return mTimestamp;
}

QList<Journey*> ConnectionsReader::journeys() const
{
    return mJourneys;
}


//
// Tag readers
//

QList<Journey*> ConnectionsReader::readConnections()
{
    // Process the attributes
    QList<Journey*> oJourneys;
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
    if (mReader.attributes().hasAttribute("number"))
    {
        QStringRef tCountString = mReader.attributes().value("number");
        int tCount = tCountString.toString().toInt();
        if (tCount > 0)
            oJourneys.reserve(tCount);
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
            if (mReader.name() == "connection")
                oJourneys << readConnection();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    return oJourneys;
}

Journey* ConnectionsReader::readConnection()
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
    Stop *tOrigin = 0, *tDestination = 0;
    QList<Connection*> tConnections;
    tConnections << new Connection(Connection::Id());
    Vehicle *tVehicleDeparture, *tVehicleArrival;       //  NOTE TO READER: the iRail API _really_ sucks
    QList<Vehicle*> tVehicles;                          //  when it comes to connections and via's...
    Station *tDirectionOrigin, *tDirectionDestination;  //  Same applies to the directions.
    QList<Station*> tDirections;                        //  Please bug Pieter about this.
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
                tOrigin = readStop(tVehicleDeparture, tDirectionOrigin);
            else if (mReader.name() == "arrival")
                tDestination = readStop(tVehicleArrival, tDirectionDestination);
            else if (mReader.name() == "vias")
                tConnections = readVias(tVehicles, tDirections);
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Fix the via/connection vehicle counterintuitiveness
    tVehicles << tVehicleArrival;
    tDirections << tDirectionDestination;
    Q_ASSERT(tVehicles.size() == tConnections.size());
    Q_ASSERT(tDirections.size() == tConnections.size());
    for (int i = 0; i < tConnections.size(); i++)
    {
        tConnections[i]->setVehicle(tVehicles.at(i));        // Did I say I really
        tConnections[i]->setTerminus(tDirections.at(i));     // hate this mess?
    }

    // Fix the first connection
    Connection::Id tConnectionFirstId;
    tConnectionFirstId.origin = tOrigin;
    tConnectionFirstId.destination = tConnections.first()->id()->destination;
    Connection* tConnectionFirst = new Connection(tConnectionFirstId);
    *tConnectionFirst = *tConnections.first();
    delete tConnections.first();
    tConnections.replace(0, tConnectionFirst);

    // Fix the last connection
    Connection::Id tConnectionLastId;
    tConnectionLastId.origin = tConnections.first()->id()->origin;
    tConnectionLastId.destination = tDestination;
    Connection* tConnectionLast = new Connection(tConnectionLastId);
    *tConnectionLast = *tConnections.last();
    delete tConnections.last();
    tConnections.replace(tConnections.size()-1, tConnectionLast);

    // Construct the object
    Journey::Id tJourneyId;
    tJourneyId.origin = tOrigin;
    tJourneyId.destination = tDestination;
    Journey* oJourney = new Journey(tJourneyId);
    // TODO oJourney->setLines(tLines);
    return oJourney;
}

Stop* ConnectionsReader::readStop(Vehicle*& iVehicle, Station*& iTerminus)
{
    // Process the attributes
    int tDelay = 0;
    if (mReader.attributes().hasAttribute("delay"))
    {
        QStringRef tDelayString = mReader.attributes().value("delay");

        tDelay = tDelayString.toString().toInt();
    }

    // Process the tags
    Station* tStation;
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
    Stop::Id tStopId;
    tStopId.datetime = tDatetime;
    tStopId.station = tStation;
    Stop *oStop = new Stop(tStopId);
    oStop->setPlatform(tPlatform);
    return oStop;
}

Vehicle* ConnectionsReader::readVehicle()
{
    // Process the contents
    QString tVehicleGuid = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    Vehicle::Id tVehicleId;
    tVehicleId.guid = tVehicleGuid;
    return new Vehicle(tVehicleId);   // TODO: look up
}

int ConnectionsReader::readPlatform()
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

QDateTime ConnectionsReader::readDatetime()
{
    // Process the contents
    QString tUnixtime = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return QDateTime::fromTime_t(tUnixtime.toUInt());
}

Station* ConnectionsReader::readStation()
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
    return new Station(tStationId); // TODO: lookup
}

QList<Connection*> ConnectionsReader::readVias(QList<Vehicle*>& iVehicles, QList<Station*>& iDirections)
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
    QList<Connection*> tConnections;
    Vehicle* tVehicle;
    Station* tDirection;
    tConnections << new Connection(Connection::Id());
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
                Connection* tConnection = readVia(tVehicle, tDirection);
                iVehicles << tVehicle;
                iDirections << tDirection;

                Connection::Id tConnectionLastId;
                tConnectionLastId.origin = tConnections.last()->id()->origin;
                tConnectionLastId.destination = tConnection->id()->destination;
                Connection* tConnectionLast = new Connection(tConnectionLastId);
                *tConnectionLast = *tConnections.last();
                delete tConnections.last();
                tConnections.replace(tConnections.size()-1, tConnectionLast);

                tConnections << tConnection;
            }
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    if (tConnections.size() != tNumber+1)
        mReader.raiseError("advertised nubmer of vias did not match the actual amount");
    return tConnections;
}

Connection* ConnectionsReader::readVia(Vehicle*& iVehicle, Station*& iDirection)
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
    Station *tArrival, *tDeparture;
    QString tVehicleDummy, tDepartureDummy;
    Station *tStation, *tTerminus;
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
                tDeparture = readStop(tVehicleDummy, tDepartureDummy);
            else if (mReader.name() == "arrival")
                tArrival = readStop(tVehicleDummy, tDepartureDummy);
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
    Connection* oLine;
    oLine.departure = tDeparture;
    oLine.arrival = tArrival;
    return oLine;
}


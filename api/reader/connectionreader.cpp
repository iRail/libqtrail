//
// Configuration
//

// Includes
#include "connectionreader.h"
#include <QStringRef>
// Namespaces
using namespace iRail;


//
// Construction and destruction
//

ConnectionReader::ConnectionReader(const QList<StationPointer>* iStations)
{
    mStations = iStations;
    mConnections = 0;
}

QList<ConnectionPointer>* ConnectionReader::connections()
{
    return mConnections;
}


//
// Tag readers
//

void ConnectionReader::readDocument()
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

void ConnectionReader::readConnections()
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
        QStringRef tVersionString = mReader.attributes().value("timestamp");

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
                *mConnections << ConnectionPointer(readConnection());
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

}

Connection* ConnectionReader::readConnection()
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
    Connection::POI tDeparture, tArrival;
    QList<Connection::Line> tLines;
    tLines << Connection::Line(Connection::POI(), Connection::POI());
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
                tDeparture = readPOI();
            else if (mReader.name() == "arrival")
                tArrival = readPOI();
            else if (mReader.name() == "vias")
                tLines = readVias();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    Connection *oConnection = new Connection(tDeparture, tArrival);
    tLines.first().departure = tDeparture;
    tLines.last().arrival = tArrival;
    oConnection->setLines(tLines);
    return oConnection;
}

Connection::POI ConnectionReader::readPOI()
{
    // Process the attributes
    int tDelay = 0;
    if (mReader.attributes().hasAttribute("delay"))
    {
        QStringRef tDelayString = mReader.attributes().value("delay");

        tDelay = tDelayString.toString().toInt();
    }

    // Process the tags
    StationPointer tStation;
    QString tVehicle;
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
            if (mReader.name() == "vehicle")
                tVehicle = readVehicle();
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
    Connection::POI oPOI;
    oPOI.station = tStation;
    oPOI.datetime = tDatetime;
    oPOI.vehicle = tVehicle;
    oPOI.delay = tDelay;
    oPOI.platform = tPlatform;
    return oPOI;
}

QString ConnectionReader::readVehicle()
{
    // Process the contents
    QString oVehicle = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return oVehicle;
}

int ConnectionReader::readPlatform()
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

QDateTime ConnectionReader::readDatetime()
{
    // Process the attributes
    QString tUnixtime = mReader.readElementText();
    QDateTime oDatetime = QDateTime::fromTime_t(tUnixtime.toUInt());
    if (mReader.isEndElement())
        mReader.readNext();

    return oDatetime;
}

StationPointer ConnectionReader::readStation()
{
    // Fetch the station id (we don't need the other stuff)
    if (!mReader.attributes().hasAttribute("id"))
        mReader.raiseError("station without id");
    QString tId = mReader.attributes().value("id").toString();
    mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Lookup the station
    QListIterator<StationPointer> tStationIterator(*mStations);
    while (tStationIterator.hasNext() && tStationIterator.peekNext()->id() != tId)
    {
        tStationIterator.next();
    }
    if (! tStationIterator.hasNext())
        mReader.raiseError("unknown station id");
    return tStationIterator.next();
}

QList<Connection::Line> ConnectionReader::readVias()
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
    QList<Connection::Line> tLines;
    tLines << Connection::Line(Connection::POI(), Connection::POI());
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
                Connection::Line tLine = readVia();
                tLines.last().arrival = tLine.arrival;
                tLines << Connection::Line(tLine.departure, Connection::POI());
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

Connection::Line ConnectionReader::readVia()
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
    Connection::POI tArrival, tDeparture;
    StationPointer tStation;
    QString tVehicle;
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
                tDeparture = readPOI();
            else if (mReader.name() == "arrival")
                tArrival = readPOI();
            else if (mReader.name() == "vehicle")
                tVehicle = readVehicle();
            else if (mReader.name() == "station")
                tStation = readStation();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    tArrival.vehicle = tVehicle;
    tArrival.station = tStation;
    tDeparture.station = tStation;
    Connection::Line oLine(tDeparture, tArrival);
    return oLine;
}


//
// Auxiliary
//

void ConnectionReader::allocate()
{
    mConnections = new QList<ConnectionPointer>();
}

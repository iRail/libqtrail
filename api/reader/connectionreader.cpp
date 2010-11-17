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
    QString tVehicleDeparture, tVehicleArrival;   //  NOTE TO READER: the iRail API _really_ sucks
    QList<QString> tVehicles;                     //  when it comes to connections and via's...
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
                tDeparture = readPOI(tVehicleDeparture);
            else if (mReader.name() == "arrival")
                tArrival = readPOI(tVehicleArrival);
            else if (mReader.name() == "vias")
                tLines = readVias(tVehicles);
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Fix the via/connection vehicle counterintuitiveness
    if (tVehicles.size() == 0)
        tVehicles << tVehicleDeparture;
    tVehicles << tVehicleArrival;
    Q_ASSERT(tVehicles.size() == tLines.size());
    for (int i = 0; i < tLines.size(); i++)
        tLines[i].vehicle = tVehicles.at(i);

    // Construct the object
    Connection *oConnection = new Connection(tDeparture, tArrival);
    tLines.first().departure = tDeparture;
    tLines.last().arrival = tArrival;
    oConnection->setLines(tLines);
    return oConnection;
}

Connection::POI ConnectionReader::readPOI(QString& iVehicle)
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
                iVehicle = readVehicle();
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
    // Process the contents
    QString tUnixtime = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return QDateTime::fromTime_t(tUnixtime.toUInt());
}

StationPointer ConnectionReader::readStation()
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
    QListIterator<StationPointer> tStationIterator(*mStations);
    while (tStationIterator.hasNext() && tStationIterator.peekNext()->id() != tStationId)
    {
        tStationIterator.next();
    }
    if (! tStationIterator.hasNext())
        mReader.raiseError("unknown station id");
    return tStationIterator.next();
}

QList<Connection::Line> ConnectionReader::readVias(QList<QString>& iVehicles)
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
    QString tVehicle;
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
                Connection::Line tLine = readVia(tVehicle);
                iVehicles << tVehicle;
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

Connection::Line ConnectionReader::readVia(QString& iVehicle)
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
    QString tVehicleDummy;
    StationPointer tStation;
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
                tDeparture = readPOI(tVehicleDummy);
            else if (mReader.name() == "arrival")
                tArrival = readPOI(tVehicleDummy);
            else if (mReader.name() == "vehicle")
                iVehicle = readVehicle();
            else if (mReader.name() == "station")
                tStation = readStation();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
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

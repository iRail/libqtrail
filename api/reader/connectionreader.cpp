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

QList<ConnectionPointer> ConnectionReader::getConnections()
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
                mConnections << ConnectionPointer(readConnection());
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
    QList<Connection::Transfer> tTransfers;
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
                tDeparture = readPOI(Connection::Departure);
            else if (mReader.name() == "arrival")
                tArrival = readPOI(Connection::Arrival);
            else if (mReader.name() == "vias")
                tTransfers = readVias();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    Connection::Transfer tTransfer;
    tTransfer.arrival = tArrival;
    tTransfer.departure = tDeparture;
    Connection *oConnection = new Connection(tTransfer);
    if (tTransfers.size() > 0)
    {
        oConnection->setTransfers(tTransfers);
    }
    return oConnection;
}

Connection::POI ConnectionReader::readPOI(Connection::POIType iType)
{
    // Process the attributes
    int tDelay = 0;
    if (mReader.attributes().hasAttribute("delay"))
    {
        QStringRef tDelayString = mReader.attributes().value("delay");

        tDelay = tDelayString.toString().toInt();
    }

    // Process the tags
    QString tVehicle, tStation;
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
    oPOI.type = iType;
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
    QDateTime oDatetime;
    if (mReader.attributes().hasAttribute("formatted"))
    {
        QStringRef tDatetimeString = mReader.attributes().value("formatted");

        oDatetime = QDateTime::fromString(tDatetimeString.toString(), "yyyy-MM-dd'T'HH:mm'Z'");
    }
    else
        mReader.raiseError("could not find time formatted attribute");

    // Ditch the contents (unixtime, meh)
    mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return oDatetime;

}

QString ConnectionReader::readStation()
{
    // Process the contents
    // TODO: cache lookup
    QString oStation = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    return oStation;

}

QList<Connection::Transfer> ConnectionReader::readVias()
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
    QList<Connection::Transfer> tTransfers;
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
                Connection::Transfer tTransfer = readVia();
                if (tTransfers.size() > 0)
                {
                    tTransfers.back().departure.vehicle = tTransfer.arrival.vehicle;
                }
                tTransfers << tTransfer;
            }
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    if (tTransfers.size() != tNumber)
        mReader.raiseError("advertised nubmer of vias did not match the actual amount");
    return tTransfers;
}

Connection::Transfer ConnectionReader::readVia()
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
    QString tStation, tVehicle;
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
                tDeparture = readPOI(Connection::Departure);
            else if (mReader.name() == "arrival")
                tArrival = readPOI(Connection::Arrival);
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
    Connection::Transfer oTransfer;
    oTransfer.arrival = tArrival;
    oTransfer.departure = tDeparture;
    return oTransfer;
}


//
// Auxiliary
//

void ConnectionReader::reset()
{
    mConnections.clear();
}

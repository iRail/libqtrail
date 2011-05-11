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

struct ConnectionData
{
    ConnectionData()
    {
        delay = 0;
        finished = false;
    }

    Stop const* origin;
    Stop const* destination;
    Station const* terminus;
    Vehicle const* vehicle;
    uint delay;
    bool finished;
};

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
    QList<ConnectionData> tConnectionData;
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
                readConnectionOrigin(tConnectionData);
            else if (mReader.name() == "arrival")
                readConnectionDestination(tConnectionData);
            else if (mReader.name() == "vias")
                readVias(tConnectionData);
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the object
    Journey::Id tJourneyId;
    tJourneyId.origin = tOrigin;
    tJourneyId.destination = tDestination;
    Journey* oJourney = new Journey(tJourneyId);
    // TODO oJourney->setLines(tLines);
    return oJourney;
}

void ConnectionsReader::readStopFields(uint& oDelay, Station*& oStation, QDateTime& oDatetime, Vehicle*& oVehicle, uint& oPlatform, Station*& oTerminus)
{
    // Process the attributes
    oDelay = 0;
    if (mReader.attributes().hasAttribute("delay"))
    {
        QStringRef tDelayString = mReader.attributes().value("delay");

        oDelay = tDelayString.toString().toInt();
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
            if (mReader.name() == "vehicle")
                oVehicle = readVehicle();
            else if (mReader.name() == "direction")
                oTerminus = readStation();
            else if (mReader.name() == "platform")
                oPlatform = readPlatform();
            else if (mReader.name() == "time")
                oDatetime = readDatetime();
            else if (mReader.name() == "station")
                oStation = readStation();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }
}


void ConnectionsReader::readConnectionOrigin(QList<ConnectionData>& iConnectionData)
{
    // Read fields
    uint& tDelay;
    Station* tStation;
    DateTime tDatetime;
    ehicle* tVehicle;
    uint tPlatform;
    Station* tTerminus;
    readStopFields(tDelay, tStation, tDatetime, tVehicle, tPlatform, tTerminus);

    // Construct the stop
    Stop::Id tStopId;
    tStopId.datetime = tDatetime;
    tStopId.station = tStation;
    Stop *oStop = new Stop(tStopId);
    oStop->setPlatform(tPlatform);

    // Construct the data
    ConnectionData tDepartureData;
    tDepartureData.delay = tDelay;
    tDepartureData.terminus = tTerminus;
    tDepartureData.vehicle = tVehicle;
    tDepartureData.origin = oStop;
    tDepartureData.finished = false;    // destination not yet filled in
    Q_ASSERT(iConnectionData.size() == 0);
    iConnectionData << tDepartureData;
}

void ConnectionsReader::readConnectionDestination(QList<ConnectionData>& iConnectionData)
{
    // Read fields
    uint& tDelay;
    Station* tStation;
    DateTime tDatetime;
    ehicle* tVehicle;
    uint tPlatform;
    Station* tTerminus;
    readStopFields(tDelay, tStation, tDatetime, tVehicle, tPlatform, tTerminus);

    // Construct the stop
    Stop::Id tStopId;
    tStopId.datetime = tDatetime;
    tStopId.station = tStation;
    Stop *oStop = new Stop(tStopId);
    oStop->setPlatform(tPlatform);

    // Construct the data
    ConnectionData tDepartureData;
    tDepartureData.delay = tDelay;
    tDepartureData.terminus = tTerminus;
    tDepartureData.vehicle = tVehicle;
    tDepartureData.destination = oStop;
    tDepartureData.finished = false;    // origin not yet filled in
    Q_ASSERT(iConnectionData.size() == 1);
    iConnectionData << tDepartureData;
}

void ConnectionsReader::readVias(QList<ConnectionData>& iConnectionData)
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
                Stop* tViArrival, tViaDeparture;
                Station* tTerminus;
                Vehicle* tVehicle;
                readVia(tViArrival, tViaDeparture, tTerminus, tVehicle);

                // Look for the first unfinished item
                int i = 0;
                while (i < iConnectionData.size() && iConnectionData.at(i).finished)
                    i++;
                Q_ASSERT(i < iConnectionData.size()-1);

                // Update it with the via origin
                iConnectionData.at(i).destination = tViArrival;
                iConnectionData.at(i).finished = true;

                // Insert the via destination
                ConnectionData tConnectionData;
                tConnectionData.delay = 0;
                tConnectionData.terminus = tTerminus;
                tConnectionData.vehicle = tVehicle;
                tConnectionData.origin = tViaDeparture;
                tConnectionData.finished = false;    // destination not yet filled in
                iConnectionData.insert(i+1, tConnectionData);
            }
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Merge the two last ConnectionData entries
    iConnectionData.last().origin = iConnectionData.at(iConnectionData.size()-2);
    iConnectionData.pop_front();
    iConnectionData.last().finished = true;

    if (iConnectionData.size() != tNumber+1)
        mReader.raiseError("advertised nubmer of vias did not match the actual amount");
}

void ConnectionsReader::readVia(Stop::Id*& oViaArrival, Stop::Id*& oViaDeparture, Station*& oTerminus, Vehicle*& oVehicle)
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
    Station* tStation;
    QDateTime tDatetimeDeparture, tDatetimeArrival;
    uint tPlatformDeparture, tPlatformArrival;
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
            {
                uint& tDummyDelay;
                Station* tDummyStation;
                Vehicle* tDummyVehicle;
                Station* tDummyTerminus;
                readStopFields(tDummyDelay, tDummyStation, tDatetimeDeparture, tDummyVehicle, tPlatformDeparture, tDummyTerminus);
            }
            else if (mReader.name() == "arrival")
            {
                uint& tDummyDelay;
                Station* tDummyStation;
                Vehicle* tDummyVehicle;
                Station* tDummyTerminus;
                readStopFields(tDummyDelay, tDummyStation, tDatetimeArrival, tDummyVehicle, tPlatformArrival, tDummyTerminus);
            }
            else if (mReader.name() == "vehicle")
                oVehicle = readVehicle();
            else if (mReader.name() == "station")
                tStation = readStation();
            else if (mReader.name() == "direction")
                oTerminus = readStation();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    // Construct the arrival stop
    Stop::Id tStopArrivalId;
    tStopArrivalId.datetime = tDatetimeArrival;
    tStopArrivalId.station = tStation;
    oViaArrival = new Stop(tStopArrivalId);
    oViaArrival->setPlatform(tPlatformArrival);

    // Construct the departure stop
    Stop::Id tStopDepartureId;
    tStopDepartureId.datetime = tDatetimeDeparture;
    tStopDepartureId.station = tStation;
    oViaDeparture = new Stop(tStopDepartureId);
    oViaDeparture->setPlatform(tPlatformDeparture);
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

//
// Configuration
//

// Includes
#include "stationsreader.h"
#include <QStringRef>
#include "api/auxiliary.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StationsReader::StationsReader()
{
}


//
// Reader interface
//

void StationsReader::readDocument()
{
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isStartElement())
        {
            if (mReader.name() == "stations")
                mStations = readStations();
            else if (mReader.name() == "error")
                readError();
            else
                mReader.raiseError("could not find stations index");
        }
        else
            mReader.readNext();
    }
}


//
// Basic I/O
//


double StationsReader::version() const
{
    return mVersion;
}

QDateTime StationsReader::timestamp() const
{
    return mTimestamp;
}

QList<Station*> StationsReader::stations() const
{
    return mStations;
}


//
// Tag readers
//

QList<Station*> StationsReader::readStations()
{
    // Process the attributes
    QList<Station*> oStations;
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
            oStations.reserve(tCount);
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
            if (mReader.name() == "station")
                oStations << readStation();
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

    return oStations;
}

Station* StationsReader::readStation()
{
    // Process the attributes
    if (! mReader.attributes().hasAttribute("id"))
        mReader.raiseError("station without id");
    QString tGuid = mReader.attributes().value("id").toString();
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
    QString tName = capitalize(mReader.readElementText());
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    Station::Id tId;
    tId.guid = tGuid;
    Station* oStation = new Station(tId);
    oStation->setName(tName);
    oStation->setLocation(tLocation);
    return oStation;
}

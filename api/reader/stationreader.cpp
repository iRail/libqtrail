//
// Configuration
//

// Includes
#include "stationreader.h"
#include <QStringRef>
#include "api/auxiliary.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StationReader::StationReader()
{
}


//
// Reader interface
//

void StationReader::readDocument()
{
    mReader.readNext();
    while (!mReader.atEnd())
    {
        if (mReader.isStartElement())
        {
            if (mReader.name() == "stations")
                readStations();
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


double StationReader::version() const
{
    return mVersion;
}

QDateTime StationReader::timestamp() const
{
    return mTimestamp;
}

QMap<QString, Station*> StationReader::stations() const
{
    return mStations;
}


//
// Tag readers
//

void StationReader::readStations()
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
            if (mReader.name() == "station")
            {
                Station* tStation = readStation();
                mStations.insert(tStation->id(), tStation);
            }
            else
                skipUnknownElement();
        }
        else
            mReader.readNext();
    }

}

Station* StationReader::readStation()
{
    // Process the attributes
    if (! mReader.attributes().hasAttribute("id"))
        mReader.raiseError("station without id");
    QString tId = mReader.attributes().value("id").toString();
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
    Station* oStation = new Station(tId);
    oStation->setName(tName);
    oStation->setLocation(tLocation);
    return oStation;
}

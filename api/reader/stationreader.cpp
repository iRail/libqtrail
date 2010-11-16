//
// Configuration
//

// Includes
#include "stationreader.h"
#include <QStringRef>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

StationReader::StationReader()
{
    mStations = 0;
}

QList<StationPointer>* StationReader::stations()
{
    return mStations;
}


//
// Tag readers
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

void StationReader::readStations()
{
    // Process the attributes
    if (mReader.attributes().hasAttribute("timestamp"))
    {
        QStringRef tTimestampString = mReader.attributes().value("timestamp");

        // TODO: when Qt 4.8 gets released, QStringRef
        //       will natively implement these
        //       convenience functionality
        //       http://qt.gitorious.org/qt/qt/merge_requests/625
        int tDay = tTimestampString.toString().midRef(0, 2).toString().toInt();
        int tMonth = tTimestampString.toString().midRef(2, 2).toString().toInt();
        int tYear = tTimestampString.toString().midRef(4, 2).toString().toInt() + 2000;

        mTimestamp = QDateTime(QDate(tYear, tMonth, tDay));
    }
    else
        mReader.raiseError("could not find stations timestamp attribute");

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
                *mStations << StationPointer(readStation());
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
    Location* tLocation = 0;
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
        tLocation = new Location(tLongitude, tLatitude);
    }
    if (! mReader.attributes().hasAttribute("id"))
        mReader.raiseError("station without id");
    QString tId = mReader.attributes().value("id").toString();

    // Process the contents
    QString tName = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    // Construct the object
    Station *oStation = new Station(tId);
    oStation->setName(tName);
    if (tLocation != 0)
    {
        oStation->setLocation(*tLocation);
        delete tLocation;
    }
    return oStation;
}


//
// Auxiliary
//

void StationReader::allocate()
{
    mStations = new QList<StationPointer>();
}

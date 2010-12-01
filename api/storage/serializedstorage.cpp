//
// Configuration
//

// Includes
#include "serializedstorage.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

SerializedStorage::SerializedStorage() : MemoryStorage()
{
}


//
// Data I/O
//

void SerializedStorage::serialize(QDataStream& iStream)
{
    // Stations
    if (stations() != 0)
    {
        iStream << true;

        iStream << stationsTimestamp();

        iStream << stations()->count();
        QMap<QString, StationPointer>::const_iterator i;
        for (i = stations()->begin(); i != stations()->end(); ++i)
        {
            iStream << i.key();
            StationPointer tStation = i.value();
            tStation->operator <<(iStream);
        }
    }
    else
        iStream << false;
}

void SerializedStorage::deserialize(QDataStream& iStream)
{
    bool tHasStations;
    iStream >> tHasStations;
    if (tHasStations)
    {
        QDateTime tStationsTimestamp;
        iStream >> tStationsTimestamp;

        unsigned int tStationCount;
        iStream >> tStationCount;
        QMap<QString, StationPointer> tStations;
        for (unsigned int i = 0; i < tStationCount; i++)
        {
            QString key;
            iStream >> key;
            Station *value = new Station("dummy");
            value->operator >>(iStream);
            tStations.insert(key, StationPointer(value));
        }

        setStations(tStations, tStationsTimestamp);
    }
}

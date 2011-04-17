//
// Configuration
//

// Includes
#include "parser.h"
#include "reader/stationreader.h"
#include "reader/connectionreader.h"
#include "reader/vehiclereader.h"
#include "reader/liveboardreader.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

Parser::Parser() : mException("this is a base exception which should never be thrown")
{    
}


//
// Parsing routines
//

QMap<QString, StationPointer>* Parser::parseStations(QIODevice *iDevice, QDateTime& oTimestamp) throw(ParserException)
{
    // Parse the document
    StationReader tReader;
    tReader.read(iDevice);

    return tReader.stations(oTimestamp);
}

QList<ConnectionPointer>* Parser::parseConnections(QIODevice *iDevice, QDateTime& oTimestamp) throw(ParserException)
{
    // Parse the document
    JourneyReader tReader;
    tReader.read(iDevice);

    return tReader.connections(oTimestamp);
}

VehiclePointer* Parser::parseVehicle(QIODevice *iDevice, QDateTime& oTimestamp) throw(ParserException)
{
    // Parse the document
    StopReader tReader;
    tReader.read(iDevice);

    return tReader.vehicle(oTimestamp);
}

LiveboardPointer* Parser::parseLiveboard(QIODevice *iDevice, QDateTime& oTimestamp) throw(ParserException)
{
    // Parse the document
    DepartureReader tReader;
    tReader.read(iDevice);

    return tReader.liveboard(oTimestamp);
}

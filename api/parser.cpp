//
// Configuration
//

// Includes
#include "parser.h"
#include "reader/stationreader.h"
#include "reader/connectionreader.h"
#include "reader/vehiclereader.h"

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

QList<StationPointer>* Parser::parseStations(QIODevice *iDevice) throw(ParserException)
{
    // Parse the document
    StationReader tReader;
    tReader.read(iDevice);

    return tReader.stations();
}

QList<ConnectionPointer>* Parser::parseConnections(const QList<StationPointer>* iStations, QIODevice *iDevice) throw(ParserException)
{
    // Parse the document
    ConnectionReader tReader(iStations);
    tReader.read(iDevice);

    return tReader.connections();
}

VehiclePointer Parser::parseVehicle(const QList<StationPointer>* iStations, QIODevice *iDevice) throw(ParserException)
{
    // Parse the document
    VehicleReader tReader(iStations);
    tReader.read(iDevice);

    return tReader.vehicle();
}

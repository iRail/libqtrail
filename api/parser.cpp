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

QMap<QString, StationPointer>* Parser::parseStations(QIODevice *iDevice) throw(ParserException)
{
    // Parse the document
    StationReader tReader;
    tReader.read(iDevice);

    return tReader.stations();
}

QList<ConnectionPointer>* Parser::parseConnections(QIODevice *iDevice) throw(ParserException)
{
    // Parse the document
    ConnectionReader tReader;
    tReader.read(iDevice);

    return tReader.connections();
}

VehiclePointer* Parser::parseVehicle(QIODevice *iDevice) throw(ParserException)
{
    // Parse the document
    VehicleReader tReader;
    tReader.read(iDevice);

    return tReader.vehicle();
}

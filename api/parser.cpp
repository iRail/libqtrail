//
// Configuration
//

// Includes
#include "parser.h"
#include "reader/stationreader.h"
#include "reader/connectionreader.h"

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

    return new QList<StationPointer>(tReader.getStations());
}

QList<ConnectionPointer>* Parser::parseConnections(QIODevice *iDevice) throw(ParserException)
{
    // Parse the document
    ConnectionReader tReader;
    tReader.read(iDevice);

    return new QList<ConnectionPointer>(tReader.getConnections());
}


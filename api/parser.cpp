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
// Validating routines
//

#ifdef BETRAINS_VALIDATINGXML

void Parser::validateStations(QXmlInputSource& iXmlInputSource) throw(ParserException)
{
    validate(iXmlInputSource, QUrl("qrc:parser/schemas/stations.xsd"));
}

#endif // BETRAINS_VALIDATINGXML


//
// Parsing routines
//

QList<StationPointer> Parser::parseStations(QIODevice *iDevice) throw(ParserException)
{
    // Parse the document
    StationReader tReader;
    tReader.read(iDevice);

    return tReader.getStations();
}

QList<ConnectionPointer> Parser::parseConnections(QIODevice *iDevice) throw(ParserException)
{
    // Parse the document
    ConnectionReader tReader;
    tReader.read(iDevice);

    return tReader.getConnections();
}



//
// Auxiliary
//

#ifdef BETRAINS_VALIDATINGXML
void Parser::validate(const QXmlInputSource& iXml, const QUrl& iSchemaURL) throw(ParserException)
{
    // Load the schema
    MessageHandler tMessageHandler;
    QXmlSchema tSchema;
    if (!tSchema.load(iSchemaURL))
        throw ParserException("invalid schema");

    // Validate the document
    QXmlSchemaValidator tValidator(tSchema);
    tValidator.setMessageHandler(&tMessageHandler);
    tSchema.setMessageHandler(&tMessageHandler);
    if (!tValidator.validate(iXml.data()))      // This fails somehow, without reporting any error (even when not using a MessageHandler)
    {
        qDebug() << "Error while validating (validator.validate returned false), an error should follow now";
        throw ParserException(tMessageHandler);
    }
}
#endif // BETRAINS_VALIDATINGXML

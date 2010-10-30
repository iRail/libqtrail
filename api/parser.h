//
// Configuration
//

// Include guard
#ifndef PARSER_H
#define PARSER_H

// Includes
#include <QtNetwork/QNetworkReply>
#include <QList>
#include <QtXml/QXmlSimpleReader>
#include <QtXml/QXmlStreamReader>
#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include "station.h"
#include "connection.h"
#include "exception/parserexception.h"
#include <QBuffer>

// Optional includes
#ifdef BETRAINS_VALIDATINGXML
#include "parser/messagehandler.h"
#endif // BETRAINS_VALIDATINGXML

/*
 This class provides the raw translation between the replies of the several API pages (trains.php, stations.php, etc)
 and their local counterpart.
 */

namespace iRail
{
    class Parser : public QObject
    {
    Q_OBJECT
    public:
        // Construction and destruction
        Parser();

        // Validation routines
#ifdef BETRAINS_VALIDATINGXML
        void validateStations(QXmlInputSource& iXmlInputSource) throw(ParserException);
        void validateConnections(QXmlInputSource& iXmlInputSource) throw(ParserException);
#endif // BETRAINS_VALIDATINGXML

        // Parsing routines
        QList<StationPointer>* parseStations(QIODevice *iDevice) throw(ParserException);
        QList<ConnectionPointer>* parseConnections(QIODevice *iDevice) throw(ParserException);

    private:
        // Member data
        ParserException mException;

        // Auxiliary
#ifdef BETRAINS_VALIDATINGXML
        void validate(const QXmlInputSource& iXml, const QUrl& iSchemaURL) throw(ParserException);
#endif // BETRAINS_VALIDATINGXML
    };
}

#endif // PARSER_H

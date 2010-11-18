//
// Configuration
//

// Include guard
#ifndef PARSER_H
#define PARSER_H

// Includes
#include <QtNetwork/QNetworkReply>
#include <QMap>
#include <QList>
#include <QtXml/QXmlSimpleReader>
#include <QtXml/QXmlStreamReader>
#include <QBuffer>
#include "station.h"
#include "connection.h"
#include "vehicle.h"
#include "liveboard.h"
#include "exception/parserexception.h"

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

        // Parsing routines
        QMap<QString, StationPointer>* parseStations(QIODevice *iDevice) throw(ParserException);
        QList<ConnectionPointer>* parseConnections(QIODevice *iDevice) throw(ParserException);
        VehiclePointer* parseVehicle(QIODevice *iDevice) throw(ParserException);
        LiveboardPointer* parseLiveboard(QIODevice *iDevice) throw(ParserException);

    private:
        // Member data
        ParserException mException;
    };
}

#endif // PARSER_H

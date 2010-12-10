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

/*!
  \class Parser

  \brief The Parser class serves as a a thin XML-parser agnostic
  wrapper around the different readers. It contains a method
  for each specialized reader, each accepting a device to read
  from, and resulting in a set of objects the reader produces.

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
        QMap<QString, StationPointer>* parseStations(QIODevice *iDevice, QDateTime& oTimestamp) throw(ParserException);
        QList<ConnectionPointer>* parseConnections(QIODevice *iDevice, QDateTime& oTimestamp) throw(ParserException);
        VehiclePointer* parseVehicle(QIODevice *iDevice, QDateTime& oTimestamp) throw(ParserException);
        LiveboardPointer* parseLiveboard(QIODevice *iDevice, QDateTime& oTimestamp) throw(ParserException);

    private:
        // Member data
        ParserException mException;
    };
}

#endif // PARSER_H

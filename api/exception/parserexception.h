//
// Configuration
//

// Include guard
#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H

// Includes
#include <QString>
#include <QtXml/QXmlParseException>
#include "../parser/messagehandler.h"
#include "../exception.h"
#include <QDebug>

// Optional includes
#ifdef BETRAINS_VALIDATINGXML
#include "../parser/messagehandler.h"
#endif // BETRAINS_VALIDATINGXML

/*
 TODO
    - Print offending XML
    - Save the exact request parameters
 */

namespace iRail
{
    class ParserException : public Exception
    {
    public:
        // Construction and destruction
        ParserException(const QString& iMessage) : Exception(iMessage)
        {
        }
#ifdef BETRAINS_VALIDATINGXML
        ParserException(const MessageHandler& iMessageHandler) : Exception(iMessageHandler.getDescription())
        {
            // TODO: do something more (source location)
        }
#endif // BETRAINS_VALIDATINGXML
        ParserException(const QXmlParseException& iException) : Exception(iException.message())
        {
            // TODO: do something more
        }

        // Auxiliary
        virtual const QString toString() const throw()
        {
            return "parser exception | " + what();
        }
    };

}

#endif // PARSEREXCEPTION_H

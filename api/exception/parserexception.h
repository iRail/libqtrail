//
// Configuration
//

// Include guard
#ifndef PARSEREXCEPTION_H
#define PARSEREXCEPTION_H

// Includes
#include <QString>
#include <QtXml/QXmlParseException>
#include "../exception.h"

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

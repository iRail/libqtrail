//
// Configuration
//

// Include guard
#ifndef NETWORKEXCEPTION_H
#define NETWORKEXCEPTION_H

// Includes
#include <QString>
#include "../exception.h"

/*
 TODO
    - Print offending XML
    - Save the exact request parameters
 */

namespace iRail
{
    class NetworkException : public Exception
    {
    public:
        // Construction and destruction
        NetworkException(const QString& iMessage) : Exception(iMessage)
        {
        }

        // Auxiliary
        virtual const QString toString() const throw()
        {
            return "network exception | " + what();
        }
    };

}

#endif // NETWORKEXCEPTION_H

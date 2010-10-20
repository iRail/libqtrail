//
// Configuration
//

// Include guard
#ifndef STORAGEEXCEPTION_H
#define STORAGEEXCEPTION_H

// Includes
#include <QString>
#include "../exception.h"

/*
 TODO
    - Print cache contents
 */

namespace iRail
{
    class StorageException : public Exception
    {
    public:
        // Construction and destruction
        StorageException(const QString& iMessage) : Exception(iMessage)
        {
        }

        // Auxiliary
        virtual const QString toString() const throw()
        {
            return "storage exception | " + what();
        }
    };

}

#endif // STORAGEEXCEPTION_H

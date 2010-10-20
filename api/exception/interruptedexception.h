//
// Configuration
//

// Include guard
#ifndef INTERRUPTEDEXCEPTION_H
#define INTERRUPTEDEXCEPTION_H

// Includes
#include <QString>
#include "../exception.h"

/*
 TODO
    - Save progress upon halt
 */

namespace iRail
{
    class InterruptedException : public Exception
    {
    public:
        // Construction and destruction
        InterruptedException() : Exception()
        {
        }

        // Auxiliary
        virtual const QString toString() const throw()
        {
            return "interrupted exception";
        }
    };

}

#endif // INTERRUPTEDEXCEPTION_H

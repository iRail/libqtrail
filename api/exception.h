//
// Configuration
//

// Include guard
#ifndef EXCEPTION_H
#define EXCEPTION_H

// Includes
#include <QString>

/*
  TODO
    - See if signals apply here
  */

namespace iRail
{
    class Exception
    {
    public:
        // Construction and destruction
        Exception() : mError(QString("unknown error"))
        {

        }
        Exception(QString iError) : mError(iError)
        {
        }

        // Operators
        Exception& operator=(const Exception& other)
        {
            if (this != &other)
            {
                mError = other.mError;
            }
            return *this;
        }


        // Message I/O
        const QString what() const throw()
        {
            return mError;
        }
        // TODO: where() giving a callstack?

        // Auxiliary
        // TODO: provide a more complex debugging data structure then a string?
        virtual const QString toString() const throw()
        {
            return "general exception | " + what();
        }

    private:
        // Member data
        QString mError;
    };

}

#endif // EXCEPTION_H

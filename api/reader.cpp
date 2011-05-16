//
// Configuration
//

// Includes
#include "reader.h"
#include "auxiliary.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

void Reader::read(QIODevice *iDevice) throw(ParserException)
{
    // Setup the reader
    mReader.clear();
    mReader.addData(iDevice->readAll());

    // Read the document
    readDocument();

    // Check the status
    if (mReader.hasError())
    {
        throw ParserException(mReader.errorString());
    }

}

//
// Parsing helpers
//

void Reader::readError()
{
    // Process the contents
    QString oError = mReader.readElementText();
    if (mReader.isEndElement())
        mReader.readNext();

    mReader.raiseError(oError);
}

void Reader::skipUnknownElement()
{
    // TODO: warn about the unknown element
    mReader.readNext();
    while (!mReader.atEnd()) {
        if (mReader.isEndElement()) {
            mReader.readNext();
            break;
        }

        if (mReader.isStartElement()) {
            skipUnknownElement();
        } else {
            mReader.readNext();
        }
    }
}


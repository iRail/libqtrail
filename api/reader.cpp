//
// Configuration
//

// Includes
#include "reader.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

void Reader::read(QIODevice *iDevice) throw(ParserException)
{
    // Setup the reader
    this->allocate();
    mReader.clear();
    mReader.addData(iDevice->readAll());

    // Read the document
    this->readDocument();

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


//
// Auxiliary
//
#include <QDebug>
QString Reader::capitalize(const QString& iString)
{
    if (iString.isEmpty())
        return iString;

    // TODO: QStringRef
    bool split = true;
    QString oString = iString.toLower();
    for (int i = 0; i < oString.length(); i++)
    {
        if (split)
        {
            oString[i] = oString[i].toUpper();
            split = false;
        }
        if (!oString[i].isLetterOrNumber())
            split = true;
    }

    return oString;
}

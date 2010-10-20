//
// Configuration
//

// Include guard
#ifndef READER_H
#define READER_H

// Includes
#include <QXmlStreamReader>
#include "exception/parserexception.h"
#include <QDebug>

namespace iRail
{
    class Reader : public QObject
    {
    Q_OBJECT
    public:
        void read(QIODevice *iDevice) throw(ParserException);   // TODO: incremental parsing, http://doc.trolltech.com/4.6/qxmlstreamreader.html
        virtual void readDocument() = 0;
    protected:
        virtual void reset() {}
        QXmlStreamReader mReader;

        // Auxiliary
        void skipUnknownElement();
    };
}

#endif // READER_H

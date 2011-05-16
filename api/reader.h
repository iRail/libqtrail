//
// Configuration
//

// Include guard
#ifndef READER_H
#define READER_H

// Includes
#include <QXmlStreamReader>
#include "exception/parserexception.h"

/*!
  \class Reader

  \brief The virtual Reader class provides common functionality for
  all specialized readers, used to convert a certain XML stream to
  usable objects. It provides a main entrypoint for the parser to
  use (the read(...) method), which sets up a pull-based XML reader
  and passes it to the virtual readDocument() method.

  */

namespace iRail
{
    class Reader : public QObject
    {
    Q_OBJECT
    public:
        void read(QIODevice *iDevice) throw(ParserException);   // TODO: incremental parsing, http://doc.trolltech.com/4.6/qxmlstreamreader.html
        virtual void readDocument() = 0;
    protected:
        QXmlStreamReader mReader;

        // Parsing helpers
        /*!
          This method allocates heap space for the data to be read,
          and is called when the document is about to be read.
          WARNING: this allocated data is not deallocated, that
          is up to the user!
          */
        void readError();
        void skipUnknownElement();
    };
}

#endif // READER_H

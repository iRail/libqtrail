//
// Configuration
//

// Include guard
#ifndef CONNECTION_H
#define CONNECTION_H

// Includes
#include <QObject>
#include <QSharedPointer>
#include <QMetaType>
#include <QString>
#include <QPair>
#include <QDateTime>
#include <QDebug>
#include <QVariant>
#include "station.h"

namespace iRail
{
    // TODO: use constCast()'s

    class Connection : public QObject
    {
    Q_OBJECT
    // Q_PROPERTY(QList linesVariant READ lines WRITE setLines)
        // TODO: see Qt::properties doc, QList needs to be QVariant<QList<QVariant>>? How to bind with QML?
    public:
        // Auxiliary types
        struct POI
        {
            QString station;
            unsigned int platform;
            unsigned int delay;

            QDateTime datetime;
        };
        struct Line
        {
            Line(POI _departure, POI _arrival) : departure(_departure), arrival(_arrival)
            {

            }

            POI departure;
            POI arrival;
            QString vehicle;
        };

        // Construction and destruction
        Connection(const POI& iDeparture, const POI& iArrival);
        ~Connection();

        // Basic I/O
        POI departure() const;  // TODO: same data at two places, with one being changeable
        POI arrival() const;
        QList<Line> lines() const;
        void setLines(const QList<Line>& iLines);

        // Debugging
        friend QDebug operator<<(QDebug dbg, const Connection &iConnection);

    private:
        POI mDeparture, mArrival;
        QList<Line> mLines;
    };

    typedef QSharedPointer<Connection> ConnectionPointer;
}

Q_DECLARE_METATYPE(iRail::ConnectionPointer)
Q_DECLARE_METATYPE(iRail::Connection::POI)

#endif // CONNECTION_H

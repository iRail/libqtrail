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
            unsigned int delay;
            QDateTime datetime;
            unsigned int platform;

            // Operators
            friend QDataStream &operator<<(QDataStream& iStream, const POI& iPOI);
            friend QDataStream &operator>>(QDataStream& iStream, POI& iPOI);
        };
        struct Line
        {
            POI departure;
            POI arrival;
            QString vehicle;

            // Operators
            friend QDataStream &operator<<(QDataStream& iStream, const Line& iLine);
            friend QDataStream &operator>>(QDataStream& iStream, Line& iLine);
        };

        // Construction and destruction
        Connection(const POI& iDeparture, const POI& iArrival);
        ~Connection();

        // Basic I/O
        POI departure() const;  // TODO: same data at two places, with one being changeable
        POI arrival() const;
        QList<Line> lines() const;
        void setLines(const QList<Line>& iLines);

        // Operators
        friend QDebug &operator<<(QDebug dbg, const Connection& iRequest);
        friend QDataStream &operator<<(QDataStream& iStream, const Connection& iRequest);
        friend QDataStream &operator>>(QDataStream& iStream, Connection& iRequest);

    private:
        POI mDeparture, mArrival;
        QList<Line> mLines;
    };

    typedef QSharedPointer<Connection> ConnectionPointer;

    QDebug &operator<<(QDebug dbg, const Connection& iRequest);
    QDataStream &operator<<(QDataStream& iStream, const Connection::POI& iPOI);
    QDataStream &operator>>(QDataStream& iStream, Connection::POI& iPOI);
    QDataStream &operator<<(QDataStream& iStream, const Connection& iRequest);
    QDataStream &operator>>(QDataStream& iStream, Connection& iRequest);
    QDataStream &operator<<(QDataStream& iStream, const ConnectionPointer& iRequest);
    QDataStream &operator>>(QDataStream& iStream, ConnectionPointer& iRequest);
}

Q_DECLARE_METATYPE(iRail::ConnectionPointer)
Q_DECLARE_METATYPE(iRail::Connection::Line)
Q_DECLARE_METATYPE(iRail::Connection::POI)

#endif // CONNECTION_H

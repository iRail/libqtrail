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

            QDataStream &operator<<(QDataStream& iStream) const
            {
                iStream << station;
                iStream << delay;
                iStream << datetime;
                iStream << platform;

                return iStream;
            }
            QDataStream &operator>>(QDataStream& iStream)
            {
                iStream >> station;
                iStream >> delay;
                iStream >> datetime;
                iStream >> platform;

                return iStream;
            }
        };
        struct Line
        {
            POI departure;
            POI arrival;
            QString vehicle;

            QDataStream &operator<<(QDataStream& iStream) const
            {
                departure.operator <<(iStream);
                arrival.operator <<(iStream);
                iStream << vehicle;

                return iStream;
            }
            QDataStream &operator>>(QDataStream& iStream)
            {
                departure.operator >>(iStream);
                arrival.operator >>(iStream);
                iStream >> vehicle;

                return iStream;
            }
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
        QDebug operator<<(QDebug dbg) const;
        QDataStream &operator<<(QDataStream& iStream) const;
        QDataStream &operator>>(QDataStream& iStream);

    private:
        POI mDeparture, mArrival;
        QList<Line> mLines;
    };

    typedef QSharedPointer<Connection> ConnectionPointer;
}

Q_DECLARE_METATYPE(iRail::ConnectionPointer)
Q_DECLARE_METATYPE(iRail::Connection::Line)
Q_DECLARE_METATYPE(iRail::Connection::POI)

#endif // CONNECTION_H

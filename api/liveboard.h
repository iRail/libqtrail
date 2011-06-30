//
// Configuration
//

// Include guard
#ifndef LIVEBOARD_H
#define LIVEBOARD_H

// Includes
#include <QObject>
#include <QSharedPointer>
#include <QMetaType>
#include <QString>
#include <QDebug>
#include <QDateTime>

namespace iRail
{
    class Liveboard : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(QString station READ station CONSTANT)
    public:
        // Auxiliary types
        struct Departure
        {
            Departure()
            {
                delay = 0;
                platform = 0;
            }

            QString station;
            QString vehicle;
            unsigned int delay;
            QDateTime datetime;
            int platform;

            // Operators
            friend QDataStream &operator<<(QDataStream& iStream, const Liveboard::Departure& iDeparture);
            friend QDataStream &operator>>(QDataStream& iStream, Liveboard::Departure& iDeparture);
        };

        // Construction and destruction
        Liveboard(QString iStation);

        // Basic I/O
        QString station() const;
        QList<Departure> departures() const;
        void setDepartures(const QList<Departure>& iDepartures);

        // Operators
        friend QDebug &operator<<(QDebug dbg, const Liveboard& iLiveboard);
        friend QDataStream &operator<<(QDataStream& iStream, const Liveboard& iLiveboard);
        friend QDataStream &operator>>(QDataStream& iStream, Liveboard& iLiveboard);

    private:
        QString mStation;
        QList<Departure> mDepartures;
    };

    typedef QSharedPointer<Liveboard> LiveboardPointer;

    QDebug &operator<<(QDebug dbg, const Liveboard& iLiveboard);
    QDataStream &operator<<(QDataStream& iStream, const Liveboard& iLiveboard);
    QDataStream &operator>>(QDataStream& iStream, Liveboard& iLiveboard);
    QDataStream &operator<<(QDataStream& iStream, const LiveboardPointer& iLiveboard);
    QDataStream &operator>>(QDataStream& iStream, LiveboardPointer& iLiveboard);
}

Q_DECLARE_METATYPE(iRail::LiveboardPointer)
Q_DECLARE_METATYPE(iRail::Liveboard::Departure)

#endif // LIVEBOARD_H
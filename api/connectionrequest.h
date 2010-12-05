//
// Configuration
//

// Include guard
#ifndef CONNECTIONREQUEST_H
#define CONNECTIONREQUEST_H

// Includes
#include <QDebug>
#include <QObject>
#include <QSharedPointer>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QMetaEnum>
#include <QDataStream>

namespace iRail
{
    // TODO: use constCast()'s
    class ConnectionRequest : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(QString origin READ origin CONSTANT)
    Q_PROPERTY(QString destination READ destination CONSTANT)
    Q_PROPERTY(bool timed READ timed)
    Q_PROPERTY(Time time READ time WRITE setTime)
    Q_ENUMS(TimeType)
    public:
        // Construction and destruction
        ConnectionRequest(const QString& iOrigin, const QString& iDestination);
        ~ConnectionRequest();

        enum TimeType
        {
            Departure,
            Arrival
        };
        Q_ENUMS(TimeType);

        struct Time
        {
            TimeType type;
            QDateTime datetime;

            // Operators
            friend QDataStream &operator<<(QDataStream& iStream, const Time& iTime);
            friend QDataStream &operator>>(QDataStream& iStream, Time& iTime);
        };

        // Basic I/O
        QString origin() const;
        QString destination() const;
        bool timed() const;
        const Time* time() const;
        void setTime(const Time& iTime);
        void setTime(const TimeType& iTimeType, const QDate& iDate, const QTime& iTime);

        // Operators
        friend QDebug &operator<<(QDebug dbg, const ConnectionRequest& iConnectionRequest);
        friend QDataStream &operator<<(QDataStream& iStream, const ConnectionRequest& iConnectionRequest);
        friend QDataStream &operator>>(QDataStream& iStream, ConnectionRequest& iConnectionRequest);

    private:
        QString mOrigin, mDestination;
        bool mTimed;
        Time *mTime;
    };

    typedef QSharedPointer<ConnectionRequest> ConnectionRequestPointer;

    QDebug &operator<<(QDebug dbg, const ConnectionRequest& iConnectionRequest);
    QDataStream &operator<<(QDataStream& iStream, const ConnectionRequest::Time& iTime);
    QDataStream &operator>>(QDataStream& iStream, ConnectionRequest::Time& iTime);
    QDataStream &operator<<(QDataStream& iStream, const ConnectionRequest& iConnectionRequest);
    QDataStream &operator>>(QDataStream& iStream, ConnectionRequest& iConnectionRequest);
    QDataStream &operator<<(QDataStream& iStream, const ConnectionRequestPointer& iConnectionRequest);
    QDataStream &operator>>(QDataStream& iStream, ConnectionRequestPointer& iConnectionRequest);
}

Q_DECLARE_METATYPE(iRail::ConnectionRequestPointer)
#endif // CONNECTIONREQUEST_H

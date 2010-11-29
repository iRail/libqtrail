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

namespace iRail
{
    // TODO: use constCast()'s
    // TODO typeoftransport
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

            QDataStream &operator<<(QDataStream& iStream) const
            {
                const QMetaObject& tMetaObject = ConnectionRequest::staticMetaObject;
                int tEnumIndex = tMetaObject.indexOfEnumerator("TimeType");
                QMetaEnum tMetaEnum = tMetaObject.enumerator(tEnumIndex);

                iStream << tMetaEnum.valueToKey(type);
                iStream << datetime;

                return iStream;
            }
            QDataStream &operator>>(QDataStream& iStream)
            {
                const QMetaObject& tMetaObject = ConnectionRequest::staticMetaObject;
                int tEnumIndex = tMetaObject.indexOfEnumerator("TimeType");
                QMetaEnum tMetaEnum = tMetaObject.enumerator(tEnumIndex);

                char* tEnumValue;
                iStream >> tEnumValue;
                type = static_cast<TimeType>(tMetaEnum.keyToValue(tEnumValue));

                iStream >> datetime;

                return iStream;
            }
        };

        // Basic I/O
        QString origin() const;  // TODO: these should be StationPointers...
        QString destination() const;
        bool timed() const;
        const Time* time() const;
        void setTime(const Time& iTime);
        void setTime(const TimeType& iTimeType, const QDate& iDate, const QTime& iTime);

        // Operators
        QDebug operator<<(QDebug dbg) const;
        QDataStream &operator<<(QDataStream& iStream) const;
        QDataStream &operator>>(QDataStream& iStream);

    private:
        QString mOrigin, mDestination;
        bool mTimed;
        Time *mTime;
    };

    typedef QSharedPointer<ConnectionRequest> ConnectionRequestPointer;
}

Q_DECLARE_METATYPE(iRail::ConnectionRequestPointer)

#endif // CONNECTIONREQUEST_H

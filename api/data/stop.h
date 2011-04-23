//
// Configuration
//

// Include guard
#ifndef STOP_H
#define STOP_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include "api/data/station.h"

namespace iRail
{
    class Stop : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Id id READ id CONSTANT)
    Q_PROPERTY(uint delay READ relay WRITE setDelay)
    Q_PROPERTY(uint platform READ platform WRITE setPlatform)
    public:
        // Construction and destruction
        Stop(Id iId);
        ~Stop();

        // Auxiliary structures
        struct Id
        {
            Station const* station;
            QDateTime datetime;
        };
        enum Roles
        {
          StationRole = Qt::UserRole+1,
          DatetimeRole,
          DelayRole,
          PlatformRole
        };

        // Basic I/O
        Id id() const;
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);
        unsigned int platform() const;
        void setPlatform(unsigned int iPlatform);

        // Operators
        friend bool operator==(const Stop& lhs, const Stop& rhs);
        friend bool operator||(const Stop& lhs, const Stop& rhs);
        friend QDataStream& operator<<(QDataStream& iStream, const Stop& iStop);
        friend QDataStream& operator>>(QDataStream& iStream, Stop& iStop);

    private:
        Q_DISABLE_COPY(Stop);
        Id mId;
        unsigned int mDelay;
        unsigned int mPlatform;
    };

    bool operator==(const Stop& lhs, const Stop& rhs);
    bool operator||(const Stop& lhs, const Stop& rhs);
    QDataStream& operator<<(QDataStream& iStream, const Stop& iStop);
    QDataStream& operator>>(QDataStream& iStream, Stop& iStop);
}

Q_DECLARE_METATYPE(iRail::Stop)
Q_DECLARE_METATYPE(iRail::Stop::Id)

#endif // STOP_H

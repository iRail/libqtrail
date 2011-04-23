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
#include <QHash>
#include "api/data/station.h"

namespace iRail
{
    class Stop : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Id id READ id CONSTANT)
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
            friend inline unsigned int qHash(const Stop::Id& iStopId);
            bool operator==(const Stop::Id& lhs, const Stop::Id& rhs);
        };
        enum Roles
        {
          StationRole = Qt::UserRole+1,
          DatetimeRole,
          PlatformRole
        };

        // Basic I/O
        Id id() const;
        unsigned int platform() const;
        void setPlatform(unsigned int iPlatform);

        // Operators
        friend bool operator==(const Stop& lhs, const Stop& rhs);

    private:
        Q_DISABLE_COPY(Stop);
        Id mId;
        unsigned int mPlatform;
    };

    bool operator==(const Stop& lhs, const Stop& rhs);
    inline unsigned int qHash(const Stop::Id& iStopId);
}

Q_DECLARE_METATYPE(iRail::Stop)
Q_DECLARE_METATYPE(iRail::Stop::Id)

#endif // STOP_H

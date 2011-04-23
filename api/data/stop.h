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
#include "api/data.h"
#include "api/data/station.h"

namespace iRail
{
    class Stop : public Data
    {
    Q_OBJECT
    Q_PROPERTY(uint platform READ platform WRITE setPlatform)
    public:
        // Auxiliary structures
        struct Id : Data::Id
        {
            Station const* station;
            QDateTime datetime;
            friend inline unsigned int qHash(const Stop::Id& iStopId);
            friend bool operator==(const Stop::Id& lhs, const Stop::Id& rhs);
        };
        enum Roles
        {
            StationRole = Qt::UserRole+1,
            DatetimeRole,
            PlatformRole
        };

        // Construction and destruction
        Stop(Id iId);
        ~Stop();

        // Basic I/O
        Id& id() const;
        unsigned int platform() const;
        void setPlatform(unsigned int iPlatform);

        // Operators
        friend bool operator==(const Stop& lhs, const Stop& rhs);
        Stop& operator=(const Stop& other);

    private:
        Id mId;
        unsigned int mPlatform;
    };

    bool operator==(const Stop& lhs, const Stop& rhs);
    inline unsigned int qHash(const Stop::Id& iStopId);
    bool operator==(const Stop::Id& lhs, const Stop::Id& rhs);
}

Q_DECLARE_METATYPE(iRail::Stop::Id)

#endif // STOP_H
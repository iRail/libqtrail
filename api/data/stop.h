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
        struct IId : Data::Id
        {
            Station const* station;
            QDateTime datetime;

            // Operator implementation
            bool equals(const Data::Id& id) const;
            unsigned int hash() const;
        };
        enum Roles
        {
            StationRole = Qt::UserRole+1,
            DatetimeRole,
            PlatformRole
        };

        // Construction and destruction
        Stop(IId iId);
        ~Stop();

        // Basic I/O
        Data::Id& id() const;
        unsigned int platform() const;
        void setPlatform(unsigned int iPlatform);

        // Operator implementation
        bool equals(const Data& data) const;
        Data& assign(const Data& data);

    private:
        IId mId;
        unsigned int mPlatform;
    };
}

#endif // STOP_H

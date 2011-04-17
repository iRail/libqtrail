//
// Configuration
//

// Include guard
#ifndef POI_H
#define POI_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include "api/data/station.h"

namespace iRail
{
    class POI : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(Station station READ station CONSTANT)
    Q_PROPERTY(QDateTime datetime READ datetime CONSTANT)
    Q_PROPERTY(uint delay READ relay WRITE setDelay)
    Q_PROPERTY(uint platform READ platform WRITE setPlatform)
    public:
        // Construction and destruction
        POI(Station const* iStation, const QDateTime& iDatetime);
        ~POI();

        // Auxiliary structures
        enum Roles {
          StationRole = Qt::UserRole+1,
          DatetimeRole,
          DelayRole,
          PlatformRole
        };

        // Basic I/O
        Station const* station() const;
        QDateTime datetime() const;
        unsigned int delay() const;
        void setDelay(unsigned int iDelay);
        unsigned int platform() const;
        void setPlatform(unsigned int iPlatform);

        // Operators
        friend bool operator==(const POI& lhs, const POI& rhs);
        friend bool operator||(const POI& lhs, const POI& rhs);
        friend QDataStream& operator<<(QDataStream& iStream, const POI& iPOI);
        friend QDataStream& operator>>(QDataStream& iStream, POI& iPOI);

    private:
        Q_DISABLE_COPY(POI);
        Station const* mStation;
        QDateTime mDatetime;
        unsigned int mDelay;
        unsigned int mPlatform;
    };

    bool operator==(const POI& lhs, const POI& rhs);
    bool operator||(const POI& lhs, const POI& rhs);
    QDataStream& operator<<(QDataStream& iStream, const POI& iPOI);
    QDataStream& operator>>(QDataStream& iStream, POI& iPOI);
}

Q_DECLARE_METATYPE(iRail::POI)

#endif // POI_H

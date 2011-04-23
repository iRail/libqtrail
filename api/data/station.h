//
// Configuration
//

// Include guard
#ifndef STATION_H
#define STATION_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QPair>
#include "auxiliary/location.h"

namespace iRail
{
    class Station : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(Location location READ location WRITE setLocation)
    public:
        // Auxiliary structures
        typedef QString Id;
        enum Roles {
          IdRole = Qt::UserRole+1,
          NameRole,
          LocationRole
        };

        // Construction and destruction
        Station(Id iId);
        ~Station();

        // Basic I/O
        Id id() const;
        QString name() const;
        void setName(const QString& iName);
        Location const* location() const;
        void setLocation(Location const* iLocation);

        // Operators
        friend bool operator==(const Station& lhs, const Station& rhs);
        friend bool operator||(const Station& lhs, const Station& rhs);
        friend QDataStream& operator<<(QDataStream& iStream, const Station& iStation);
        friend QDataStream& operator>>(QDataStream& iStream, Station& iStation);

    private:
        Q_DISABLE_COPY(Station);
        Id mId;
        QString mName;
        Location const* mLocation;
    };

    bool operator==(const Station& lhs, const Station& rhs);
    bool operator||(const Station& lhs, const Station& rhs);
    QDataStream& operator<<(QDataStream& iStream, const Station& iStation);
    QDataStream& operator>>(QDataStream& iStream, Station& iStation);
}

Q_DECLARE_METATYPE(iRail::Station)

#endif // STATION_H

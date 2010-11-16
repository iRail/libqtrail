//
// Configuration
//

/*
 TODO: thread safety. When moving from QSharedDataPointer to
       QSharedPointer to conserve QObject idioms, we lost
       thread safety...
 */

// Include guard
#ifndef STATION_H
#define STATION_H

// Includes
#include <QObject>
#include <QSharedPointer>
#include <QMetaType>
#include <QString>
#include <QPair>
#include <QDebug>

namespace iRail
{
    // TODO: use constCast()'s
    typedef QPair<qreal, qreal> Location;

    class Station : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool locatable READ locatable)
    Q_PROPERTY(Location location READ location WRITE setLocation)
    public:
        // Construction and destruction
        Station(QString iId);
        ~Station();

        // Basic I/O
        QString id() const;
        QString name() const;
        void setName(const QString& iName);
        const Location* location() const;
        bool locatable() const;
        void setLocation(const Location& iLocation);

        // Debugging
        friend QDebug operator<<(QDebug dbg, const Station &iStation);

    private:
        QString mId;
        QString mName;
        bool mLocatable;
        Location* mLocation;
    };

    typedef QSharedPointer<Station> StationPointer;
}

Q_DECLARE_METATYPE(iRail::StationPointer)

#endif // STATION_H

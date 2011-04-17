//
// Configuration
//

// Include guard
#ifndef JOURNEY_H
#define JOURNEY_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include "poi.h"
#include "station.h"
#include "vehicle.h"

namespace iRail
{
    class Journey : public QObject
    {
    Q_OBJECT
    Q_PROPERTY(POI departure READ departure CONSTANT)
    Q_PROPERTY(POI arrival READ arrival CONSTANT)
    Q_PROPERTY(uint connections READ connections CONSTANT)
    public:
        // Construction and destruction
        Journey(const POI& iDeparture, const POI& iArrival);

        // Basic I/O
        POI departure() const;
        POI arrival() const;

        // Operators
        friend QDataStream &operator<<(QDataStream& iStream, const Journey& iJourney);
        friend QDataStream &operator>>(QDataStream& iStream, Journey& iJourney);

    private:
        POI mDeparture, mArrival;
    };

    QDataStream &operator<<(QDataStream& iStream, const Journey& iJourney);
    QDataStream &operator>>(QDataStream& iStream, Journey& iJourney);
}

Q_DECLARE_METATYPE(iRail::Journey)

#endif // JOURNEY_H

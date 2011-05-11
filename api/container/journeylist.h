//
// Configuration
//

// Include guard
#ifndef JOURNEYLIST_H
#define JOURNEYLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QHash>
#include "api/exception.h"
#include "api/data/journey.h"
#include "api/container.h"

namespace iRail
{
    class JourneyList : public Container
    {
    Q_OBJECT
    private:
        // Construction and destruction
        JourneyList(const Station::Id& iOrigin, const Station::Id& iDestination, QObject* iParent = 0);
        ~JourneyList();

        // Basic I/O
    public:
        Station::Id const* origin() const;
        Station::Id const* destination() const;

    signals:
        // Data reply signals

        // Data processing methods
    private slots:

    private:
        // Member data
        QDateTime mTimestamp;
        Station::Id mOrigin, mDestination;
    };
}

#endif // JOURNEYLIST_H

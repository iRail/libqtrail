//
// Configuration
//

// Include guard
#ifndef CONNECTIONLIST_H
#define CONNECTIONLIST_H

// Includes
#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDateTime>
#include <QHash>
#include "api/exception.h"
#include "api/data/connection.h"
#include "api/data/journey.h"
#include "api/container.h"

namespace iRail
{
    class ConnectionList : public Container<Connection>
    {
    Q_OBJECT
    public:
        // Construction and destruction
        ConnectionList(const Journey::Id& iJourney, QObject* iParent = 0);
        ~ConnectionList();

        // Basic I/O
    public:
        Journey::Id const* journeyId() const;

    private:
        // Member data
        QDateTime mTimestamp;
        Journey::Id mJourneyId;
    };
}

#endif // CONNECTIONLIST_H

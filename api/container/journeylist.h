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
#include "api/requesthelper.h"
#include "api/data/journey.h"
#include "api/container.h"

namespace iRail
{
    class JourneyList : public Container<Journey>,  private RequestHelper
    {
    Q_OBJECT
    public:
        // Construction and destruction
        JourneyList(Station::Id const* iOrigin, Station::Id const* iDestination, QObject* iParent = 0);
        ~JourneyList();

        // Auxiliary types
        enum Type {
            Arrival,
            Departure
        };

        // Basic I/O
    public:
        Station::Id const* origin() const;
        Station::Id const* destination() const;

        // Data request methods
        void fetch();
        void fetch(const QDateTime& iDatetime, JourneyList::Type iType);

    signals:
        // Data reply signals
        void success();
        void failure(const Exception& iException);

        // Data processing methods
    private slots:
        void process();

    private:
        // Member data
        QDateTime mTimestamp;
        Station::Id const *mOrigin, *mDestination;
    };
}

#endif // JOURNEYLIST_H

//
// Configuration
//

// Includes
#include "journeylist.h"
#include "api/reader/connectionsreader.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

JourneyList::JourneyList(const Station::Id& iOrigin, const Station::Id& iDestination, QObject* iParent) : mOrigin(iOrigin), mDestination(iDestination), QAbstractListModel(iParent)
{
    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Journey::OriginRole] = "origin";
    tRoleNames[Journey::DestinationRole] = "destination";
    tRoleNames[Journey::DelayRole] = "delay";
    setRoleNames(tRoleNames);
}

JourneyList::~JourneyList()
{
    qDeleteAll(mJourneys.values());
    mJourneys.clear();
}


//
// Basic I/O
//


Station::Id const* JourneyList::origin() const
{
    return &mOrigin;
}

Station::Id const* JourneyList::destination() const
{
    return &mDestination;
}


//
// Model interface
//

int JourneyList::rowCount(const QModelIndex& iParent) const
{
    Q_UNUSED(iParent);
    return mJourneys.size();
}

QVariant JourneyList::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mJourneys.size()-1) )
        return QVariant();

    // TODO: sort through virtual mapping structure
    Journey* oJourney = mJourneys.values().at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Journey::OriginRole:
        return QVariant::fromValue(oJourney->id()->origin);
    case Journey::DestinationRole:
        return QVariant::fromValue(oJourney->id()->destination);
    case Journey::DelayRole:
        return QVariant::fromValue(oJourney->delay());
    default:
        return QVariant();
    }
}

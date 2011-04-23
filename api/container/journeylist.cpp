//
// Configuration
//

// Includes
#include "journeylist.h"
#include <QString>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

JourneyList::JourneyList(const Stop& iDeparture, const Stop& iArrival, QObject* iParent) : mDeparture(iDeparture), mArrival(iArrival), QAbstractListModel(iParent)
{
    qRegisterMetaType<JourneyList>("JourneyList");
    qRegisterMetaType<JourneyListPointer>("JourneyListPointer");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Journey::OriginRole] = "origin";
    tRoleNames[Journey::DestinationRole] = "destination";
    tRoleNames[Journey::DelayRole] = "delay";
    setRoleNames(tRoleNames);
}


JourneyList::~Connection()
{
}


//
// Basic I/O
//


const Stop& JourneyList::departure() const
{
    return mDeparture;
}

const Stop& JourneyList::arrival() const
{
    return mArrival;
}


//
// Model interface
//

int JourneyList::rowCount(const QModelIndex& iParent) const
{
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
        return QVariant::fromValue(oJourney->origin());
    case Journey::DestinationRole:
        return QVariant::fromValue(oJourney->destination());
    case Journey::DelayRole:
        return QVariant::fromValue(oJourney->delay());
    default:
        return QVariant();
    }
}

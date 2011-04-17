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

JourneyList::JourneyList(const POI& iDeparture, const POI& iArrival, QObject* iParent) : mDeparture(iDeparture), mArrival(iArrival), QAbstractListModel(iParent)
{
    qRegisterMetaType<JourneyList>("JourneyList");

    QHash<int, QByteArray> tRoleNames;
    tRoleNames[Journey::DepartureRole] = "departure";
    tRoleNames[Journey::ArrivalRole] = "arrival";
    setRoleNames(tRoleNames);
}


JourneyList::~Connection()
{
}


//
// Basic I/O
//


const POI& JourneyList::departure() const
{
    return mDeparture;
}

const POI& JourneyList::arrival() const
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

    Journey* oJourney = mJourneys.at(iIndex.row());
    switch (iRole)
    {
    case Qt::DisplayRole:
    case Journey::DepartureRole:
        return QVariant::fromValue(oJourney->departure());
    case Journey::ArrivalRole:
        return QVariant::fromValue(oJourney->arrival());
    default:
        return QVariant();
    }
}


//
// Operators
//

QDataStream& iRail::operator<<(QDataStream& iStream, const JourneyList& iJourneyList)
{
    iStream << iJourneyList.mDeparture;
    iStream << iJourneyList.mArrival;

    iStream << iJourneyList.mJourneys.size();
    foreach (Journey* tJourney, iJourneyList.mJourneys)
        iStream << *tJourney;

    return iStream;
}

QDataStream& iRail::operator>>(QDataStream& iStream, JourneyList& iJourneyList)
{
    iStream >> iJourneyList.mDeparture;
    iStream >> iJourneyList.mArrival;

    int tJourneyCount;
    iStream >> tJourneyCount;
    Q_ASSERT(iJourneyList.mJourneys.size() == 0);
    for (int i = 0; i < tJourneyCount; i++)
    {
        Journey* tJourney;
        iStream >> *tJourney;
        iJourneyList.mJourneys << tJourney;
    }

    return iStream;
}

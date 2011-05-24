//
// Configuration
//

// Includes
#include "container.h"

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

template <class Data>
Container<Data>::Container(QObject *iParent) : QAbstractListModel(iParent)
{
    setRoleNames(roleNames());
}

template <class Data>
Container<Data>::~Container()
{

}


//
// Basic I/O
//

template <class Data>
void Container<Data>::append(Data* iData)
{
    mData.append(iData);
}


//
// Model interface
//

template <class Data>
int Container<Data>::rowCount(const QModelIndex& iParent) const
{
    Q_UNUSED(iParent);
    return mData.size();
}

template <class Data>
Data* Container<Data>::object(const QModelIndex& iIndex) const
{
    if (!iIndex.isValid())
        return 0;
    if (iIndex.row() > (mData.size()-1) )
        return 0;

    return mData.at(iIndex.row());
}

template <class Data>
QVariant Container<Data>::data(const QModelIndex& iIndex, int iRole) const
{
    if (!iIndex.isValid())
        return QVariant();
    if (iIndex.row() > (mData.size()-1) )
        return QVariant();

    Data* tData = mData.at(iIndex.row());

    return tData->field(iRole);
}

template <class Data>
QModelIndex Container<Data>::indexFromItem(const Data* iData) const
{
    Q_ASSERT(iData);
    for(int tRow = 0; tRow < mData.size(); ++tRow)
    {
      if(*mData.at(tRow)->id() == *iData->id())
          return index(tRow);
    }
    return QModelIndex();
}



//
// Data handling
//

template <class Data>
void Container<Data>::clear()
{
    // Remove existing items
    beginRemoveRows(QModelIndex(), 0, mData.size()-1);
    qDeleteAll(mData);
    mData.clear();
    endRemoveRows();
}

template <class Data>
void Container<Data>::replaceData(QList<Data*> iData)
{
    // Clear current data
    clear();

    // Insert new data
    beginInsertRows(QModelIndex(), 0, iData.size()-1);
    mData = iData;
    endInsertRows();
}


//
// Template instantiations
//

#include "data/station.h"
template class iRail::Container<Station>;

#include "data/vehicle.h"
template class iRail::Container<Vehicle>;

#include "data/stop.h"
template class iRail::Container<Stop>;

#include "data/journey.h"
template class iRail::Container<Journey>;

#include "data/connection.h"
template class iRail::Container<Connection>;

#include "data/departure.h"
template class iRail::Container<Departure>;

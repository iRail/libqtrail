//
// Configuration
//

// Include guard
#ifndef SERIALIZEDSTORAGE_H
#define SERIALIZEDSTORAGE_H

// Includes
#include "api/storage.h"
#include "api/station.h"
#include "api/liveboardrequest.h"
#include "api/connectionrequest.h"
#include "memorystorage.h"
#include <QDataStream>

namespace iRail
{
    class SerializedStorage : public MemoryStorage
    {
    Q_OBJECT
    public:
        // Construction and destruction
        SerializedStorage();

        // Data I/O
        void serialize(QDataStream& iStream);
        void deserialize(QDataStream& iSteam);

        // Auxiliary types
        enum VariantType
        {
            LiveboardRequestType,
            ConnectionRequestType
        };
        Q_ENUMS(VariantType)
    };
}

#endif // SERIALIZEDSTORAGE_H

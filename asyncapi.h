//
// Configuration
//

// Include guard
#ifndef ASYNCAPI_H
#define ASYNCAPI_H

/*
 This class serves as high-level wrapper around the iRail API, providing
 objects easy to use within the different GUI's.
 */

// Includes
#include <QUrl>
#include <QList>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "api/station.h"
#include "api/parser.h"
#include "api/exception/networkexception.h"
#include "api/exception/storageexception.h"
#include "api/connectionrequest.h"
#include "api/connection.h"
#include "api/storage.h"

namespace iRail
{
    class AsyncAPI : public QObject
    {
    Q_OBJECT
        // Construction and destruction
    public:
        AsyncAPI(const QString& iClientID, const QString& iClientVersion);
        void setStorage(Storage* iStorage);

        // Cach request methods
    public:
        QList<StationPointer> stations_cache() throw(StorageException);

        // Request slots
    public slots:
        void stations_request();
        void connections_request(ConnectionRequestPointer iConnectionRequest);

        // Processing methods
    private slots:
        void stations_process();
        void connections_process();

        // Network routines
    private slots:
        void network_request(QNetworkRequest iRequest, QObject* iObject, const char* iSlot);
        void network_progress(qint64 iProgress, qint64 totalSteps);
        void network_cleanup();

        // Reply signals
    signals:
        void stations_reply(QList<StationPointer> iStations);
        void connections_reply(QList<ConnectionPointer> iConnections);

        // Messages
    signals:
        void warning(const QString& iMessage);
        void error(const QString& iMessage);
        void fatal(const QString& iMessage);
        void progress(int progress);

        // Member data
    private:
        QString mClientID, mClientVersion;
        QByteArray mUserAgent;
        Storage* mStorage;
        Parser mParser;
        QNetworkAccessManager mNetworkAccessManager;
        QNetworkReply* mNetworkReply;

        // Auxiliary
    private:
        QUrl createBaseURL() const;
        QNetworkRequest getRequest(QUrl iURL) const;
    };
}

#endif // ASYNCAPI_H

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
#include "api/progresshandler.h"
#include "api/station.h"
#include "api/parser.h"
#include "api/exception/networkexception.h"
#include "api/connectionrequest.h"
#include "api/connection.h"

namespace iRail
{
    class AsyncAPI : public QObject
    {
    Q_OBJECT
        // Construction and destruction
    public:
        // TODO: make the API Singleton, with some global init for resources etc
        AsyncAPI(const QString& iClientID, const QString& iClientVersion);

        // Error handling
        bool hasError() const;
        Exception error() const;
        QString errorString() const;

        // Request slots
    public slots:
        virtual void requestStations();
        virtual void requestConnections(ConnectionRequestPointer iConnectionRequest);

        // Processing methods
    private slots:
        void processStations();
        void processConnections();

        // Network routines
    private slots:
        void network_request(QNetworkRequest iRequest, QObject* iObject, const char* iSlot);
        void network_progress(qint64 iProgress, qint64 totalSteps);
        void network_cleanup();

        // Reply signals
    signals:
        void replyStations(QList<StationPointer>* iStations);
        void replyConnections(QList<ConnectionPointer>* iConnections);

        // Progress indicator signals
    signals:
        void progress(int current);
        void action(QString action);

        // Member data
    private:
        QString mClientID, mClientVersion;
        QByteArray mUserAgent;
        Parser mParser;
        QNetworkAccessManager mNetworkAccessManager;
        QNetworkReply* mNetworkReply;
        Exception mError;
        bool mHasError;
        int mProgressLevel;
        int mProgress;
        ProgressHandler mProgressHandler;

        // Auxiliary
    private:
        QUrl createBaseURL() const;
        QNetworkRequest getRequest(QUrl iURL) const;
    };
}

#endif // ASYNCAPI_H

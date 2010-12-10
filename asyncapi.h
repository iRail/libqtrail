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
#include <QMap>
#include <QList>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "api/progresshandler.h"
#include "api/station.h"
#include "api/parser.h"
#include "api/exception/networkexception.h"
#include "api/connectionrequest.h"
#include "api/connection.h"
#include "api/liveboardrequest.h"
#include "api/liveboard.h"

/*!
  \class AsyncAPI

  \brief The AsyncAPI class is the main wrapper around the iRail API.
  As its name indicates, it processes user request in an asynchronous
  manner, returning all data through Qt signals.

  */

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
        virtual void requestVehicle(const QString& iVehicleId);
        virtual void requestLiveboard(LiveboardRequestPointer iLiveboardRequest);

        // Processing methods
    private slots:
        void processStations();
        void processConnections();
        void processVehicle();
        void processLiveboard();

        // Network routines
    private slots:
        void network_request(QNetworkRequest iRequest, QObject* iObject, const char* iSlot);
        void network_progress(qint64 iProgress, qint64 totalSteps);
        void network_cleanup();

        // Reply signals
    signals:
        void replyStations(QMap<QString, StationPointer>* iStations, QDateTime iTimestamp);
        void replyConnections(QList<ConnectionPointer>* iConnections, QDateTime iTimestamp);
        void replyVehicle(VehiclePointer* iVehicle, QDateTime iTimestamp);
        void replyLiveboard(LiveboardPointer* iVehicle, QDateTime iTimestamp);

        // Progress indicator signals
    signals:
        void progress(int current);
        void action(QString action);

        // Member data
    private:
        QString mClientID, mClientVersion, mClientLanguage;
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

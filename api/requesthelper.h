//
// Configuration
//

// Include guard
#ifndef REQUESTHELPER_H
#define REQUESTHELPER_H

// Includes
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QSettings>
#include "exception/networkexception.h"

namespace iRail
{
    class RequestHelper
    {
    public:
        // Construction and destruction
        RequestHelper();

        // Network helpers
    public:
        void networkRequest(QNetworkRequest iRequest, QObject* iObject, const char* iSlot) throw(NetworkException);
        QNetworkReply* networkReply();
        void networkCleanup();

        // Auxiliary
    public:
        QUrl createBaseURL() const;
        QNetworkRequest getRequest(QUrl iURL) const;

        // Member data
    private:
        QSettings mSettings;
        QString mClientID, mClientVersion, mClientLanguage;
        QByteArray mUserAgent;
        QNetworkAccessManager mNetworkAccessManager;
        QNetworkReply* mNetworkReply;
    };
}

#endif // REQUESTHELPER_H

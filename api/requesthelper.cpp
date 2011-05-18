//
// Configuration
//

// Includes
#include "requesthelper.h"
#include <QLocale>
#include <QApplication>
#include <QDebug>

// Namespaces
using namespace iRail;


//
// Construction and destruction
//

RequestHelper::RequestHelper()
{
    Q_ASSERT(mSettings.contains("client/id"));
    Q_ASSERT(mSettings.contains("client/version"));
    mUserAgent.append(mSettings.applicationName() + "-" +                   // Application
                      mSettings.value("client/id").toString() +             // Client
                      "/" + mSettings.value("client/version").toString() +  // Client version
                      " libqtrail/0.2"                                      // Library
                      );
    mNetworkReply = 0;

    switch (QLocale::system().language())
    {
    case QLocale::English:
        mClientLanguage = "en";
        break;
    case QLocale::French:
        mClientLanguage = "fr";
        break;
    case QLocale::German:
        mClientLanguage = "de";
        break;
    case QLocale::Dutch:
        mClientLanguage = "nl";
        break;
    default:
        mClientLanguage = "en";
    }
}


//
// Network helpers
//

void RequestHelper::networkRequest(QNetworkRequest iRequest, QObject* iObject, const char* iSlot) throw(NetworkException)
{
    if (mNetworkReply != 0)
        throw NetworkException("cannot perform concurrent requests");

    // TODO: this is quite a blocking request, we shouldn't wait for it!
    QApplication::processEvents();  // Temporary fix
    mNetworkReply = mNetworkAccessManager.get(iRequest);

    // TODO: this doesn't cach errors properly, e.g. when connection to a nonexisting url
    if (mNetworkReply->error() != QNetworkReply::NoError)
    {
        throw NetworkException(mNetworkReply->errorString());
    }

    QObject::connect(mNetworkReply, SIGNAL(finished()), iObject, iSlot);
}

QNetworkReply* RequestHelper::networkReply()
{
    return mNetworkReply;
}

void RequestHelper::networkCleanup()
{
    mNetworkReply->deleteLater();
    mNetworkReply = 0;
}


//
// Auxiliary
//

QUrl RequestHelper::createBaseURL() const
{
    // Build base URL
    QUrl oUrl;
    oUrl.setScheme("http");
    oUrl.setHost("api.irail.be");
    oUrl.addQueryItem("lang", mClientLanguage);
    oUrl.setQueryDelimiters('=', '&');

    return oUrl;
}

QNetworkRequest RequestHelper::getRequest(QUrl iURL) const
{
    QNetworkRequest oRequest;
    oRequest.setUrl(iURL);
    oRequest.setRawHeader("User-Agent", mUserAgent);

    return oRequest;
}

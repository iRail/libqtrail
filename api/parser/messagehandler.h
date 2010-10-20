//
// Configuration
//

// Include guard
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

// Includes
#include <QtXmlPatterns/QAbstractMessageHandler>
#include <QtXmlPatterns/QSourceLocation>
#include <QString>
#include <QUrl>
#include <QDebug>

namespace iRail
{
    class MessageHandler : public QAbstractMessageHandler
    {
    public:
        MessageHandler() : QAbstractMessageHandler(0)
        {
        }

        QString getDescription() const
        {
            return mDescription;
        }

        QSourceLocation getSourceLocation() const
        {
            return mSourceLocation;
        }

    protected:
        virtual void handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation)
        {
            Q_UNUSED(type);
            Q_UNUSED(identifier);
            qDebug() << "Handling message";

            mDescription = description;
            mSourceLocation = sourceLocation;
        }

    private:
        QString mDescription;
        QSourceLocation mSourceLocation;
    };
}

#endif // MESSAGEHANDLER_H

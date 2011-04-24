//
// Configuration
//

// Include guard
#ifndef AUXILIARY_H
#define AUXILIARY_H

// Includes
#include <QString>
#include <QMap>
#include <QStringBuilder>

namespace iRail
{
    inline QString capitalize(const QString& iString)
    {
        if (iString.isEmpty())
            return iString;

        // TODO: QStringRef
        bool split = true;
        QString oString = iString.toLower();
        for (int i = 0; i < oString.length(); i++)
        {
            if (split)
            {
                oString[i] = oString[i].toUpper();
                split = false;
            }
            if (!oString[i].isLetterOrNumber())
                split = true;
        }

        return oString;
    }
}

#endif // AUXILIARY_H

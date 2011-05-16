//
// Configuration
//

// Include guard
#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

// Includes
#include <QObject>

namespace iRail
{
    class ProgressIndicator : public QObject
    {
    Q_OBJECT
        // Construction and destruction
    private:
        ProgressIndicator();
    public:
        ProgressIndicator& instance();

        // Member data
    private:
    };
}

#endif // PROGRESSINDICATOR_H

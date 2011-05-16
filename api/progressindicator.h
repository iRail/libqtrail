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

        // Signals
    signals:
        void transferStarted();
        void transferStopped();
        void requestStarted();
        void requestStopped();

        // Slots
    public slots:
        void startTransfer();
        void stopTransfer();
        void startRequest();
        void stopRequest();

        // Member data
    private:
    };
}

#endif // PROGRESSINDICATOR_H

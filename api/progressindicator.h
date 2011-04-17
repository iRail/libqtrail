#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

class ProgressIndicator
{
private:
    ProgressIndicator();
public:
    ProgressIndicator& instance();
signals:
    transferStarted();
    transferStopped();
    requestStarted();
    requestStopped();
public slots:
    startTransfer();
    stopTransfer();
    startRequest();
    stopRequest();
};

#endif // PROGRESSINDICATOR_H

#include <QtTest/QtTest>

class Compile : public QObject
{
    Q_OBJECT
};

QTEST_MAIN(Compile)

#include "compile.moc"


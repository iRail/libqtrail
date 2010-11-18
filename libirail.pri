#
# Base configuration
#

# Path configuration
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT       += network xml

RESOURCES += \
    api/parser.qrc
SOURCES += \
    asyncapi.cpp \
    cachedapi.cpp \
    api/station.cpp \
    api/connectionrequest.cpp \
    api/parser.cpp \
    api/connection.cpp \
    api/storage/memorystorage.cpp \
    api/reader.cpp \
    api/reader/stationreader.cpp \
    api/reader/connectionreader.cpp \
    api/vehicle.cpp \
    api/reader/vehiclereader.cpp \
    api/liveboard.cpp \
    api/reader/liveboardreader.cpp
HEADERS += \
    asyncapi.h \
    cachedapi.h \
    api/station.h \
    api/connectionrequest.h \
    api/parser.h \
    api/exception.h \
    api/exception/parserexception.h \
    api/exception/networkexception.h \
    api/exception/interruptedexception.h \
    api/connection.h \
    api/storage.h \
    api/storage/memorystorage.h \
    api/reader.h \
    api/reader/stationreader.h \
    api/reader/connectionreader.h \
    api/progresshandler.h \
    api/vehicle.h \
    api/reader/vehiclereader.h \
    ../libirail/api/liveboard.h \
    ../libirail/api/reader/liveboardreader.h

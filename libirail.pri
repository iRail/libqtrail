#
# Base configuration
#

# Path configuration
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT       += network xml

RESOURCES += i18n_libirail.qrc \
    api/parser.qrc
TRANSLATIONS += \
    i18n_libirail/nl.ts \
    i18n_libirail/fr.ts \
    i18n_libirail/de.ts \
    i18n_libirail/en.ts
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
    api/reader/liveboardreader.cpp \
    api/storage/serializedstorage.cpp \
    api/liveboardrequest.cpp
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
    api/liveboard.h \
    api/reader/liveboardreader.h \
    api/storage/serializedstorage.h \
    api/liveboardrequest.h \
    api/auxiliary.h

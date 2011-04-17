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
    api/progressindicator.cpp \
    api/storage/memorystorage.cpp \
    api/storage/serializedstorage.cpp \
    api/parser.cpp \
    api/reader.cpp \
    api/reader/stationreader.cpp \
    api/reader/journeyreader.cpp \
    api/reader/stopreader.cpp \
    api/reader/departurereader.cpp \
    api/data/station.cpp \
    api/data/vehicle.cpp \
    api/data/departure.cpp \
    api/data/poi.cpp \
    api/data/connection.cpp \
    api/data/journey.cpp \
    api/container/journeylist.cpp \
    api/container/departurelist.cpp \
    api/container/stationlist.cpp \
    api/container/stoplist.cpp \
    api/requesthelper.cpp \
    ../libirail/api/data/location.cpp \
    ../libirail/api/container/vehiclelist.cpp \
    ../libirail/api/container/connectionlist.cpp \
    ../libirail/api/containercache.cpp
HEADERS += \
    asyncapi.h \
    cachedapi.h \
    api/auxiliary.h \
    api/progresshandler.h \
    api/progressindicator.h \
    api/exception.h \
    api/exception/parserexception.h \
    api/exception/networkexception.h \
    api/exception/interruptedexception.h \
    api/storage.h \
    api/storage/memorystorage.h \
    api/storage/serializedstorage.h \
    api/parser.h \
    api/reader.h \
    api/reader/stationreader.h \
    api/reader/journeyreader.h \
    api/reader/stopreader.h \
    api/reader/departurereader.h \
    api/data/station.h \
    api/data/vehicle.h \
    api/data/departure.h \
    api/data/poi.h \
    api/data/connection.h \
    api/data/journey.h \
    api/container/journeylist.h \
    api/container/departurelist.h \
    api/container/stationlist.h \
    api/container/stoplist.h \
    api/requesthelper.h \
    ../libirail/api/data/location.h \
    ../libirail/api/container/vehiclelist.h \
    ../libirail/api/container/connectionlist.h \
    ../libirail/api/containercache.h

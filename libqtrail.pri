#
# Base configuration
#

QT       += network xml

RESOURCES +=
SOURCES += \
    api/progressindicator.cpp \
    api/reader.cpp \
    api/data.cpp \
    api/data/station.cpp \
    api/data/vehicle.cpp \
    api/data/departure.cpp \
    api/data/connection.cpp \
    api/data/journey.cpp \
    api/container.cpp \
    api/container/journeylist.cpp \
    api/container/departurelist.cpp \
    api/container/stationlist.cpp \
    api/container/stoplist.cpp \
    api/requesthelper.cpp \
    api/data/auxiliary/location.cpp \
    api/container/vehiclelist.cpp \
    api/container/connectionlist.cpp \
    api/containercache.cpp \
    api/data/stop.cpp \
    api/reader/liveboardreader.cpp \
    api/reader/connectionsreader.cpp \
    api/reader/stationsreader.cpp \
    api/reader/vehiclereader.cpp
HEADERS += \
    api/auxiliary.h \
    api/progressindicator.h \
    api/exception.h \
    api/exception/parserexception.h \
    api/exception/networkexception.h \
    api/exception/interruptedexception.h \
    api/reader.h \
    api/data.h \
    api/data/station.h \
    api/data/vehicle.h \
    api/data/departure.h \
    api/data/connection.h \
    api/data/journey.h \
    api/container.h \
    api/container/journeylist.h \
    api/container/departurelist.h \
    api/container/stationlist.h \
    api/container/stoplist.h \
    api/requesthelper.h \
    api/data/auxiliary/location.h \
    api/container/vehiclelist.h \
    api/container/connectionlist.h \
    api/containercache.h \
    api/data/stop.h \
    api/reader/liveboardreader.h \
    api/reader/connectionsreader.h \
    api/reader/stationsreader.h \
    api/reader/vehiclereader.h

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
    api/station.cpp \
    api/connectionrequest.cpp \
    api/parser.cpp \
    api/connection.cpp \
    api/storage/memorystorage.cpp \
    api/reader.cpp \
    api/reader/stationreader.cpp \
    api/reader/connectionreader.cpp
HEADERS += \
    asyncapi.h \
    api/station.h \
    api/connectionrequest.h \
    api/parser.h \
    api/exception.h \
    api/exception/parserexception.h \
    api/exception/networkexception.h \
    api/connection.h \
    api/storage.h \
    api/storage/memorystorage.h \
    api/exception/storageexception.h \
    api/reader.h \
    api/reader/stationreader.h \
    api/reader/connectionreader.h


#
# Optional modules
#

# Validate XML files
ValidatingXml {
    QT += xmlpatterns

    HEADERS += api/parser/messagehandler.h

    DEFINES += BETRAINS_VALIDATINGXML
}


TEMPLATE = app

QT += qml quick
CONFIG += c++11

#HEADERS += \
#    listmodel.h \
#    moon2.h

SOURCES += main.cpp
#   listmodel.cpp   \
#    moon2.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=



QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DbManager.cpp \
    Helper.cpp \
    dbmanagerhelper.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DbManager.h \
    Helper.h \
    Models/Apartment.h \
    Models/Buyer.h \
    Models/Sale.h \
    Models/Salesman.h \
    Models/TableModel.h \
    dbmanagerhelper.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

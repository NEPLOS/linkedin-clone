QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fill_the_form.cpp \
    main.cpp \
    main_page.cpp \
    mainwindow.cpp \
    page_sender.cpp \
    verify_code.cpp \
    welcome.cpp

HEADERS += \
    fill_the_form.h \
    main_page.h \
    mainwindow.h \
    page_sender.h \
    verify_code.h \
    welcome.h

FORMS += \
    fill_the_form.ui \
    main_page.ui \
    mainwindow.ui \
    page_sender.ui \
    verify_code.ui \
    welcome.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imgs.qrc

DISTFILES +=

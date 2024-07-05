QT       += core gui sql multimedia widgets multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    comment.cpp \
    comments.cpp \
    company.cpp \
    content.cpp \
    direct_message.cpp \
    fill_the_form.cpp \
    job.cpp \
    job_form.cpp \
    job_form_company.cpp \
    like.cpp \
    main.cpp \
    main_page.cpp \
    mainwindow.cpp \
    make_company.cpp \
    make_job.cpp \
    message_contact.cpp \
    message_with_user.cpp \
    my_network.cpp \
    page_sender.cpp \
    person.cpp \
    post.cpp \
    profile.cpp \
    send_post.cpp \
    timew.cpp \
    verify_code.cpp \
    view_profile.cpp \
    welcome.cpp

HEADERS += \
    account.h \
    comment.h \
    comments.h \
    company.h \
    content.h \
    direct_message.h \
    fill_the_form.h \
    job.h \
    job_form.h \
    job_form_company.h \
    like.h \
    main_page.h \
    mainwindow.h \
    make_company.h \
    make_job.h \
    message_contact.h \
    message_with_user.h \
    my_network.h \
    page_sender.h \
    person.h \
    post.h \
    profile.h \
    send_post.h \
    timew.h \
    verify_code.h \
    view_profile.h \
    welcome.h

FORMS += \
    comments.ui \
    fill_the_form.ui \
    job_form.ui \
    job_form_company.ui \
    main_page.ui \
    mainwindow.ui \
    make_company.ui \
    make_job.ui \
    message_contact.ui \
    message_with_user.ui \
    my_network.ui \
    page_sender.ui \
    profile.ui \
    send_post.ui \
    verify_code.ui \
    view_profile.ui \
    welcome.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=

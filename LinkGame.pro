QT       += core gui
QT       += network
QT       += sql
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    autoproblemsolvethread.cpp \
    chooselevel_ui.cpp \
    deleteqgraphicsitemthread.cpp \
    game_ui.cpp \
    global_value_method.cpp \
    login_ui.cpp \
    main.cpp \
    linkgame.cpp \
    map.cpp \
    messagedialog.cpp \
    mybutton.cpp \
    mymainwindow.cpp \
    rankinglist.cpp \
    register_ui.cpp \
    set_ui.cpp \
    timeprogressbarthread.cpp \
    voiceplayer.cpp

HEADERS += \
    autoproblemsolvethread.h \
    chooselevel_ui.h \
    deleteqgraphicsitemthread.h \
    game_ui.h \
    global_value_method.h \
    linkgame.h \
    linklist.h \
    login_ui.h \
    map.h \
    messagedialog.h \
    mybutton.h \
    mymainwindow.h \
    rankinglist.h \
    register_ui.h \
    set_ui.h \
    timeprogressbarthread.h \
    voiceplayer.h

FORMS += \
    chooselevel_ui.ui \
    game_ui.ui \
    linkgame.ui \
    login_ui.ui \
    messagedialog.ui \
    rankinglist.ui \
    register_ui.ui \
    set_ui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Voice.qrc

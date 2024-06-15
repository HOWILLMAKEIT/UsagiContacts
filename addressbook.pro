QT       += core gui
QT      += sql
QT       += network
QT      += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_func.cpp \
    contact.cpp \
    db_operator.cpp \
    delete_account.cpp \
    email.cpp \
    email_func.cpp \
    email_func_birth.cpp \
    email_func_normal.cpp \
    email_login.cpp \
    email_send_func.cpp \
    main.cpp \
    login.cpp \
    mainfunc.cpp \
    modify_func.cpp \
    mysound.cpp \
    name_modify_func.cpp \
    password_modify_func.cpp \
    regist.cpp

HEADERS += \
    add_func.h \
    contact.h \
    db_operator.h \
    delete_account.h \
    email.h \
    email_func.h \
    email_func_birth.h \
    email_func_normal.h \
    email_login.h \
    email_send_func.h \
    login.h \
    mainfunc.h \
    modify_func.h \
    mysound.h \
    name_modify_func.h \
    password_modify_func.h \
    regist.h

FORMS += \
    add_func.ui \
    delete_account.ui \
    email_func.ui \
    email_func_birth.ui \
    email_func_normal.ui \
    email_login.ui \
    email_send_func.ui \
    login.ui \
    mainfunc.ui \
    modify_func.ui \
    name_modify_func.ui \
    password_modify_func.ui \
    regist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/resource.qrc \
    resource/resource.qrc

DISTFILES += \
    resource/0x300a0a0.png \
    resource/R-C.jpg \
    resource/background/DWS7G5GWUdVzjzJ.jpeg \
    resource/background/login_bg.jpg \
    resource/background/v2-3e895c4b6dd21bd93839c26198182227_720w.webp \
    resource/background/v2-5bf1fa2af20e843ecd19dbbc17d21f9d_r.jpg \
    resource/background/屏幕截图 2024-06-01 110331.png \
    resource/background/屏幕截图 2024-06-01 114350.png \
    resource/background/屏幕截图 2024-06-01 172200.png \
    resource/background/屏幕截图 2024-06-01 173533.png \
    resource/background/屏幕截图 2024-06-01 175317.png \
    resource/background/屏幕截图 2024-06-01 180551.png \
    resource/default_image.jpg \
    resource/sound/ha.wav \
    resource/sound/highest_yaha.wav \
    resource/sound/wuda.wav \
    resource/sound/wulayahayahawula.wav \
    resource/sound/yaha.wav \
    resource/u=129999000,2456342745&fm=253&fmt=auto&app=120&f=JPEG.webp \
    resource/u=3765018513,1526613524&fm=253&fmt=auto&app=138&f=JPEG.webp \
    resource/微信图片_20240524115747.png

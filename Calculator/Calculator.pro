QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    calculator.cpp \
    rpncalculator.cpp

HEADERS += \
    calculator.h \
    rpncalculator.h

FORMS += \
    calculator.ui

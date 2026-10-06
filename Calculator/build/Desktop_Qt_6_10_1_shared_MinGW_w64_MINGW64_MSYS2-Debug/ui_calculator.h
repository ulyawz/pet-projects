/********************************************************************************
** Form generated from reading UI file 'calculator.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calculator
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton_AC;
    QPushButton *pushButton_PM;
    QPushButton *pushButton_Pr;
    QPushButton *pushButton_Pow;
    QPushButton *pushButton_Div;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_Mul;
    QPushButton *pushButton_Paren_Open;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_Sub;
    QPushButton *pushButton_Paren_Close;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_Add;
    QPushButton *pushButton_Empty;
    QPushButton *pushButton_0;
    QPushButton *pushButton_Dot;
    QPushButton *pushButton_Equal;

    void setupUi(QWidget *Calculator)
    {
        if (Calculator->objectName().isEmpty())
            Calculator->setObjectName("Calculator");
        Calculator->resize(301, 360);
        lineEdit = new QLineEdit(Calculator);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(0, 0, 301, 60));
        QFont font;
        font.setFamilies({QString::fromUtf8("Calibri")});
        font.setPointSize(16);
        font.setBold(true);
        lineEdit->setFont(font);
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{background-color:white;border:none;padding-right:6px;}"));
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        lineEdit->setReadOnly(true);
        pushButton_AC = new QPushButton(Calculator);
        pushButton_AC->setObjectName("pushButton_AC");
        pushButton_AC->setGeometry(QRect(0, 60, 61, 60));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        pushButton_AC->setFont(font1);
        pushButton_AC->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(215,215,215);}QPushButton:pressed{background-color:#bebebe;}"));
        pushButton_PM = new QPushButton(Calculator);
        pushButton_PM->setObjectName("pushButton_PM");
        pushButton_PM->setGeometry(QRect(60, 60, 61, 60));
        pushButton_PM->setFont(font1);
        pushButton_PM->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(215,215,215);}QPushButton:pressed{background-color:#bebebe;}"));
        pushButton_Pr = new QPushButton(Calculator);
        pushButton_Pr->setObjectName("pushButton_Pr");
        pushButton_Pr->setGeometry(QRect(120, 60, 61, 60));
        pushButton_Pr->setFont(font1);
        pushButton_Pr->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(215,215,215);}QPushButton:pressed{background-color:#bebebe;}"));
        pushButton_Pow = new QPushButton(Calculator);
        pushButton_Pow->setObjectName("pushButton_Pow");
        pushButton_Pow->setGeometry(QRect(180, 60, 61, 60));
        pushButton_Pow->setFont(font1);
        pushButton_Pow->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(255,151,57);color:white;}QPushButton:pressed{background-color:#ff7832;}"));
        pushButton_Div = new QPushButton(Calculator);
        pushButton_Div->setObjectName("pushButton_Div");
        pushButton_Div->setGeometry(QRect(240, 60, 61, 60));
        pushButton_Div->setFont(font1);
        pushButton_Div->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(255,151,57);color:white;}QPushButton:pressed{background-color:#ff7832;}"));
        pushButton_7 = new QPushButton(Calculator);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(0, 120, 61, 60));
        pushButton_7->setFont(font1);
        pushButton_8 = new QPushButton(Calculator);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(60, 120, 61, 60));
        pushButton_8->setFont(font1);
        pushButton_9 = new QPushButton(Calculator);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(120, 120, 61, 60));
        pushButton_9->setFont(font1);
        pushButton_Mul = new QPushButton(Calculator);
        pushButton_Mul->setObjectName("pushButton_Mul");
        pushButton_Mul->setGeometry(QRect(180, 120, 61, 60));
        pushButton_Mul->setFont(font1);
        pushButton_Mul->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(255,151,57);color:white;}QPushButton:pressed{background-color:#ff7832;}"));
        pushButton_Paren_Open = new QPushButton(Calculator);
        pushButton_Paren_Open->setObjectName("pushButton_Paren_Open");
        pushButton_Paren_Open->setGeometry(QRect(240, 120, 61, 60));
        pushButton_Paren_Open->setFont(font1);
        pushButton_Paren_Open->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(215,215,215);}QPushButton:pressed{background-color:#bebebe;}"));
        pushButton_4 = new QPushButton(Calculator);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(0, 180, 61, 60));
        pushButton_4->setFont(font1);
        pushButton_5 = new QPushButton(Calculator);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(60, 180, 61, 60));
        pushButton_5->setFont(font1);
        pushButton_6 = new QPushButton(Calculator);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(120, 180, 61, 60));
        pushButton_6->setFont(font1);
        pushButton_Sub = new QPushButton(Calculator);
        pushButton_Sub->setObjectName("pushButton_Sub");
        pushButton_Sub->setGeometry(QRect(180, 180, 61, 60));
        pushButton_Sub->setFont(font1);
        pushButton_Sub->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(255,151,57);color:white;}QPushButton:pressed{background-color:#ff7832;}"));
        pushButton_Paren_Close = new QPushButton(Calculator);
        pushButton_Paren_Close->setObjectName("pushButton_Paren_Close");
        pushButton_Paren_Close->setGeometry(QRect(240, 180, 61, 60));
        pushButton_Paren_Close->setFont(font1);
        pushButton_Paren_Close->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(215,215,215);}QPushButton:pressed{background-color:#bebebe;}"));
        pushButton_1 = new QPushButton(Calculator);
        pushButton_1->setObjectName("pushButton_1");
        pushButton_1->setGeometry(QRect(0, 240, 61, 60));
        pushButton_1->setFont(font1);
        pushButton_2 = new QPushButton(Calculator);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(60, 240, 61, 60));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(Calculator);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(120, 240, 61, 60));
        pushButton_3->setFont(font1);
        pushButton_Add = new QPushButton(Calculator);
        pushButton_Add->setObjectName("pushButton_Add");
        pushButton_Add->setGeometry(QRect(180, 240, 61, 60));
        pushButton_Add->setFont(font1);
        pushButton_Add->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(255,151,57);color:white;}QPushButton:pressed{background-color:#ff7832;}"));
        pushButton_Empty = new QPushButton(Calculator);
        pushButton_Empty->setObjectName("pushButton_Empty");
        pushButton_Empty->setGeometry(QRect(240, 240, 61, 60));
        pushButton_Empty->setFont(font1);
        pushButton_Empty->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(215,215,215);}QPushButton:pressed{background-color:#bebebe;}"));
        pushButton_Empty->setEnabled(false);
        pushButton_0 = new QPushButton(Calculator);
        pushButton_0->setObjectName("pushButton_0");
        pushButton_0->setGeometry(QRect(0, 300, 121, 60));
        pushButton_0->setFont(font1);
        pushButton_Dot = new QPushButton(Calculator);
        pushButton_Dot->setObjectName("pushButton_Dot");
        pushButton_Dot->setGeometry(QRect(120, 300, 61, 60));
        pushButton_Dot->setFont(font1);
        pushButton_Dot->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(215,215,215);}QPushButton:pressed{background-color:#bebebe;}"));
        pushButton_Equal = new QPushButton(Calculator);
        pushButton_Equal->setObjectName("pushButton_Equal");
        pushButton_Equal->setGeometry(QRect(180, 300, 121, 60));
        pushButton_Equal->setFont(font1);
        pushButton_Equal->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(255,151,57);color:white;}QPushButton:pressed{background-color:#ff7832;}"));

        retranslateUi(Calculator);

        QMetaObject::connectSlotsByName(Calculator);
    } // setupUi

    void retranslateUi(QWidget *Calculator)
    {
        Calculator->setWindowTitle(QCoreApplication::translate("Calculator", "Calculator", nullptr));
        pushButton_AC->setText(QCoreApplication::translate("Calculator", "AC", nullptr));
        pushButton_PM->setText(QCoreApplication::translate("Calculator", "+/-", nullptr));
        pushButton_Pr->setText(QCoreApplication::translate("Calculator", "%", nullptr));
        pushButton_Pow->setText(QCoreApplication::translate("Calculator", "^", nullptr));
        pushButton_Div->setText(QCoreApplication::translate("Calculator", "/", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Calculator", "7", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Calculator", "8", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Calculator", "9", nullptr));
        pushButton_Mul->setText(QCoreApplication::translate("Calculator", "*", nullptr));
        pushButton_Paren_Open->setText(QCoreApplication::translate("Calculator", "(", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Calculator", "4", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Calculator", "5", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Calculator", "6", nullptr));
        pushButton_Sub->setText(QCoreApplication::translate("Calculator", "-", nullptr));
        pushButton_Paren_Close->setText(QCoreApplication::translate("Calculator", ")", nullptr));
        pushButton_1->setText(QCoreApplication::translate("Calculator", "1", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Calculator", "2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Calculator", "3", nullptr));
        pushButton_Add->setText(QCoreApplication::translate("Calculator", "+", nullptr));
        pushButton_Empty->setText(QString());
        pushButton_0->setText(QCoreApplication::translate("Calculator", "0", nullptr));
        pushButton_Dot->setText(QCoreApplication::translate("Calculator", ".", nullptr));
        pushButton_Equal->setText(QCoreApplication::translate("Calculator", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calculator: public Ui_Calculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H

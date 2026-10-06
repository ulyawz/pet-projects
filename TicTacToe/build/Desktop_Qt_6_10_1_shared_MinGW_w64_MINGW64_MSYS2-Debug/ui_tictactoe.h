/********************************************************************************
** Form generated from reading UI file 'tictactoe.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TICTACTOE_H
#define UI_TICTACTOE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TicTacToe
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *modeComboBox;
    QLabel *statusLabel;
    QGridLayout *gridLayout;
    QPushButton *clearBtn;

    void setupUi(QWidget *TicTacToe)
    {
        if (TicTacToe->objectName().isEmpty())
            TicTacToe->setObjectName("TicTacToe");
        verticalLayout = new QVBoxLayout(TicTacToe);
        verticalLayout->setObjectName("verticalLayout");
        modeComboBox = new QComboBox(TicTacToe);
        modeComboBox->setObjectName("modeComboBox");

        verticalLayout->addWidget(modeComboBox);

        statusLabel = new QLabel(TicTacToe);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");

        verticalLayout->addLayout(gridLayout);

        clearBtn = new QPushButton(TicTacToe);
        clearBtn->setObjectName("clearBtn");

        verticalLayout->addWidget(clearBtn);


        retranslateUi(TicTacToe);

        QMetaObject::connectSlotsByName(TicTacToe);
    } // setupUi

    void retranslateUi(QWidget *TicTacToe)
    {
        TicTacToe->setWindowTitle(QCoreApplication::translate("TicTacToe", "TicTacToe", nullptr));
        statusLabel->setText(QCoreApplication::translate("TicTacToe", "Player1", nullptr));
        clearBtn->setText(QCoreApplication::translate("TicTacToe", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TicTacToe: public Ui_TicTacToe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TICTACTOE_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayoutTop;
    QPushButton *btnNewGame;
    QLabel *labelStatus;
    QPushButton *btnRecords;
    QHBoxLayout *horizontalLayoutInput;
    QLabel *labelPrompt;
    QLineEdit *lineEditInput;
    QPushButton *btnCheck;
    QTableWidget *tableHistory;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 500);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayoutTop = new QHBoxLayout();
        horizontalLayoutTop->setObjectName("horizontalLayoutTop");
        btnNewGame = new QPushButton(centralwidget);
        btnNewGame->setObjectName("btnNewGame");

        horizontalLayoutTop->addWidget(btnNewGame);

        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName("labelStatus");
        labelStatus->setAlignment(Qt::AlignCenter);

        horizontalLayoutTop->addWidget(labelStatus);

        btnRecords = new QPushButton(centralwidget);
        btnRecords->setObjectName("btnRecords");

        horizontalLayoutTop->addWidget(btnRecords);


        verticalLayout->addLayout(horizontalLayoutTop);

        horizontalLayoutInput = new QHBoxLayout();
        horizontalLayoutInput->setObjectName("horizontalLayoutInput");
        labelPrompt = new QLabel(centralwidget);
        labelPrompt->setObjectName("labelPrompt");

        horizontalLayoutInput->addWidget(labelPrompt);

        lineEditInput = new QLineEdit(centralwidget);
        lineEditInput->setObjectName("lineEditInput");
        lineEditInput->setMaxLength(4);

        horizontalLayoutInput->addWidget(lineEditInput);

        btnCheck = new QPushButton(centralwidget);
        btnCheck->setObjectName("btnCheck");

        horizontalLayoutInput->addWidget(btnCheck);


        verticalLayout->addLayout(horizontalLayoutInput);

        tableHistory = new QTableWidget(centralwidget);
        if (tableHistory->columnCount() < 2)
            tableHistory->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableHistory->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableHistory->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableHistory->setObjectName("tableHistory");

        verticalLayout->addWidget(tableHistory);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\221\321\213\320\272\320\270 \320\270 \320\272\320\276\321\200\320\276\320\262\321\213", nullptr));
        btnNewGame->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\260\321\217 \320\270\320\263\321\200\320\260", nullptr));
        labelStatus->setText(QCoreApplication::translate("MainWindow", "\320\230\320\263\321\200\320\260 \320\275\320\265 \320\275\320\260\321\207\320\260\321\202\320\260", nullptr));
        btnRecords->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\272\320\276\321\200\320\264\321\213", nullptr));
        labelPrompt->setText(QCoreApplication::translate("MainWindow", "\320\262\320\262\320\265\320\264\320\270 \321\207\320\270\321\201\320\273\320\276", nullptr));
        btnCheck->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214!", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableHistory->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\247\320\270\321\201\320\273\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableHistory->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "rpncalculator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();
    void operatorClicked();
    void on_pushButton_Dot_clicked();
    void on_pushButton_AC_clicked();
    void on_pushButton_Equal_clicked();
    void on_pushButton_PM_clicked();
    void on_pushButton_Pr_clicked();
    void on_pushButton_Paren_Open_clicked();
    void on_pushButton_Paren_Close_clicked();
    void on_pushButton_Pow_clicked();

private:
    Ui::Calculator *ui;
    RPNCalculator rpn;
    bool resultShown;
    void appendToExpression(const QString &text);
};

#endif // CALCULATOR_H

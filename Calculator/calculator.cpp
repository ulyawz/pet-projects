#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculator)
    , resultShown(false)
{
    ui->setupUi(this);

    // Цифры
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digitClicked()));

    // Операторы
    connect(ui->pushButton_Add, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(ui->pushButton_Sub, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(ui->pushButton_Mul, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(ui->pushButton_Div, SIGNAL(clicked()), this, SLOT(operatorClicked()));

    // Запрет ввода с клавиатуры
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::appendToExpression(const QString &text)
{
    if (resultShown) {
        // Если нажата цифра после результата — начинаем новое выражение
        // Если оператор — продолжаем с результатом
        resultShown = false;
    }
    ui->lineEdit->setText(ui->lineEdit->text() + text);
}

void Calculator::digitClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    if (resultShown) {
        // Начинаем новое выражение
        ui->lineEdit->clear();
        resultShown = false;
    }
    ui->lineEdit->setText(ui->lineEdit->text() + btn->text());
}

void Calculator::operatorClicked()
{
    QPushButton *btn = (QPushButton *)sender();
    resultShown = false;
    ui->lineEdit->setText(ui->lineEdit->text() + btn->text());
}

void Calculator::on_pushButton_Dot_clicked()
{
    // Добавляем точку только если в текущем числе её нет
    QString expr = ui->lineEdit->text();
    // Находим начало последнего числа
    int i = expr.length() - 1;
    while (i >= 0 && (expr[i].isDigit() || expr[i] == '.')) i--;
    QString lastNum = expr.mid(i + 1);
    if (!lastNum.contains('.')) {
        if (lastNum.isEmpty()) ui->lineEdit->setText(expr + "0.");
        else appendToExpression(".");
    }
}

void Calculator::on_pushButton_AC_clicked()
{
    ui->lineEdit->clear();
    resultShown = false;
}

void Calculator::on_pushButton_Equal_clicked()
{
    QString expression = ui->lineEdit->text();
    if (expression.isEmpty()) return;

    QString result = rpn.evaluate(expression);
    ui->lineEdit->setText(result);
    resultShown = true;
}

void Calculator::on_pushButton_PM_clicked()
{
    // +/- : оборачиваем текущее выражение в -(...)
    QString expr = ui->lineEdit->text();
    if (expr.isEmpty()) return;
    if (expr.startsWith("-(") && expr.endsWith(")"))
        ui->lineEdit->setText(expr.mid(2, expr.length() - 3));
    else
        ui->lineEdit->setText("-(" + expr + ")");
    resultShown = false;
}

void Calculator::on_pushButton_Pr_clicked()
{
    // % : делим на 100
    QString expr = ui->lineEdit->text();
    if (expr.isEmpty()) return;
    ui->lineEdit->setText("(" + expr + ")*0.01");
    resultShown = false;
}

void Calculator::on_pushButton_Paren_Open_clicked()
{
    if (resultShown) { ui->lineEdit->clear(); resultShown = false; }
    ui->lineEdit->setText(ui->lineEdit->text() + "(");
}

void Calculator::on_pushButton_Paren_Close_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + ")");
}

void Calculator::on_pushButton_Pow_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "^");
    resultShown = false;
}

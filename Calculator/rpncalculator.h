#ifndef RPNCALCULATOR_H
#define RPNCALCULATOR_H

#include <QString>
#include <QStack>
#include <QVector>
#include <cmath>

// Токен для обратной польской записи
struct Token {
    enum Type { NUMBER, OPERATOR, LEFT_PAREN, RIGHT_PAREN } type;
    double number;
    QChar op;
};

class RPNCalculator
{
public:
    RPNCalculator();

    // Вычислить выражение, возвращает результат или ошибку
    QString evaluate(const QString &expression);

private:
    // Приоритет оператора
    int precedence(QChar op);

    // Токенизация строки выражения
    QVector<Token> tokenize(const QString &expression, bool &ok, QString &error);

    // Перевод в обратную польскую запись (алгоритм сортировочной станции)
    QVector<Token> toRPN(const QVector<Token> &tokens, bool &ok, QString &error);

    // Вычисление по обратной польской записи
    double calcRPN(const QVector<Token> &rpn, bool &ok, QString &error);

    // Применить оператор к двум числам
    double applyOp(QChar op, double a, double b, bool &ok, QString &error);
};

#endif // RPNCALCULATOR_H

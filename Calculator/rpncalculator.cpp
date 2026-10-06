#include "rpncalculator.h"

RPNCalculator::RPNCalculator() {}

QString RPNCalculator::evaluate(const QString &expression)
{
    bool ok = false;
    QString error;

    // Шаг 1: токенизация
    QVector<Token> tokens = tokenize(expression, ok, error);
    if (!ok) return "Ошибка: " + error;

    // Шаг 2: перевод в обратную польскую запись
    QVector<Token> rpn = toRPN(tokens, ok, error);
    if (!ok) return "Ошибка: " + error;

    // Шаг 3: вычисление
    double result = calcRPN(rpn, ok, error);
    if (!ok) return "Ошибка: " + error;

    // Форматирование результата
    if (result == (long long)result)
        return QString::number((long long)result);
    return QString::number(result, 'g', 15);
}

int RPNCalculator::precedence(QChar op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^')              return 3;
    return 0;
}

QVector<Token> RPNCalculator::tokenize(const QString &expression, bool &ok, QString &error)
{
    QVector<Token> tokens;
    ok = true;
    int i = 0;

    while (i < expression.length()) {
        QChar c = expression[i];

        // Пробелы пропускаем
        if (c.isSpace()) { i++; continue; }

        // Число
        if (c.isDigit() || c == '.') {
            QString numStr;
            while (i < expression.length() &&
                   (expression[i].isDigit() || expression[i] == '.')) {
                numStr += expression[i++];
            }
            bool numOk;
            double num = numStr.toDouble(&numOk);
            if (!numOk) { ok = false; error = "Некорректное число: " + numStr; return {}; }
            tokens.append({Token::NUMBER, num, '\0'});
            continue;
        }

        // Унарный минус: в начале или после оператора/открывающей скобки
        if (c == '-' && (tokens.isEmpty() ||
                         tokens.last().type == Token::OPERATOR ||
                         tokens.last().type == Token::LEFT_PAREN)) {
            i++;
            // Читаем число после унарного минуса
            QString numStr = "-";
            while (i < expression.length() &&
                   (expression[i].isDigit() || expression[i] == '.')) {
                numStr += expression[i++];
            }
            bool numOk;
            double num = numStr.toDouble(&numOk);
            if (!numOk) { ok = false; error = "Некорректное число после унарного минуса"; return {}; }
            tokens.append({Token::NUMBER, num, '\0'});
            continue;
        }

        // Операторы
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            tokens.append({Token::OPERATOR, 0, c});
            i++;
            continue;
        }

        // Скобки
        if (c == '(') { tokens.append({Token::LEFT_PAREN,  0, c}); i++; continue; }
        if (c == ')') { tokens.append({Token::RIGHT_PAREN, 0, c}); i++; continue; }

        // Неизвестный символ
        ok = false;
        error = QString("Неизвестный символ: ") + c;
        return {};
    }

    return tokens;
}

QVector<Token> RPNCalculator::toRPN(const QVector<Token> &tokens, bool &ok, QString &error)
{
    // Алгоритм сортировочной станции (Shunting-yard) Дейкстры
    QVector<Token> output;
    QStack<Token> opStack;
    ok = true;

    for (const Token &token : tokens) {
        switch (token.type) {
        case Token::NUMBER:
            output.append(token);
            break;

        case Token::OPERATOR:
            // Правоассоциативность для ^ (степень)
            while (!opStack.isEmpty() &&
                   opStack.top().type == Token::OPERATOR &&
                   ((token.op != '^' && precedence(opStack.top().op) >= precedence(token.op)) ||
                    (token.op == '^' && precedence(opStack.top().op) >  precedence(token.op)))) {
                output.append(opStack.pop());
            }
            opStack.push(token);
            break;

        case Token::LEFT_PAREN:
            opStack.push(token);
            break;

        case Token::RIGHT_PAREN:
            while (!opStack.isEmpty() && opStack.top().type != Token::LEFT_PAREN)
                output.append(opStack.pop());
            if (opStack.isEmpty()) {
                ok = false; error = "Несбалансированные скобки"; return {};
            }
            opStack.pop(); // убираем '('
            break;
        }
    }

    while (!opStack.isEmpty()) {
        if (opStack.top().type == Token::LEFT_PAREN) {
            ok = false; error = "Несбалансированные скобки"; return {};
        }
        output.append(opStack.pop());
    }

    return output;
}

double RPNCalculator::calcRPN(const QVector<Token> &rpn, bool &ok, QString &error)
{
    QStack<double> stack;
    ok = true;

    for (const Token &token : rpn) {
        if (token.type == Token::NUMBER) {
            stack.push(token.number);
        } else if (token.type == Token::OPERATOR) {
            if (stack.size() < 2) {
                ok = false; error = "Некорректное выражение"; return 0;
            }
            double b = stack.pop();
            double a = stack.pop();
            double res = applyOp(token.op, a, b, ok, error);
            if (!ok) return 0;
            stack.push(res);
        }
    }

    if (stack.size() != 1) {
        ok = false; error = "Некорректное выражение"; return 0;
    }

    return stack.top();
}

double RPNCalculator::applyOp(QChar op, double a, double b, bool &ok, QString &error)
{
    ok = true;
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) { ok = false; error = "Деление на 0"; return 0; }
        return a / b;
    }
    if (op == '^') return std::pow(a, b);
    ok = false; error = "Неизвестный оператор"; return 0;
}

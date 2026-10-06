#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recordswindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QRegularExpressionValidator>
#include <random>
#include <algorithm>
#include <set>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , attemptsCount(0)
    , isGameActive(false)
{
    ui->setupUi(this);
    this->setWindowTitle("Быки и коровы");

    ui->tableHistory->setColumnCount(2);
    ui->tableHistory->setHorizontalHeaderLabels(QStringList() << "Число" << "Результат");
    ui->tableHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QRegularExpression rx("^[0-9]{4}$");
    QValidator* validator = new QRegularExpressionValidator(rx, this);
    ui->lineEditInput->setValidator(validator);

    ui->lineEditInput->setEnabled(false);
    ui->btnCheck->setEnabled(false);
    ui->labelStatus->setText("Игра не начата");

    connect(ui->btnNewGame, &QPushButton::clicked, this, &MainWindow::startNewGame);
    connect(ui->btnCheck, &QPushButton::clicked, this, &MainWindow::checkGuess);
    connect(ui->lineEditInput, &QLineEdit::returnPressed, this, &MainWindow::checkGuess);
    connect(ui->btnRecords, &QPushButton::clicked, this, &MainWindow::showRecords);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startNewGame() {
    generateSecretNumber();
    attemptsCount = 0;
    isGameActive = true;

    ui->tableHistory->setRowCount(0);
    ui->lineEditInput->setEnabled(true);
    ui->btnCheck->setEnabled(true);
    ui->lineEditInput->clear();
    ui->lineEditInput->setFocus();

    ui->labelStatus->setText("Игра началась!");
}

void MainWindow::generateSecretNumber() {
    std::vector<char> digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(digits.begin(), digits.end(), g);

    secretNumber.clear();
    for (int i = 0; i < 4; ++i) {
        secretNumber += digits[i];
    }
}

bool MainWindow::isValidInput(const QString& input) const {
    if (input.length() != 4) return false;

    std::set<QChar> uniqueChars;
    for (const QChar& c : input) {
        uniqueChars.insert(c);
    }
    return uniqueChars.size() == 4;
}

void MainWindow::checkGuess() {
    if (!isGameActive) return;

    QString guessStr = ui->lineEditInput->text();
    if (!isValidInput(guessStr)) {
        QMessageBox::warning(this, "Ошибка ввода", "Введите 4 уникальные цифры.");
        return;
    }

    attemptsCount++;
    std::string guess = guessStr.toStdString();

    int bulls = 0;
    int cows = 0;

    for (size_t i = 0; i < 4; ++i) {
        if (guess[i] == secretNumber[i]) {
            bulls++;
        } else if (secretNumber.find(guess[i]) != std::string::npos) {
            cows++;
        }
    }

    int row = ui->tableHistory->rowCount();
    ui->tableHistory->insertRow(row);
    ui->tableHistory->setItem(row, 0, new QTableWidgetItem(QString::number(attemptsCount) + "    " + guessStr));
    ui->tableHistory->setItem(row, 1, new QTableWidgetItem(QString("Быков: %1; Коров: %2").arg(bulls).arg(cows)));
    ui->tableHistory->scrollToBottom();

    ui->lineEditInput->clear();
    ui->lineEditInput->setFocus();

    if (bulls == 4) {
        handleVictory();
    } else {
        ui->labelStatus->setText("Не угадали, попробуйте еще...");
    }
}

void MainWindow::handleVictory() {
    isGameActive = false;
    ui->lineEditInput->setEnabled(false);
    ui->btnCheck->setEnabled(false);
    ui->labelStatus->setText("Победа!");

    QMessageBox::information(this, "Победа!", QString("Вы угадали число за %1 попыток!").arg(attemptsCount));

    RecordsWindow rw;
    if (rw.isNewRecord(attemptsCount)) {
        bool ok;
        QString name = QInputDialog::getText(this, "Новый рекорд", "Введите ваше имя:", QLineEdit::Normal, "", &ok);
        if (ok && !name.isEmpty()) {
            rw.addRecord(attemptsCount, name);
        }
    }
}

void MainWindow::showRecords() {
    RecordsWindow rw;
    rw.exec();
}

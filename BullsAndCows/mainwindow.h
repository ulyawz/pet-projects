#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startNewGame();
    void checkGuess();
    void showRecords();

private:
    void generateSecretNumber();
    void handleVictory();
    bool isValidInput(const QString& input) const;

    Ui::MainWindow *ui;
    std::string secretNumber;
    int attemptsCount;
    bool isGameActive;
};

#endif

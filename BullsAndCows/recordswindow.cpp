#include "recordswindow.h"
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
#include <algorithm>

RecordsWindow::RecordsWindow(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Рекорды");
    this->resize(300, 250);

    QVBoxLayout *layout = new QVBoxLayout(this);
    tableRecords = new QTableWidget(this);
    layout->addWidget(tableRecords);

    tableRecords->setColumnCount(2);
    tableRecords->setHorizontalHeaderLabels(QStringList() << "Попыток" << "Имя");
    tableRecords->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableRecords->setEditTriggers(QAbstractItemView::NoEditTriggers);

    loadRecords();
    updateTable();
}

RecordsWindow::~RecordsWindow() {}

void RecordsWindow::loadRecords() {
    records.clear();
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() == 2) {
                records.push_back({parts[0].toInt(), parts[1]});
            }
        }
        file.close();
    }
    std::sort(records.begin(), records.end());
}

void RecordsWindow::saveRecords() {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& rec : records) {
            out << rec.attempts << "|" << rec.name << "\n";
        }
        file.close();
    }
}

bool RecordsWindow::isNewRecord(int attempts) {
    loadRecords();
    if (records.size() < 5) return true;
    return attempts < records.back().attempts;
}

void RecordsWindow::addRecord(int attempts, const QString& name) {
    loadRecords();
    records.push_back({attempts, name});
    std::sort(records.begin(), records.end());

    if (records.size() > 5) {
        records.resize(5);
    }

    saveRecords();
    updateTable();
}

void RecordsWindow::updateTable() {
    tableRecords->setRowCount(0);
    for (size_t i = 0; i < records.size(); ++i) {
        tableRecords->insertRow(i);
        tableRecords->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(records[i].attempts)));
        tableRecords->setItem(i, 1, new QTableWidgetItem(records[i].name));
    }
}

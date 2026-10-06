#ifndef RECORDSWINDOW_H
#define RECORDSWINDOW_H

#include <QDialog>
#include <QString>
#include <QTableWidget>
#include <QVBoxLayout>
#include <vector>

struct RecordEntry {
    int attempts;
    QString name;

    bool operator<(const RecordEntry& other) const {
        return attempts < other.attempts;
    }
};

class RecordsWindow : public QDialog {
    Q_OBJECT

public:
    explicit RecordsWindow(QWidget *parent = nullptr);
    ~RecordsWindow();

    bool isNewRecord(int attempts);
    void addRecord(int attempts, const QString& name);

private:
    void loadRecords();
    void saveRecords();
    void updateTable();

    QTableWidget *tableRecords;
    std::vector<RecordEntry> records;
    const QString fileName = "records.txt";
};

#endif

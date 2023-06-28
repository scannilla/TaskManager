#ifndef FREQUENCYDIALOG_H
#define FREQUENCYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QTimer>

class FrequencyDialog : public QDialog
{
    Q_OBJECT

public:
    FrequencyDialog(QWidget* parent = nullptr);

    QList<QTimer*> getTimers(void);

private:
  


    QLabel* numberLabel;
    QLineEdit* numberLineEdit;
    QLabel* unitLabel;
    QComboBox* unitComboBox;
    QTableWidget* scheduleTable;

    //List of QTimer associated with the current task
    QList<QTimer*> timerList;

private slots:
    void handleAddScheduleButton();
    void handleDeleteButton();
};

#endif // FREQUENCYDIALOG_H



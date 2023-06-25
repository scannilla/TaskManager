#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QLabel>



class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    TaskDialog(QWidget* parent = nullptr);

    QString getTaskName() const;
    QString getAction() const;
    QDateTime getSchedule() const;

private:
    QComboBox* actionComboBox;
    QLineEdit* taskLineEdit;
    QLineEdit* actionLineEdit;
    QDateTimeEdit* scheduleDateTimeEdit;
    QLineEdit* textToPrintLineEdit;
    QLineEdit* fileToCheckLineEdit;
    QLabel* extraLabel;

private slots:
    void handleActionSelection(const QString& action);
};

#endif // TASKDIALOG_H


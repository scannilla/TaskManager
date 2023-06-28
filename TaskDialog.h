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
#include <QList>
#include <QTimer>



class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    TaskDialog(QWidget* parent = nullptr);

    QString getTaskName();

private:

    //Labels
    QLabel* taskLabel;
    QLabel* actionLabel;
    QLabel* descriptionLabel;
    QLabel* scheduleLabel;

    QLineEdit* taskLineEdit;
    QComboBox* actionComboBox;
    QLineEdit* descriptionLineEdit;
    QPushButton* schedulePushButton;

    QList<QTimer*> timerList;

private slots:
    void handleActionSelection(const QString& action);
    void handleButtonClicked();
};

#endif // TASKDIALOG_H


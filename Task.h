#pragma once

#include <QObject>
#include <QTimer>
#include <QMutex>


class Task : public QObject
{
    Q_OBJECT

public:
    Task();
    Task(QString name, bool action, QString description, QList<QTimer*> timerList);
    ~Task();

    void startTimers();
    QString getName();
    QString getAction();
    QString getDescription();
    QList<QTimer*> getTimers();
    void setTimers(QList<QTimer*> timerList);

private:
    QString* name;
    //Here the action is represented as a bool for semplicity
    //0 = print, 1 = check file
    bool action;
    QString* description;
    QList<QTimer*> timerList;

    //Task must be serialized and not parallelized
    QMutex mutex;

private slots:
    void handleTimer(QTimer* timedOutTImer);
};

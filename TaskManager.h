#ifndef TASKMANAGER_H
#define TASKMANAGER_H



#include <QtWidgets/QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QMutex>
#include <QMenu>
#include <QAction>

#include "Task.h"


class TaskManager : public QMainWindow
{
    Q_OBJECT

public:
    TaskManager(QWidget *parent = nullptr);
    ~TaskManager();

private:
    QSystemTrayIcon* trayIcon;
    QMenu *trayIconMenu;
    QList<Task*> taskList;

private slots:
    void handleTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void handleAddTask();
    void handleManageTasks();

};

#endif // TASKMANAGER_H

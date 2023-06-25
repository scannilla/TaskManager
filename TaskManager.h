#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TaskManager.h"
#include <QSystemTrayIcon>


class TaskManager : public QMainWindow
{
    Q_OBJECT

public:
    TaskManager(QWidget *parent = nullptr);
    ~TaskManager();

private:
    QSystemTrayIcon* trayIcon;
    QMenu *trayIconMenu;

private slots:
    void handleTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void handleAddTask();

};

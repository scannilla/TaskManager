/*
 * File: TaskManager.h
 * Author: S. Cannilla
 * -----------------------------
 * Description: Task class implementation
 *
 * -----------------------------
 * This file is part of TaskManager.
 *
 * TaskManager is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * TaskManager is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TaskManager. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <QtWidgets/QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QMutex>
#include <QMenu>
#include <QAction>

#include "Task.h"

/**
 * @brief The TaskManager class
 */
class TaskManager : public QMainWindow
{
    Q_OBJECT

public:
    /**
    * @brief TaskManager default constructor
    * @param[in] QWidget parent (default nullptr) parent widget
    * @return TaskManager object
    */
    TaskManager(QWidget *parent = nullptr);

    /**
    * @brief TaskManager destructor
    */
    ~TaskManager();

private:
    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;
    QList<Task*> taskList;

private slots:

    /**
    * @brief Open the add task dialog (TaskDialog)
    */
    void handleAddTask();

    /**
    * @brief Open the manage task dialog (ManageTaskDialog)
    */
    void handleManageTasks();

};

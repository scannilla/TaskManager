/*
 * File: TaskManager.cpp
 * Author: S. Cannilla
 * -----------------------------
 * Description: Create the QSystemTrayIcon and the associated menu
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

#include <QFile>
#include <QApplication>

#include "TaskManager.h"
#include "TaskDialog.h"
#include "ManageTaskDialog.h"

TaskManager::TaskManager(QWidget *parent)
    : QMainWindow(parent)
{
    //Create the tray icon
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/taskmanager.png"));
    trayIcon->setToolTip("Task Manager");
    trayIcon->show();

    //Create the tray icon menu
    trayIconMenu = new QMenu(this);

    //Create the actions
    QAction* quitAction = new QAction("Quit", this);
    QAction* addTaskAction = new QAction("Add task", this);
    QAction* manageTasksAction = new QAction("Manage tasks", this);

    //Add the actions to the menu
    trayIconMenu->addAction(addTaskAction);
    trayIconMenu->addAction(manageTasksAction);
    trayIconMenu->addAction(quitAction);

    //Connect the actions to the slots
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(addTaskAction, &QAction::triggered, this, &TaskManager::handleAddTask);
    connect(manageTasksAction, &QAction::triggered, this, &TaskManager::handleManageTasks);
    trayIcon->setContextMenu(trayIconMenu);

    //Initialize the task list
    taskList = QList<Task*>();
}

TaskManager::~TaskManager()
{}


void TaskManager::handleAddTask()
{
    TaskDialog dialog;

    // Execute the dialog as a modal dialog
    if (dialog.exec() == QDialog::Accepted) {
        //Create a new task
        Task* task = new Task(dialog.getTaskName(), dialog.getAction(), dialog.getDescription(), dialog.getTimers());
        taskList.append(task);
    }
    else {
		qDebug() << "User canceled the dialog";
	}
}

void TaskManager::handleManageTasks()
{
	//Open the ManageTaskDialog
    ManageTaskDialog* manageTaskDialog = new ManageTaskDialog(taskList);
    manageTaskDialog->exec();
}


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

    //Connect the tray icon to the slot
    connect(trayIcon, &QSystemTrayIcon::activated, this, &TaskManager::handleTrayIcon);

    //Create the tray icon menu
    trayIconMenu = new QMenu(this);
    QAction* quitAction = new QAction("Quit", this);
    QAction* addTaskAction = new QAction("Add task", this);
    QAction* manageTasksAction = new QAction("Manage tasks", this);
    trayIconMenu->addAction(addTaskAction);
    trayIconMenu->addAction(quitAction);
    trayIconMenu->addAction(manageTasksAction);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(addTaskAction, &QAction::triggered, this, &TaskManager::handleAddTask);
    connect(manageTasksAction, &QAction::triggered, this, &TaskManager::handleManageTasks);
    trayIcon->setContextMenu(trayIconMenu);
}

TaskManager::~TaskManager()
{}

void TaskManager::handleTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        if (this->isVisible())
        {
			this->hide();
		}
        else
        {
			this->show();
		}
    }
}

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


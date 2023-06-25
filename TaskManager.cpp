#include "TaskManager.h"
#include "TaskDialog.h"

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
    QAction *quitAction = new QAction("Quit", this);
    QAction *addTaskAction = new QAction("Add task", this);
    trayIconMenu->addAction(addTaskAction);
    trayIconMenu->addAction(quitAction);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(addTaskAction, &QAction::triggered, this, &TaskManager::handleAddTask);
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
        // Retrieve the input values from the dialog
        QString taskName = dialog.getTaskName();
        QString action = dialog.getAction();
        QDateTime schedule = dialog.getSchedule();

        // Process the input values as needed
        // For example, you can add the task to a list or perform any other task

        // Print the values to the console as an example
        qDebug() << "Task Name: " << taskName;
        qDebug() << "Action: " << action;
        qDebug() << "Schedule: " << schedule.toString(Qt::ISODate);
    }
    else {
		qDebug() << "User canceled the dialog";
	}
}
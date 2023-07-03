/*
 * File: ManageTaskDialog.h
 * Author: S. Cannilla
 * -----------------------------
 * Description: ManageTaskDialog is a QDialog that allows the user to manage the
 * already existing tasks.
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
#include <QDialog>
#include "Task.h"
#include <QTableWidget>

/**
 * @brief The ManageTaskDialog class
 */
class ManageTaskDialog : public QDialog
{
    Q_OBJECT

public:

    /**
    * @brief ManageTaskDialog
    * @param[in] QList<Task*> taskList list of existing tasks
    * @param[in] QWidget* parent (default nullptr) parent widget
    * @return ManageTaskDialog object
    */
    ManageTaskDialog(QList<Task*> taskList, QWidget* parent = nullptr);

private:

    QList<Task*> taskList;
    QTableWidget* table;
    
private slots:

    /**
    * @brief opens the schedule dialog for the selected task
    */
    void handleScheduleButton();

    /**
    * @brief deletes the selected task
    *
    */
	void handleDeleteButton();
};


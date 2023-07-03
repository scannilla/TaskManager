/*
 * File: TaskDialog.h
 * Author: S. Cannilla
 * -----------------------------
 * Description: TaskDialog is a QDialog that allows the user to create a new
 * task.
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
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QLabel>
#include <QList>
#include <QTimer>


/**
* @brief The TaskDialog class (Add Task Dialog)
*/
class TaskDialog : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief TaskDialog
    * @param[in] QWidget* parent (default nullptr) parent widget
    * @return TaskDialog object
    */
    TaskDialog(QWidget* parent = nullptr);

    /**
    * @brief Returns the task name
    * @return QString task name
    */
    QString getTaskName();

    /**
    * @brief Returns the task action in bool format
    * @return bool task action
    */
    bool getAction();

    /**
    * @brief Returns the task description (either the text to print or the
    * file to check)
    * @return QString task description
    */
    QString getDescription();

    /**
    * @brief Returns the list of timers associated to the task
    * @return QList<QTimer*> list of timers
    */
    QList<QTimer*> getTimers();

private:

    //Labels
    QLabel* taskLabel;
    QLabel* actionLabel;
    QLabel* descriptionLabel;
    QLabel* scheduleLabel;

    //Fields
    QLineEdit* taskLineEdit;
    QComboBox* actionComboBox;
    QLineEdit* descriptionLineEdit;
    QPushButton* schedulePushButton;

    QList<QTimer*> timerList;

private slots:

    /**
    * @brief change the label of the description field based on the combo box
    * @param[in] QString action the action selected in the combo box
    */
    void handleActionSelection(const QString& action);

    /**
    * @brief open the schedule dialog
    */
    void handleButtonClicked();
};


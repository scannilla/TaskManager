/*
 * File: Task.h
 * Author: S. Cannilla
 * -----------------------------
 * Description: Task is a class that represents a task.
 * (A task can be a print or a file check)
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

#include <QObject>
#include <QTimer>
#include <QMutex>


/**
* @brief The Task class
*/
class Task : public QObject
{
    Q_OBJECT

public:

    /**
    * @brief Task default constructor
    */
    Task();
    /**
    * @brief Task constructor
    * @param[in] QString name task name
    * @param[in] bool action task action
    * @param[in] QString description task description
    * @param[in] QList<QTimer*> timerList list of timers associated to the task
    * @return Task object
    */
    Task(QString name, bool action, QString description, QList<QTimer*> timerList);
    ~Task();

    /**
    * @brief starts all the timers associated to the task
    */
    void startTimers();

    /**
    * @brief get the task name
    * @return QString task name
    */
    QString getName();

    /**
    * @brief get the task action, trasnformed in a QString (0 = print, 
    * 1 = check file)
    * @return QString task action
    */
    QString getAction();

    /**
    * @brief get the task description
    * @return QString task description
    */
    QString getDescription();

    /**
    * @brief get the list of timers associated to the task
    * @return QList<QTimer*> list of timers associated to the task
    */
    QList<QTimer*> getTimers();

    /**
    * @brief set the task timers
    * @param[in] QList<QTimer*> timerList new list of timers to be associated
    * to the task
    */
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

    /**
    * @brief handles the timeout of a timer
    * @param[in] QTimer* timedOutTimer timer that timed out
    */
    void handleTimer(QTimer* timedOutTImer);
};

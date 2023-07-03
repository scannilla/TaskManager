/*
 * File: Task.cpp
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

#include <QFile>
#include <QDebug>
#include "Task.h"


Task::Task()
{
    name = new QString();
    action = false;
    description = new QString();
    timerList = QList<QTimer*>();
}

Task::Task(QString name, bool action, QString description, QList<QTimer*> timerList)
{
    this->name = new QString(name);
    this->action = action;
    this->description = new QString(description);
    this->timerList = timerList;

    startTimers();
}

Task::~Task()
{
    delete name;
    delete description;
    for (int i = 0; i < timerList.size(); i++)
    {
        delete timerList.at(i);
    }
}

void Task::startTimers()
{
    for (int i = 0; i < timerList.size(); i++)
    {
        timerList.at(i)->start();
        //Connect the timer to the slot passing the timer itself
        connect(timerList.at(i), &QTimer::timeout, this, [this, timer = timerList.at(i)]() { handleTimer(timer); });
    }
}

void Task::handleTimer(QTimer* timedOutTImer)
{
    //Serialize task execution
    mutex.lock();
    if (action)
    {
        //Try to open the file in the path contained in description
        QFile file(*description);
        if (file.open(QIODevice::ReadOnly))
        {
            qDebug() << "File exists";
            file.close();
        }
    }
    else
    {
        //Print the selected string
        qDebug() << *description;
    }
    timedOutTImer->start();
    mutex.unlock();
}

QString Task::getName()
{
	return *name;
}

QString Task::getAction()
{
    //Trasnform the bool value in a string
	if(action)
        return "Check File";
    else
        return "Print";
}

QString Task::getDescription()
{
	return *description;
}

QList<QTimer*> Task::getTimers()
{
	return timerList;
}

void Task::setTimers(QList<QTimer*> timerList)
{
	this->timerList = timerList;

    startTimers();
}
#include "Task.h"
#include <QFile>
#include <QDebug>

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
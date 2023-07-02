#pragma once
#include <QDialog>
#include "Task.h"
#include <QTableWidget>

class ManageTaskDialog : public QDialog
{
    Q_OBJECT

public:
    ManageTaskDialog(QList<Task*> taskList, QWidget* parent = nullptr);

private:
    QList<Task*> taskList;
    QTableWidget* table;
    
private slots:
    void handleScheduleButton();
	void handleDeleteButton();
};


#include "ManageTaskDialog.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include "FrequencyDialog.h"
#include <QDialogButtonBox>

ManageTaskDialog::ManageTaskDialog(QList<Task*> taskList, QWidget* parent)
	: QDialog(parent)
{
	setWindowTitle("Manage Task Dialog");

	//Set the task list
	
	//This is potentially dangerous because the task list is passed by reference
	//But we know that the task list can only be modified by adding or removing tasks
	//And this is the only dialog that deletes tasks
	this->taskList = taskList;

	//Create a table with 4 columns: Name, Action, Schedule button and Delete button
	QVBoxLayout* layout = new QVBoxLayout(this);
	table = new QTableWidget;
	table->setColumnCount(4);
	table->setHorizontalHeaderLabels(QStringList() << "Name" << "Action" << "Schedule" << "Delete");
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	table->verticalHeader()->hide();
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	
	//Add each task to the table
	for (int i = 0; i < taskList.size(); i++) {
		Task* task = taskList.at(i);
		table->insertRow(i);
		table->setItem(i, 0, new QTableWidgetItem(task->getName()));
		table->setItem(i, 1, new QTableWidgetItem(task->getAction()));
		QPushButton* scheduleButton = new QPushButton("Schedule");
		table->setCellWidget(i, 2, scheduleButton);
		QPushButton* deleteButton = new QPushButton("Delete");
		table->setCellWidget(i, 3, deleteButton);
		connect(scheduleButton, &QPushButton::clicked, this, &ManageTaskDialog::handleScheduleButton);
		connect(deleteButton, &QPushButton::clicked, this, &ManageTaskDialog::handleDeleteButton);
	}

	//Add the table to the layout
	layout->addWidget(table);

	//Add a button box with an OK button
	QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
	layout->addWidget(buttonBox);
	connect(buttonBox, &QDialogButtonBox::accepted, this, &ManageTaskDialog::accept);


}

void ManageTaskDialog::handleScheduleButton() {
	//When the schedule button is pressed, open the FrequencyDialog passing the timer list of the selected task
	QPushButton* scheduleButton = qobject_cast<QPushButton*>(sender());
	int row = table->indexAt(scheduleButton->pos()).row();
	Task* task = taskList.at(row);
	FrequencyDialog dialog(task->getTimers());
	if (dialog.exec() == QDialog::Accepted)
	{
		//If the dialog is accepted, update the timer list of the task
		task->setTimers(dialog.getTimers());
	}
}

void ManageTaskDialog::handleDeleteButton() {
	//When the delete button is pressed, delete the task from the table
	QPushButton* deleteButton = qobject_cast<QPushButton*>(sender());
	int row = table->indexAt(deleteButton->pos()).row();
	//Get the task from the task list and delete it
	Task* task = taskList.at(row);
	taskList.removeOne(task);
	delete task;
	//Delete the row from the table
	table->removeRow(row);

	
}
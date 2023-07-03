/*
 * File: FrequencyDialog.cpp
 * Author: S. Cannilla
 * -----------------------------
 * Description: Add or remove timers from a task
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

#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QPushButton>

#include "FrequencyDialog.h"


FrequencyDialog::FrequencyDialog(QWidget* parent)
    : QDialog(parent)
{
    timerList = QList<QTimer*>();
    setupLayout();
}

FrequencyDialog::FrequencyDialog(QList<QTimer*> timerList, QWidget* parent)
    : QDialog(parent)
{
    this->timerList = timerList;
	setupLayout();
	
}

void FrequencyDialog::setupLayout() {
    setWindowTitle("Frequency Dialog");

    QVBoxLayout* layout = new QVBoxLayout(this);

    //Indicates the frequency of the timer
    numberLabel = new QLabel("Number:");
    numberLineEdit = new QLineEdit;

    //Indicates the unit of measure of the timer
    unitLabel = new QLabel("Unit of Measure:");
    unitComboBox = new QComboBox;
    unitComboBox->addItem("seconds");
    unitComboBox->addItem("minutes");
    unitComboBox->addItem("hours");
    unitComboBox->addItem("days");
    
    //Create a new timer button
    QPushButton* addScheduleButton = new QPushButton("Add Schedule");
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    //Add all the widgets to the layout
    layout->addWidget(numberLabel);
    layout->addWidget(numberLineEdit);
    layout->addWidget(unitLabel);
    layout->addWidget(unitComboBox);
    layout->addWidget(addScheduleButton);
    layout->addWidget(buttonBox);
    
    //Connect the buttons to their slots
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(addScheduleButton, &QPushButton::clicked, this, &FrequencyDialog::handleAddScheduleButton);

    //Create a table to hold all the schedules, everytime the add button is pressed a new row is added to the table
    scheduleTable = new QTableWidget;
    scheduleTable->setColumnCount(3);
    scheduleTable->setHorizontalHeaderLabels(QStringList() << "Frequency" << "Unit of Measure" << "Delete");
    scheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    scheduleTable->verticalHeader()->hide();
    scheduleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    scheduleTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    scheduleTable->setSelectionMode(QAbstractItemView::SingleSelection);

    //If the timer list is not empty, populate the table with the timers
    if (!timerList.isEmpty()) {
        for (int i = 0; i < timerList.size(); i++) {
			int row = scheduleTable->rowCount();
			scheduleTable->insertRow(row);
            //Interval in seconds
            int interval = timerList.at(i)->interval() / 1000;
			scheduleTable->setItem(row, 0, new QTableWidgetItem(QString::number(interval)));
			scheduleTable->setItem(row, 1, new QTableWidgetItem("seconds"));

			//add a delete button to the third column
			QPushButton* deleteButton = new QPushButton("Delete");
			scheduleTable->setCellWidget(row, 2, deleteButton);

			//connect the delete button to a slot that will delete the row
			connect(deleteButton, &QPushButton::clicked, this, &FrequencyDialog::handleDeleteButton);

			//Everytime a new row is added, resize the table to fit the new row
			scheduleTable->resizeRowsToContents();
		}
	}

    layout->addWidget(scheduleTable);
}

QList<QTimer*> FrequencyDialog::getTimers() {
	return timerList;
}

void FrequencyDialog::handleAddScheduleButton() {
    //When the add button is pressed, take the info from the line edit and combo box and add it to the table
    int row = scheduleTable->rowCount();
    scheduleTable->insertRow(row);
    scheduleTable->setItem(row, 0, new QTableWidgetItem(numberLineEdit->text()));
    scheduleTable->setItem(row, 1, new QTableWidgetItem(unitComboBox->currentText()));

    //add a delete button to the third column
    QPushButton* deleteButton = new QPushButton("Delete");
    scheduleTable->setCellWidget(row, 2, deleteButton);

    //connect the delete button to a slot that will delete the row
    connect(deleteButton, &QPushButton::clicked, this, &FrequencyDialog::handleDeleteButton);

    //Everytime a new row is added, resize the table to fit the new row
    scheduleTable->resizeRowsToContents();

    //When a new entry is added, create a QTimer and add it to the list of timers
    QTimer* timer = new QTimer;
    timerList.append(timer);

    //Configure the new timer depending on the unit of measure and frequency
    if (unitComboBox->currentText() == "seconds") {
		timer->setInterval(numberLineEdit->text().toInt() * 1000);
	}
    else if (unitComboBox->currentText() == "minutes") {
		timer->setInterval(numberLineEdit->text().toInt() * 1000 * 60);
	}
    else if (unitComboBox->currentText() == "hours") {
		timer->setInterval(numberLineEdit->text().toInt() * 1000 * 60 * 60);
	}
    else if (unitComboBox->currentText() == "days") {
		timer->setInterval(numberLineEdit->text().toInt() * 1000 * 60 * 60 * 24);
	}

}

void FrequencyDialog::handleDeleteButton() {
	//When the delete button is pressed, delete the row that the button is in
	QPushButton* deleteButton = qobject_cast<QPushButton*>(sender());
	int row = scheduleTable->indexAt(deleteButton->pos()).row();
    //Get the timer from the timer list and delete it
    QTimer* timer = timerList.at(row);
    timerList.removeOne(timer);
    delete timer;
    //Remove the row from the table
	scheduleTable->removeRow(row);
}
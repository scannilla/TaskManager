/*
 * File: TaskDialog.cpp
 * Author: S. Cannilla
 * -----------------------------
 * Description: Create a new task
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
#include <QPushButton>

#include "TaskDialog.h"
#include "FrequencyDialog.h"

TaskDialog::TaskDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Add Task");

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Task Name
    taskLabel = new QLabel("Task Name:");
    taskLineEdit = new QLineEdit;

    // Task Layout
    QHBoxLayout* taskLayout = new QHBoxLayout;
    taskLayout->addWidget(taskLabel);
    taskLayout->addWidget(taskLineEdit);

    // Action
    actionLabel = new QLabel("Action:");
    actionComboBox = new QComboBox;
    actionComboBox->addItem("Please select an action");
    actionComboBox->setCurrentIndex(0);
    actionComboBox->setItemData(0, false, Qt::ItemIsEnabled);
    actionComboBox->addItem("Print");
    actionComboBox->addItem("Check File");

    // Action Layout
    QHBoxLayout* actionLayout = new QHBoxLayout;
    actionLayout->addWidget(actionLabel);
    actionLayout->addWidget(actionComboBox);

    //Change the description label and line edit based on the action selected
    connect(actionComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, &TaskDialog::handleActionSelection);

    descriptionLabel = new QLabel;
    descriptionLineEdit = new QLineEdit;

    //Show the description label and line edit as disabled until an action is selected
    descriptionLabel->setEnabled(false);
    descriptionLineEdit->setEnabled(false);

    QHBoxLayout* extraLayout = new QHBoxLayout;
    extraLayout->addWidget(descriptionLabel);
    extraLayout->addWidget(descriptionLineEdit);
    extraLayout->setContentsMargins(0, 0, 0, 0);

    // Schedule
    scheduleLabel = new QLabel("Schedule:");
    schedulePushButton = new QPushButton("Schedule");
    connect(schedulePushButton, &QPushButton::clicked, this, &TaskDialog::handleButtonClicked);
    QHBoxLayout* scheduleLayout = new QHBoxLayout;
    scheduleLayout->addWidget(scheduleLabel);
    scheduleLayout->addWidget(schedulePushButton);

    // Buttons
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    // Add layouts to main layout
    layout->addLayout(taskLayout);
    layout->addLayout(actionLayout);
    layout->addLayout(extraLayout);
    layout->addLayout(scheduleLayout);
    layout->addWidget(buttonBox);
}

QString TaskDialog::getTaskName()
{
    return taskLineEdit->text();
}

bool TaskDialog::getAction()
{
	if (actionComboBox->currentText() == "Print")
		return false;
	else
		return true;
}

QString TaskDialog::getDescription()
{
	return descriptionLineEdit->text();
}

QList<QTimer*> TaskDialog::getTimers()
{
	return timerList;
}



void TaskDialog::handleActionSelection(const QString& action)
{
    if (action == "Print") {
        descriptionLabel->setEnabled(true);
        descriptionLineEdit->setEnabled(true);
        descriptionLabel->setText("Text to Print:");
    }
    else if (action == "Check File") {
        descriptionLabel->setEnabled(true);
        descriptionLineEdit->setEnabled(true);
        descriptionLabel->setText("File to Check:");
    }
    else if (action == "Please select an action") {
		descriptionLabel->setEnabled(false);
        descriptionLineEdit->setEnabled(false);
	}
}


void TaskDialog::handleButtonClicked(void) {
    FrequencyDialog* frequencyDialog = new FrequencyDialog(this);
    if (frequencyDialog->exec() == QDialog::Accepted)
    {
        timerList = frequencyDialog->getTimers();
        
    }

}
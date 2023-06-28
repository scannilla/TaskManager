#include "frequencydialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QPushButton>

FrequencyDialog::FrequencyDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Frequency Dialog");

    QVBoxLayout* layout = new QVBoxLayout(this);

    numberLabel = new QLabel("Number:");
    numberLineEdit = new QLineEdit;

    unitLabel = new QLabel("Unit of Measure:");
    unitComboBox = new QComboBox;
    unitComboBox->addItem("seconds");
    unitComboBox->addItem("minutes");
    unitComboBox->addItem("hours");
    unitComboBox->addItem("days");

    QPushButton* addScheduleButton = new QPushButton("Add Schedule");
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    layout->addWidget(numberLabel);
    layout->addWidget(numberLineEdit);
    layout->addWidget(unitLabel);
    layout->addWidget(unitComboBox);
    layout->addWidget(addScheduleButton);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(addScheduleButton, &QPushButton::clicked, this, &FrequencyDialog::handleAddScheduleButton);

    //Create a table to hold all the schedules, everytime the add button is pressed a new row is added to the table
    scheduleTable = new QTableWidget;

    //add a third column to the table to hold the delete button
    scheduleTable->setColumnCount(3);
    scheduleTable->setHorizontalHeaderLabels(QStringList() << "Frequency" << "Unit of Measure" << "Delete");
    scheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    scheduleTable->verticalHeader()->hide();
    scheduleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    scheduleTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    scheduleTable->setSelectionMode(QAbstractItemView::SingleSelection);

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
	scheduleTable->removeRow(row);
}
#include "taskdialog.h"
#include <QPushButton>
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
    actionComboBox->addItem("Plasse select an action");
    actionComboBox->setCurrentIndex(0);
    actionComboBox->setItemData(0, false, Qt::ItemIsEnabled);
    actionComboBox->addItem("Print");
    actionComboBox->addItem("Check File");

    // Action Layout
    QHBoxLayout* actionLayout = new QHBoxLayout;
    actionLayout->addWidget(actionLabel);
    actionLayout->addWidget(actionComboBox);

    connect(actionComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, &TaskDialog::handleActionSelection);

    descriptionLabel = new QLabel("Text to Print:");
    descriptionLineEdit = new QLineEdit;

    QHBoxLayout* extraLayout = new QHBoxLayout;
    extraLayout->addWidget(descriptionLabel);
    extraLayout->addWidget(descriptionLineEdit);
    extraLayout->setContentsMargins(0, 0, 0, 0);
    extraLayout->setEnabled(false);

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



void TaskDialog::handleActionSelection(const QString& action)
{
    if (action == "Print") {
        descriptionLabel->setText("Text to Print:");
    }
    else if (action == "Check File") {
        descriptionLabel->setText("File to Check:");
    }
}


void TaskDialog::handleButtonClicked(void) {
    FrequencyDialog* frequencyDialog = new FrequencyDialog(this);
    if (frequencyDialog->exec() == QDialog::Accepted)
    {
        // Handle the frequency settings
        int frequency = frequencyDialog->getFrequency();
        QString unitOfMeasure = frequencyDialog->getUnitOfMeasure();

    }

}
#include "taskdialog.h"

TaskDialog::TaskDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Add Task");

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Task Name
    QLabel* taskLabel = new QLabel("Task Name:");
    taskLineEdit = new QLineEdit;
    QHBoxLayout* taskLayout = new QHBoxLayout;
    taskLayout->addWidget(taskLabel);
    taskLayout->addWidget(taskLineEdit);

    // Action

    QLabel* actionLabel = new QLabel("Action:");
    actionComboBox = new QComboBox;
    actionComboBox->addItem("Plasse select an action");
    actionComboBox->setCurrentIndex(0);
    actionComboBox->setItemData(0, false, Qt::ItemIsEnabled);
    actionComboBox->addItem("Print");
    actionComboBox->addItem("Check File");

    QHBoxLayout* actionLayout = new QHBoxLayout;
    actionLayout->addWidget(actionLabel);
    actionLayout->addWidget(actionComboBox);

    bool bRet= connect(actionComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged),
        this, &TaskDialog::handleActionSelection);
    Q_ASSERT(bRet);

    extraLabel = new QLabel("Text to Print:");
    textToPrintLineEdit = new QLineEdit;
    fileToCheckLineEdit = new QLineEdit;

    QHBoxLayout* extraLayout = new QHBoxLayout;
    extraLayout->addWidget(extraLabel);
    extraLayout->addWidget(textToPrintLineEdit);
    extraLayout->addWidget(fileToCheckLineEdit);
    extraLayout->setContentsMargins(0, 0, 0, 0);
    extraLayout->setEnabled(false);

    // Schedule
    QLabel* scheduleLabel = new QLabel("Schedule:");
    scheduleDateTimeEdit = new QDateTimeEdit;
    QHBoxLayout* scheduleLayout = new QHBoxLayout;
    scheduleLayout->addWidget(scheduleLabel);
    scheduleLayout->addWidget(scheduleDateTimeEdit);

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

QString TaskDialog::getTaskName() const
{
    return taskLineEdit->text();
}

QString TaskDialog::getAction() const
{
    return actionLineEdit->text();
}

QDateTime TaskDialog::getSchedule() const
{
    return scheduleDateTimeEdit->dateTime();
}

void TaskDialog::handleActionSelection(const QString& action)
{
    if (action == "Print") {
        extraLabel->setText("Text to Print:");
        textToPrintLineEdit->setEnabled(true);
        fileToCheckLineEdit->setEnabled(false);
    }
    else if (action == "Check File") {
        extraLabel->setText("File to Check:");
        textToPrintLineEdit->setEnabled(false);
        fileToCheckLineEdit->setEnabled(true);
    }
}

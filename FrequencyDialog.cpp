#include "frequencydialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>

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

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    layout->addWidget(numberLabel);
    layout->addWidget(numberLineEdit);
    layout->addWidget(unitLabel);
    layout->addWidget(unitComboBox);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

int FrequencyDialog::getFrequency()
{
    return numberLineEdit->text().toInt();
}

QString FrequencyDialog::getUnitOfMeasure()
{
    return unitComboBox->currentText();
}

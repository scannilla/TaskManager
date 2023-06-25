#ifndef FREQUENCYDIALOG_H
#define FREQUENCYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

class FrequencyDialog : public QDialog
{
    Q_OBJECT

public:
    FrequencyDialog(QWidget* parent = nullptr);

    int getFrequency();
    QString getUnitOfMeasure();

private:
  


    QLabel* numberLabel;
    QLineEdit* numberLineEdit;
    QLabel* unitLabel;
    QComboBox* unitComboBox;
};

#endif // FREQUENCYDIALOG_H



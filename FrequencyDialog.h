/*
 * File: FrequencyDialog.h
 * Author: S. Cannilla
 * -----------------------------
 * Description: FrequencyDialog is a QDialog that allows the user to set the
 * frequency of the task.
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

#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <QTimer>

/**
 * @brief The FrequencyDialog class
 */
class FrequencyDialog : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief FrequencyDialog default constructor
    * @param[in] QWidget* parent (default nullptr) parent widget
    * @return FrequencyDialog object
    */
    FrequencyDialog(QWidget* parent = nullptr);

    /**
    * @brief FrequencyDialog constructor
    * @param[in] QList<QTimer*> timerList list of QTimer associated with the
    * selected task
    * @param[in] QWidget* parent (default nullptr) parent widget
    * @return FrequencyDialog object
    */
    FrequencyDialog(QList<QTimer*> timerList, QWidget* parent = nullptr);

    /**
    * @brief Setups the layout of the dialog
    */
    void setupLayout();

    /**
    * @brief Returns the list of QTimer associated with the selected task
    * @return QList<QTimer*> list of QTimer associated with the selected task
    */
    QList<QTimer*> getTimers(void);

private:
  
    QLabel* numberLabel;
    QLineEdit* numberLineEdit;
    QLabel* unitLabel;
    QComboBox* unitComboBox;
    QTableWidget* scheduleTable;

    //List of QTimer associated with the current task
    QList<QTimer*> timerList;

private slots:

    /**
    * @brief Adds a new schedule to the list
    */
    void handleAddScheduleButton();

    /*
    * @brief Deletes the selected schedule from the list
    **/
    void handleDeleteButton();
};




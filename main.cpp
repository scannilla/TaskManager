/*
 * File: main.cpp
 * Author: S. Cannilla
 * -----------------------------
 * Description: main function
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
#include <QtWidgets/QApplication>

#include "TaskManager.h"

/**
* @brief main function
* @param[in] argc number of arguments
* @param[in] argv arguments
* @return int exit code
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Needed to keep the application running after the last window is closed
    a.setQuitOnLastWindowClosed(false);
    TaskManager w;
    
    return a.exec();
}

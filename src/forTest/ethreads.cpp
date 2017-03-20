/*
 * Copyright (C) <2017>  <Yehor Raketskyi(egormilo@gmail.com)>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ethreads.h"
#include <QTimer>
#include "src/logger/logger.h"

void EThreads::run()
  {

    while (shotCounter > 0)
      {
        timerHandler();
        QThread::msleep(1);
      }
    this->exit();
  }

void EThreads::timerHandler()
  {
    LOG_EMERGENCY("EMERGENCY!");
    LOG_ALERT("ALERT!");
    LOG_CRITICAL("CRITICAL!");
    LOG_ERROR("ERROR!");
    LOG_WARNING("WARNING!");
    LOG_NOTICE("NOTICE!");
    LOG_INFORMATIONAL("INFORMATIONAL!");
    LOG_DEBUG("DEBUG!");
    LOG_DEBUG(QString("shotCounter is %1").arg(QString::number(shotCounter)));
    shotCounter--;
  }

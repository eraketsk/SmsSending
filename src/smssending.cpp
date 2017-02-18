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

#include "smssending.h"
#include "ui_smssending.h"

#include <QTextStream>
#include "src/logger/logger.h"
#include "src/forTest/ethreads.h"

SmsSending::SmsSending(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SmsSending)
  {
    ui->setupUi(this);
  }

SmsSending::~SmsSending()
  {
    delete ui;
  }

void SmsSending::on_pushButton_clicked()
  {
    EMERGENCY("EMERGENCY");
    ALERT("ALERT");
    CRITICAL("CRITICAL");
    ERROR("ERROR");
    WARNING("WARNING");
    NOTICE("NOTICE");
    INFORMATIONAL("INFORMATIONAL");
    DEBUG("DEBUG");
    for (int i = 0; i < 300;i++)
      {
        EThreads* thread = new EThreads();
        thread->start();
      }
  }

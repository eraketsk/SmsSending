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

#ifndef SMSSENDING_H
#define SMSSENDING_H

#include <QMainWindow>

namespace Ui {
  class SmsSending;
  }

class SmsSending : public QMainWindow
  {
    Q_OBJECT

  public:
    explicit SmsSending(QWidget *parent = 0);
    ~SmsSending();

  private:
    Ui::SmsSending *ui;
  };

#endif // SMSSENDING_H

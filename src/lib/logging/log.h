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

#ifndef LOG_H
#define LOG_H

//---------LOG LEVEL------------------
/* rfc 5424
    0       Emergency: system is unusable
    1       Alert: action must be taken immediately
    2       Critical: critical conditions
    3       Error: error conditions
    4       Warning: warning conditions
    5       Notice: normal but significant condition
    6       Informational: informational messages
    7       Debug: debug-level messages
  */
#define LOG_LEVEL_EMERGENCY     0
#define LOG_LEVEL_ALERT         1
#define LOG_LEVEL_CRITICAL      2
#define LOG_LEVEL_ERROR         3
#define LOG_LEVEL_WARNING       4
#define LOG_LEVEL_NOTICE        5
#define LOG_LEVEL_INFORMATIONAL 6
#define LOG_LEVEL_DEBUG         7

#define DEFAULT_LOG_LEVEL LOG_LEVEL_DEBUG

#define DEFAULT_LOG_DIR "logs/tets/dir"
#define DEFAULT_LOG_PATH DEFAULT_LOG_DIR

#endif // LOG_H

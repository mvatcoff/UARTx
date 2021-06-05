/*
This is a software to write and read data from USB-UART port in Linux systems

Copyright (C) 2021  Mariano Vatcoff <marianovatcoff@gmail.com>

    This file is part of UARTx

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

int kbhit();
void init_keyboard();
void close_keyboard();
int readch();
void khbit_loop(int *fd, FILE *fd_log);

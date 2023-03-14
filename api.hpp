/*
 * Glacier OS
 * Copyright (C) 2023 Johnny Stene
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef API_HPP
#define API_HPP

#include <stdbool.h>

// FS functions
#define FS_TYPE_DIRECTORY 0
#define FS_TYPE_FILE 1

void fs_init();
void fs_shutdown();
bool fs_format();
bool fs_open(const char* path, const char* mode);
bool fs_exists(const char* path);
bool fs_mkdir(const char* path);
bool fs_rmdir(const char* path);
bool fs_open_dir(const char* path);
bool fs_dir_next(char* buffer, int buffer_len, int* type);
bool fs_delete(const char* path);
bool fs_rename(const char* path);
void fs_seek(int offset);
int fs_position();
int fs_size();
void fs_read(char* buffer, int length);
void fs_write(char* buffer, int length);


#endif
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

#ifndef FS_HPP
#define FS_HPP

#include <SDFS.h>
File fs_file;
Dir fs_dir;

void fs_init() {
    SDFS.begin();
}

void fs_shutdown() {
    SDFS.end();
}

bool fs_format() {
    return SDFS.format();
}

bool fs_open(const char* path, const char* mode) {
    fs_file = SDFS.open(path, mode);
    return (!fs_file);
}

bool fs_exists(const char* path) {
    return SDFS.exists(path);
}

bool fs_mkdir(const char* path) {
    return SDFS.mkdir(path);
}

bool fs_rmdir(const char* path) {
    return SDFS.rmdir(path);
}

bool fs_open_dir(const char* path) {
    fs_dir = SDFS.opendir(path);
    return true;
}

bool fs_dir_next(char* buffer, int buffer_len, int* type) {
    if(fs_dir.next()) {
        const char* filename = fs_dir.fileName();
        for(int i = 0; i < buffer_len; i++) {
            if(filename[i] == '\0') {
                break;
            }
            buffer[i] = filename[i];
        }

        if(fs_dir.isFile()) type[0] = FS_TYPE_FILE;
        else type[0] = FS_TYPE_DIRECTORY;
        return true;
    } else return false;
}

bool fs_delete(const char* path) {

}

bool fs_rename(const char* path) {

}

void fs_seek(int offset) {

}

int fs_position() {

}

int fs_size() {

}

void fs_read(char* buffer, int length) {

}

void fs_write(char* buffer, int length) {

}

#endif
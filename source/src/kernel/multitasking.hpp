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

typedef struct {
    bool in_use;
    String name;
    xTaskHandle handle;
} process_t;

process_t tasks[MAXIMUM_PROCESS_COUNT];
int foreground_process;

int get_process_pid(String name) {
    for(int i = 0; i < MAXIMUM_PROCESS_COUNT; i++) {
        if(tasks[i].in_use) {
            if(name == tasks[i].name) return i;
        }
    }
    return -1;
}

int spawn_process(String name, void(*function)(void*), int priority) {
    for(int i = 0; i < MAXIMUM_PROCESS_COUNT; i++) {
        if(!tasks[i].in_use) {
            tasks[i].in_use = true;
            tasks[i].name = name;
            xTaskCreate(function, name.c_str(), 100, NULL, priority, &tasks[i].handle);
            return i;
        }
    }
    return -1;
}

void multitasking_cleanup() {
    for(int i = 0; i < MAXIMUM_PROCESS_COUNT; i++) {
        if(tasks[i].in_use) {
            if(eTaskGetState(tasks[i].handle) == eDeleted) {
                tasks[i].in_use = false;
            }
        }
    }
}

void multitasking_init() {
    //vTaskStartScheduler();
}
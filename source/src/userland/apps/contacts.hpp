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

contact_t create_contact() {
    debug("Creating new contact\n");
    debug("TODO: this\n");
    contact_t new_contact;
    new_contact.name = "Test Contact";
    new_contact.number = "18002672001";
    return new_contact;
}

int contact_search() {
    debug("Contact picker started\n");
    std::vector<String> contact_names;
    
    contact_names.push_back(STRING_NEW);
    for(int i = contacts.size() - 1; i >= 0; i--) {
        contact_names.push_back(contacts.at(i).name);
    }
    debug("Populated contact name list\n");
    int chosen = gui_list(STRING_CONTACTS, contact_names);
    if(chosen == 0) {
        debug("Picking new contact\n");
        contact_t new_contact = create_contact();
        contacts.push_back(new_contact);
        chosen = contacts.size() - 1;
    } else chosen --;

    return chosen;
}

void load_contacts() {
    debug("Loading contacts...\n");
    debug("TODO: this\n");
}

void start_contacts() {
    debug("Running contacts app\n");
    int chosen = contact_search();
    if(chosen == -1) return;
    
    for(;;) {
        display_clear();
        display_draw_string(0, 0, (char*) contacts.at(chosen).name.c_str(), 1);
        display_draw_string(0, 8, (char*) contacts.at(chosen).number.c_str(), 1);
        
        char key = keypad_wait_key();
        if(key == KEY_CANCEL) return;
    }
}

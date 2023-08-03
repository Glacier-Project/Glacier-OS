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
    
    for(int i = contacts.size() - 1; i >= 0; i--) {
        contact_names.push_back(contacts.at(i).name);
    }
    debug("Populated contact name list\n");
    int chosen = gui_list(STRING_CONTACTS, contact_names);
    if(chosen == -1) {
        contact_t new_contact = create_contact();
        contacts.push_back(new_contact);
        chosen = contacts.size() - 1;
    }

    return chosen;
}

void load_contacts() {
    debug("Loading contacts...");
    debug("TODO: this");
}

void start_contacts() {
    
}

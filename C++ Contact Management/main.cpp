#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

void saveContactsToFile(const vector<Contact>& contacts) {
    ofstream outFile("contacts.txt");
    for (const auto& contact : contacts) {
        outFile << contact.name << "," << contact.phone << "," << contact.email << "\n";
    }
}

vector<Contact> loadContactsFromFile() {
    vector<Contact> contacts;
    ifstream inFile("contacts.txt");
    string line;

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');

        if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
            Contact contact;
            contact.name = line.substr(0, pos1);
            contact.phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            contact.email = line.substr(pos2 + 1);
            contacts.push_back(contact);
        }
    }

    return contacts;
}

void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter name: ";
    getline(cin >> ws, newContact.name);
    cout << "Enter phone: ";
    getline(cin, newContact.phone);
    cout << "Enter email: ";
    getline(cin, newContact.email);

    contacts.push_back(newContact);
    saveContactsToFile(contacts);
    cout << "Contact added successfully.\n";
}

void displayContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts to display.\n";
        return;
    }

    cout << "\n--- Contact List ---\n";
    for (const auto& contact : contacts) {
        cout << "Name: " << contact.name << "\n";
        cout << "Phone: " << contact.phone << "\n";
        cout << "Email: " << contact.email << "\n";
        cout << "---------------------\n";
    }
}

void searchContact(const vector<Contact>& contacts) {
    string searchName;
    cout << "Enter name to search: ";
    getline(cin >> ws, searchName);

    bool found = false;
    for (const auto& contact : contacts) {
        if (contact.name == searchName) {
            cout << "\nContact Found:\n";
            cout << "Name: " << contact.name << "\n";
            cout << "Phone: " << contact.phone << "\n";
            cout << "Email: " << contact.email << "\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Contact not found.\n";
}

void deleteContact(vector<Contact>& contacts) {
    string nameToDelete;
    cout << "Enter name to delete: ";
    getline(cin >> ws, nameToDelete);

    auto it = remove_if(contacts.begin(), contacts.end(), [&](const Contact& c) {
        return c.name == nameToDelete;
    });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        saveContactsToFile(contacts);
        cout << "Contact deleted successfully.\n";
    } else {
        cout << "Contact not found.\n";
    }
}

int main() {
    vector<Contact> contacts = loadContactsFromFile();
    int choice;

    do {
        cout << "\n--- Contact Management System ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addContact(contacts); break;
            case 2: displayContacts(contacts); break;
            case 3: searchContact(contacts); break;
            case 4: deleteContact(contacts); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 0);

    return 0;
}

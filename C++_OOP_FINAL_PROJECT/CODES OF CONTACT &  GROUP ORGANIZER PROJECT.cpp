#include <iostream>
#include <cstring>
using namespace std;

struct Contact {
    char name[30];
    char phone[15];
};

class ContactBase {
public:
    virtual void display() = 0;
    virtual const char* getName() = 0;
    virtual ~ContactBase() {}
};

class FriendContact : public ContactBase {
    Contact data;
public:
    FriendContact(const char* n, const char* p) {
        strcpy(data.name, n);
        strcpy(data.phone, p);
    }
    void display() override {
        cout << "[Friend] " << data.name << " - " << data.phone << endl;
    }
    const char* getName() override {
        return data.name;
    }
};

class WorkContact : public ContactBase {
    Contact data;
public:
    WorkContact(const char* n, const char* p) {
        strcpy(data.name, n);
        strcpy(data.phone, p);
    }
    void display() override {
        cout << "[Work] " << data.name << " - " << data.phone << endl;
    }
    const char* getName() override {
        return data.name;
    }
};

struct Group {
    char name[20];
    ContactBase** members;
    int memberCount;

    Group(const char* groupName) {
        strcpy(name, groupName);
        members = nullptr;
        memberCount = 0;
    }

    void addMember(ContactBase* contact) {
        ContactBase** temp = new ContactBase*[memberCount + 1];
        for (int i = 0; i < memberCount; i++)
            temp[i] = members[i];
        temp[memberCount] = contact;
        delete[] members;
        members = temp;
        memberCount++;
    }

    void removeMember(const char* contactName) {
        int index = -1;
        for (int i = 0; i < memberCount; i++) {
            if (strcmp(members[i]->getName(), contactName) == 0) {
                index = i;
                break;
            }
        }
        if (index == -1) return;

        ContactBase** temp = new ContactBase*[memberCount - 1];
        for (int i = 0, j = 0; i < memberCount; i++) {
            if (i != index)
                temp[j++] = members[i];
        }
        delete[] members;
        members = temp;
        memberCount--;
    }

    void displayGroup() {
        cout << "\nGroup: " << name << "\n";
        for (int i = 0; i < memberCount; i++)
            members[i]->display();
    }

    ~Group() {
        delete[] members;
    }
};

struct GroupManager {
    Group** groups;
    int groupCount;

    GroupManager() {
        groups = nullptr;
        groupCount = 0;
    }

    void addGroup(const char* groupName) {
        Group** temp = new Group*[groupCount + 1];
        for (int i = 0; i < groupCount; i++)
            temp[i] = groups[i];
        temp[groupCount] = new Group(groupName);
        delete[] groups;
        groups = temp;
        groupCount++;
    }

    void removeGroup(const char* groupName) {
        int index = -1;
        for (int i = 0; i < groupCount; i++) {
            if (strcmp(groups[i]->name, groupName) == 0) {
                index = i;
                break;
            }
        }
        if (index == -1) return;

        delete groups[index];
        Group** temp = new Group*[groupCount - 1];
        for (int i = 0, j = 0; i < groupCount; i++) {
            if (i != index)
                temp[j++] = groups[i];
        }
        delete[] groups;
        groups = temp;
        groupCount--;
    }

    Group* findGroup(const char* name) {
        for (int i = 0; i < groupCount; i++) {
            if (strcmp(groups[i]->name, name) == 0)
                return groups[i];
        }
        return nullptr;
    }

    void displayAllGroups() {
        for (int i = 0; i < groupCount; i++)
            groups[i]->displayGroup();
    }

    ~GroupManager() {
        for (int i = 0; i < groupCount; i++)
            delete groups[i];
        delete[] groups;
    }
};

int main() {
    ContactBase** contacts = nullptr;
    int contactCount = 0;
    GroupManager gm;

    char name[30], phone[15], groupName[20];
    int type;
    char choice;

    // Add contacts
    do {
        cout << "\n--- Add Contact  ---\n";
        cout << "Enter name: ";
        cin.getline(name, 30);
        cout << "Enter phone: ";
        cin.getline(phone, 15);
        cout << "Type (1-Friend, 2-Work): ";
        cin >> type;
        cin.ignore();

        ContactBase** temp = new ContactBase*[contactCount + 1];
        for (int i = 0; i < contactCount; i++)
            temp[i] = contacts[i];

        if (type == 1)
            temp[contactCount] = new FriendContact(name, phone);
        else
            temp[contactCount] = new WorkContact(name, phone);

        delete[] contacts;
        contacts = temp;
        contactCount++;

        cout << "Add another contact? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');

    // Show all contacts
    cout << "\nAll Contacts:\n";
    for (int i = 0; i < contactCount; i++)
        contacts[i]->display();

    // Create groups
    cout << "\n--- Create Groups ---\n";
    do {
        cout << "Enter group name: ";
        cin.getline(groupName, 20);
        gm.addGroup(groupName);

        cout << "Add another group? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');

    // Assign contacts to groups
    cout << "\n--- Assign Contacts to Groups ---\n";
    do {
        cout << "Enter group name: ";
        cin.getline(groupName, 20);
        Group* g = gm.findGroup(groupName);
        if (!g) {
            cout << "Group not found!\n";
            continue;
        }

        cout << "Enter contact name to add: ";
        cin.getline(name, 30);
        bool found = false;
        for (int i = 0; i < contactCount; i++) {
            if (strcmp(contacts[i]->getName(), name) == 0) {
                g->addMember(contacts[i]);
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Contact not found.\n";

        cout << "Add another member? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');

    // Remove group or member menu
    do {
        cout << "\n--- Remove Options ---\n";
        cout << "1. Remove Group\n";
        cout << "2. Remove Member from Group\n";
        cout << "3. Display All Groups\n";
        cout << "4. Exit Remove Menu\n";
        cout << "Enter your choice: ";
        int removeOption;
        cin >> removeOption;
        cin.ignore();

        if (removeOption == 1) {
            cout << "Enter group name to remove: ";
            cin.getline(groupName, 20);
            gm.removeGroup(groupName);
            cout << "Group removed!\n";
            
        } else if (removeOption == 2) {
            cout << "Enter group name: ";
            cin.getline(groupName, 20);
            Group* g = gm.findGroup(groupName);
            if (!g) {
                cout << "Group not found.\n";
                continue;
            }
            cout << "Enter contact name to remove from group: ";
            cin.getline(name, 30);
            g->removeMember(name);
            cout << "Member removed if found.\n";
        } else if (removeOption == 3) {
            gm.displayAllGroups();
        } else if (removeOption == 4) {
            break;
        } else {
            cout << "Invalid option.\n";
        }

        cout << "Do want to proceed with remove/display operation? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');

    // Final group display
    cout << "\n--- Final Group Details ---\n";
    gm.displayAllGroups();

    // Cleanup
    for (int i = 0; i < contactCount; i++)
        delete contacts[i];
    delete[] contacts;

    return 0;
}





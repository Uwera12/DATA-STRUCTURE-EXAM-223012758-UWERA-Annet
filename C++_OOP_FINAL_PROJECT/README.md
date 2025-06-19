PROJECT: CONTACT & GROUP ORGANIZER README.


The Contact & Group Organizer project is a C++ application created to manage personal and professional contacts and organize them into dynamically created groups. The program allows users to create, store, display, and manage two types of contacts Friends and Work colleagues and assign them into custom groups. It implements object-oriented programming principles including inheritance, abstraction, polymorphism, and dynamic memory allocation using raw pointers.

This project meets all requirements stated in the assignment by showcasing the use of abstract classes, dynamic arrays of objects, and pointer arithmetic to manipulate memory structures manually.

Objectives and Implementation

1. Struct Definition for Contact Data

At the core of the program is a simple Contact structure. It stores a person's name and phone number using character arrays. This struct is used inside the derived contact classes to represent the basic identity of any contact.

#include <iostream> // Used for input and output operations 
#include <cstring> // Used for string manipulation functions (like strcpy,
strcmp)
using namespace std; // Makes it easier to use standard C++ elements like cout and cin without writing std::
struct Contact {
 char name[30]; // A fixed-size space to store the contact's name (up to 29 characters + null terminator)
 char phone[15]; // A fixed-size space to store the contact's phone number (up to 14 characters + null terminator)
};

2. Abstract Base Class: ContactBase
   
An abstract class named ContactBase is used to define a common interface for all contact types. It includes pure virtual functions for displaying contact information and retrieving a contact's name. These virtual functions enforce that any derived class must implement its own version of these behaviors. A virtual destructor is also included to support proper cleanup of dynamically allocated contact objects through base-class pointers. 

class ContactBase {
public:
 virtual void display() = 0; // A "pure virtual" function: every derived class have to implement its own display
 virtual const char* getName() = 0; // A "pure virtual" function: every derived class MUST implement its own getName
 virtual ~ContactBase() {} // A virtual destructor: important for correct memory cleanup with polymorphic objects
};


3. FriendContact and WorkContact: Demonstrating Inheritance and Polymorphism
   
The program defines two specialized classes that inherit from the abstract base class: FriendContact and WorkContact. These classes each store the contact’s details and override the display and name-access functions to handle their specific formatting and behavior. This demonstrates inheritance and polymorphism, where a base class pointer can point to an object of a derived class, and the correct method is called at runtime depending on the object type.

For instance, calling the display() function on a ContactBase pointer will dynamically call either the friend’s or the work contact’s version of that function based on the actual object type.

class FriendContact : public ContactBase {
 Contact data; // Contains the basic name and phone number
public:
 FriendContact(const char* n, const char* p) { // Constructor: called when you create a new FriendContact
 strcpy(data.name, n); // Copies the provided name 'n' into data.name
 strcpy(data.phone, p); // Copies the provided phone 'p' into data.phone
 }
 void display() override { // Implementation of the display function for FriendContact
 cout << "[Friend] " << data.name << " - " << data.phone << endl;
 }
 const char* getName() override { return data.name; } // Implementation of getName for FriendContact
};
class WorkContact : public ContactBase {
 Contact data; // Contains the basic name and phone number
public:
 WorkContact(const char* n, const char* p) { // Constructor: called when you create a new WorkContact
 strcpy(data.name, n);
 strcpy(data.phone, p);
 }
 void display() override { // Implementation of the display function for WorkContact
 cout << "[Work] " << data.name << " - " << data.phone << endl;
 }
 const char* getName() override { return data.name; } // Implementation of getName for WorkContact
};

4. Managing a Dynamic Contact List
   
Contacts are stored in a dynamically resizable array of base-class pointers. This means every time a contact is added, a new array is created with one additional slot, the previous elements are copied, and memory is reallocated. The old array is deleted to avoid memory leaks. This approach provides flexibility to grow the contact list based on user input during runtime.

ContactBase** contacts = nullptr;
int contactCount = 0;

// Adding a contact
ContactBase** temp = new ContactBase*[contactCount + 1];
for (int i = 0; i < contactCount; i++)
    temp[i] = contacts[i];
temp[contactCount] = new FriendContact(name, phone); // or WorkContact

delete[] contacts;
contacts = temp;
contactCount++;

5. Group Structure for Contact Organization
   
Each group in the program is represented by a structure that stores:
A name for the group
A dynamic array of contact pointers (i.e., group members)
The number of contacts in the group

This design supports the creation of user-defined groups, such as "Family", "Colleagues", or "Team A", and allows assigning multiple contacts to a single group. A user can add contacts to a group, display all members of a group, or remove specific members.

struct Group {
 char name[20]; // Name of the group (e.g., "Family", "Co-workers")
 ContactBase** members; // A dynamic array of pointers to ContactBase objects (can hold Friends or Work contacts)
 int memberCount; // How many contacts are currently in this group
 Group(const char* groupName) { // Constructor for Group
 strcpy(name, groupName);
 members = nullptr; // Initialize members to null (no members yet)
 memberCount = 0; // No members yet
 }
 void addMember(ContactBase* contact) { // Dynamically resize the members array to add a new contact
 ContactBase** temp = new ContactBase*[memberCount + 1]; // Create a new array, one size larger
 for (int i = 0; i < memberCount; i++)
 temp[i] = members[i]; // Copy existing members to the new array
 temp[memberCount] = contact; // Add the new contact at the end
 delete[] members; // Delete the old (smaller) array
 members = temp; // Point 'members' to the new (larger) array
 memberCount++; // Increment the count of members
 }
 void removeMember(const char* contactName) {
 int index = -1; // To store the index of the contact to remove
 for (int i = 0; i < memberCount; i++) {
 if (strcmp(members[i]->getName(), contactName) == 0) { // Compare names to find whether they are matching
 index = i; // Found the contact, store its index
 break;
 }
 }
 if (index == -1) return; // If contact not found, do nothing
 // Dynamically resize the members array to remove a contact
 
 ContactBase** temp = new ContactBase*[memberCount - 1]; // Create a new array, one size smaller
 for (int i = 0, j = 0; i < memberCount; i++) { // Loop through old members
 if (i != index) // If it's not the one we're removing
 temp[j++] = members[i]; // Copy it to the new array
 }
 delete[] members; // Delete the old array
 members = temp; // Point 'members' to the new array
 memberCount--; // Decrement the count
 }
 void displayGroup() {
 cout << "\nGroup: " << name << "\n"; // Print group name
 for (int i = 0; i < memberCount; i++)
 members[i]->display(); // Call display() for each member (polymorphically)
 }
 ~Group() { // Destructor for Group: called when a Group object is destroyed
 delete[] members; // Frees the memory allocated for the members array
 }
};

6. Dynamic Group Creation and Management
   
The program uses a manager structure to handle an array of groups. Like the contact list, this group array is also dynamically resizable. Users can create as many groups as they want, and each group can independently maintain its own contact members. The program also supports removing entire groups by name. When a group is removed, its memory is cleaned up to prevent resource leaks.

struct GroupManager {
 Group** groups; // A dynamic array of pointers to Group objects
 int groupCount; // How many groups are currently managed
 GroupManager() { // Constructor for GroupManager
 groups = nullptr; // Initialize to no groups
 groupCount = 0;
 }
 void addGroup(const char* groupName) { // Dynamically resize the groups array
 Group** temp = new Group*[groupCount + 1]; // Create a new array, one size larger
 for (int i = 0; i < groupCount; i++)
 temp[i] = groups[i]; // Copy existing group pointers
 temp[groupCount] = new Group(groupName); // Create a NEW Group object and add its pointer
 delete[] groups; // Delete the old array
 groups = temp; // Point to the new array
 groupCount++; // Increment count
 }
 void removeGroup(const char* groupName) {
 int index = -1;
 for (int i = 0; i < groupCount; i++) {
 if (strcmp(groups[i]->name, groupName) == 0) { // Find group by name
 index = i;
 break;
 }
 }
 if (index == -1) return;
 delete groups[index]; // IMPORTANT: Delete the actual Group object first
 Group** temp = new Group*[groupCount - 1]; // Create a new array, one size smaller
 for (int i = 0, j = 0; i < groupCount; i++) {
 if (i != index)
 temp[j++] = groups[i]; // Copy other group pointers
 }
 delete[] groups; // Delete the old array
 groups = temp; // Point to the new array
 groupCount--; // Decrement count
 }
 Group* findGroup(const char* name) {
 for (int i = 0; i < groupCount; i++) {
 if (strcmp(groups[i]->name, name) == 0)
 return groups[i]; // Return pointer to the found group
 }
 return nullptr; // Group not found
 }
 void displayAllGroups() {
 for (int i = 0; i < groupCount; i++)
 groups[i]->displayGroup(); // Call displayGroup for each group
 }
 ~GroupManager() { // Destructor for GroupManager
 for (int i = 0; i < groupCount; i++)
 delete groups[i]; // IMPORTANT: Delete each Group object held by the manager
 delete[] groups; // Delete the array of group pointers
 }
};

7. User Interaction
The program operates via console-based interaction. Users are prompted to:

Enter contact information and specify whether the contact is a friend or a work colleague.

Create and name groups.

Assign contacts to specific groups.

Display all created groups and their members.

Remove a group or remove a specific member from a group.

At the end of the program, all dynamically allocated memory is properly deleted to ensure the application runs efficiently and safely.

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



Key Object-Oriented Concepts Demonstrated
Abstraction: Through the use of a base abstract class for contacts.

Inheritance: Friend and Work contact types inherit from the abstract base.

Polymorphism: Display and access methods are resolved at runtime via virtual functions.

Encapsulation: Contact and group details are managed within their respective classes.

Dynamic Memory Management: Arrays are manually resized using raw pointers and deleted after use.

Sample Functionalities in Action

Create Contact: The user enters name, phone number, and type (Friend or Work).
Create Group: The user assigns a name to a new group (e.g., "Family").
Assign Contact to Group: The user links existing contacts to specific groups.

Display Group Members: All members of a group are displayed using polymorphic behavior.

Remove Group or Member: The user can delete either an entire group or specific members from a group.

 Memory Management
All dynamic arrays (for contacts, groups, and group members) are handled manually using new and delete[]. Proper memory cleanup is included in destructors to avoid memory leaks, ensuring the program remains safe and efficient even after repeated user operations.

This Contact & Group Organizer project fulfills all the functional and technical requirements of the assignment. It efficiently demonstrates the use of C++ features such as abstract classes, inheritance, polymorphism, and dynamic memory allocation. It offers practical experience in handling dynamic data structures and lays a strong foundation for object-oriented programming using C++.













































































































































































































































































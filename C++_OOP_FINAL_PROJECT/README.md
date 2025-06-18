PROJECT: CONTACT & GROUP ORGANIZER README.


The Contact & Group Organizer project is a C++ application designed to manage personal and professional contacts and organize them into dynamically created groups. The program allows users to create, store, display, and manage two types of contacts Friends and Work colleagues and assign them into custom groups. It implements object-oriented programming principles including inheritance, abstraction, polymorphism, and dynamic memory allocation using raw pointers.

This project meets all requirements stated in the assignment by showcasing the use of abstract classes, dynamic arrays of objects, and pointer arithmetic to manipulate memory structures manually.

Objectives and Implementation

1. Struct Definition for Contact Data
At the core of the program is a simple Contact structure. It stores a person's name and phone number using character arrays. This struct is used inside the derived contact classes to represent the basic identity of any contact.

2. Abstract Base Class: ContactBase
An abstract class named ContactBase is used to define a common interface for all contact types. It includes pure virtual functions for displaying contact information and retrieving a contact's name. These virtual functions enforce that any derived class must implement its own version of these behaviors. A virtual destructor is also included to support proper cleanup of dynamically allocated contact objects through base-class pointers.

3. FriendContact and WorkContact: Demonstrating Inheritance and Polymorphism
The program defines two specialized classes that inherit from the abstract base class: FriendContact and WorkContact. These classes each store the contact’s details and override the display and name-access functions to handle their specific formatting and behavior. This demonstrates inheritance and polymorphism, where a base class pointer can point to an object of a derived class, and the correct method is called at runtime depending on the object type.

For instance, calling the display() function on a ContactBase pointer will dynamically call either the friend’s or the work contact’s version of that function based on the actual object type.

4. Managing a Dynamic Contact List
Contacts are stored in a dynamically resizable array of base-class pointers. This means every time a contact is added, a new array is created with one additional slot, the previous elements are copied, and memory is reallocated. The old array is deleted to avoid memory leaks. This approach provides flexibility to grow the contact list based on user input during runtime.

5. Group Structure for Contact Organization
Each group in the program is represented by a structure that stores:

A name for the group

A dynamic array of contact pointers (i.e., group members)

The number of contacts in the group

This design supports the creation of user-defined groups, such as "Family", "Colleagues", or "Team A", and allows assigning multiple contacts to a single group. A user can add contacts to a group, display all members of a group, or remove specific members.

6. Dynamic Group Creation and Management
The program uses a manager structure to handle an array of groups. Like the contact list, this group array is also dynamically resizable. Users can create as many groups as they want, and each group can independently maintain its own contact members. The program also supports removing entire groups by name. When a group is removed, its memory is cleaned up to prevent resource leaks.

7. User Interaction
The program operates via console-based interaction. Users are prompted to:

Enter contact information and specify whether the contact is a friend or a work colleague.

Create and name groups.

Assign contacts to specific groups.

Display all created groups and their members.

Remove a group or remove a specific member from a group.

At the end of the program, all dynamically allocated memory is properly deleted to ensure the application runs efficiently and safely.

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

 void display() override { ... }: This is the specific implementation of the
display() function that FriendContact must provide because of ContactBase. The
override keyword is a good practice to show that you are intentionally overriding a
virtual function from the base class. Here, it prints "[Friend]" before the name and phone.
 const char* getName() override { return data.name; }: This is the specific
implementation of getName() for FriendContact.
 WorkContact: Works exactly like FriendContact, but its display() function prints
"[Work]" instead. This demonstrates polymorphism: the same display() call will
behave differently depending on whether the object is a FriendContact or a
WorkContact.
Step 4: Structuring a Group of Contacts
C++
// ========== STEP 4: Group Struct ==========
struct Group {
 char name[20]; // Name of the group (e.g., "Family", "Co-workers")
 ContactBase** members; // A dynamic array of pointers to ContactBase
objects (can hold Friends or Work contacts)
 int memberCount; // How many contacts are currently in this group
 Group(const char* groupName) { // Constructor for Group
 strcpy(name, groupName);
 members = nullptr; // Initialize members to null (no members yet)
 memberCount = 0; // No members yet
 }
 void addMember(ContactBase* contact) {
 // Dynamically resize the members array to add a new contact
 ContactBase** temp = new ContactBase*[memberCount + 1]; // Create a
new array, one size larger
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
 if (strcmp(members[i]->getName(), contactName) == 0) { // Compare
names
 index = i; // Found the contact, store its index
 break;
 }
 }
 if (index == -1) return; // If contact not found, do nothing
 // Dynamically resize the members array to remove a contact
 ContactBase** temp = new ContactBase*[memberCount - 1]; // Create a
new array, one size smaller
 for (int i = 0, j = 0; i < memberCount; i++) { // Loop through old
members
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
 members[i]->display(); // Call display() for each member
(polymorphically)
 }
 ~Group() { // Destructor for Group: called when a Group object is
destroyed
 delete[] members; // Frees the memory allocated for the members array
 }
};
 struct Group: This defines a blueprint for a group. Each group has a name, a list of
members, and a memberCount.
 ContactBase** members;: This is the core of how groups hold contacts. It's a pointer
to a pointer. This means it points to the beginning of an array, and each element in that
array is itself a pointer to a ContactBase object. This allows a group to hold any type of
ContactBase (Friend or Work) in the same list.
 Group(const char* groupName): The constructor for Group. It initializes the group's
name and sets members to nullptr (meaning it's empty) and memberCount to 0.
 void addMember(ContactBase* contact): This function adds a contact to the group. It
dynamically allocates a new, larger array, copies all the existing members into it, adds
the new member, then deletes the old array and updates the members pointer to the new
array. This is a common pattern for managing dynamic arrays (like std::vector does
for you automatically).
 void removeMember(const char* contactName): This function removes a contact by
name. It finds the contact, then creates a new, smaller array, copies all members except
the one to be removed, deletes the old array, and updates members.
 void displayGroup(): Prints the group's name and then calls display() on each
contact in the group. Because members holds ContactBase* pointers, this again
demonstrates polymorphism: the correct display() (Friend's or Work's) is called for
each contact.
 ~Group(): This is the destructor for Group. When a Group object is destroyed, this
function runs. It's crucial for freeing the dynamically allocated memory for the
members array (delete[] members;) to prevent memory leaks. Note that it only deletes
the array of pointers, not the actual ContactBase objects themselves, as those are
managed by main's contacts array.
Step 5: Managing All Your Groups
C++
// ========== STEP 5: Group Manager ==========
struct GroupManager {
 Group** groups; // A dynamic array of pointers to Group objects
 int groupCount; // How many groups are currently managed
 GroupManager() { // Constructor for GroupManager
 groups = nullptr; // Initialize to no groups
 groupCount = 0;
 }
 void addGroup(const char* groupName) {
 // Dynamically resize the groups array
 Group** temp = new Group*[groupCount + 1]; // Create a new array, one
size larger
 for (int i = 0; i < groupCount; i++)
 temp[i] = groups[i]; // Copy existing group pointers
 temp[groupCount] = new Group(groupName); // Create a NEW Group object
and add its pointer
 delete[] groups; // Delete the old array
 groups = temp; // Point to the new array
 groupCount++; // Increment count
 }
 void removeGroup(const char* groupName) {
 int index = -1;
 for (int i = 0; i < groupCount; i++) {
 if (strcmp(groups[i]->name, groupName) == 0) { // Find group by
name
 index = i;
 break;
 }
 }
 if (index == -1) return;
 delete groups[index]; // IMPORTANT: Delete the actual Group object
first
 Group** temp = new Group*[groupCount - 1]; // Create a new array, one
size smaller
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
 delete groups[i]; // IMPORTANT: Delete each Group object held by
the manager
 delete[] groups; // Delete the array of group pointers
 }
};
 struct GroupManager: This acts as a central organizer for all your groups. It holds a
dynamic array of Group* (pointers to Group objects).
 GroupManager(): The constructor initializes groups to nullptr and groupCount to 0.
 void addGroup(const char* groupName): This function is very similar to
Group::addMember. It creates a new Group object with the given name, dynamically
resizes the groups array to include this new group, copies existing groups, and updates
the pointer.
 void removeGroup(const char* groupName): Removes a group by its name. It finds
the group, deletes the actual Group object (which in turn calls the Group's destructor to
free its members array), then resizes and updates the groups array.
 Group* findGroup(const char* name): This utility function helps you find a specific
group by its name. It returns a pointer to the Group if found, or nullptr if not.
 void displayAllGroups(): Loops through all managed groups and calls
displayGroup() on each one.
 ~GroupManager(): The destructor for GroupManager. This is absolutely critical! When
the GroupManager object is destroyed (at the end of the main function), it loops through
all the Group objects it created and deletes them one by one. Finally, it deletes the array
(groups) itself. This prevents memory leaks.
Step 6: The Main Program Logic
C++
// ========== STEP 6: Main Function ==========
int main() {
 ContactBase** contacts = nullptr; // A dynamic array to hold ALL contacts
(Friend or Work)
 int contactCount = 0; // Number of contacts currently stored
 GroupManager gm; // Create an instance of our
GroupManager
 char name[30], phone[15], groupName[20]; // Temporary buffers for user
input
 int type; // For contact type (1 for
Friend, 2 for Work)
 char choice; // For user's 'y/n' choice
 do {
 cout << "\n--- Add New Contact ---\n";
 cout << "Enter name: ";
 cin.ignore(); // Clears any leftover newline characters in the input
buffer
 cin.getline(name, 30); // Reads a line of text (including spaces) for
the name
 cout << "Enter phone: ";
 cin.getline(phone, 15); // Reads a line of text for the phone
 cout << "Type (1-Friend, 2-Work): ";
 cin >> type; // Reads a single integer for the type
 // Dynamically resize the contacts array to add a new contact
 ContactBase** temp = new ContactBase*[contactCount + 1];
 for (int i = 0; i < contactCount; i++)
 temp[i] = contacts[i];
 if (type == 1)
 temp[contactCount] = new FriendContact(name, phone); // Create a
new FriendContact
 else
 temp[contactCount] = new WorkContact(name, phone); // Create a
new WorkContact
 delete[] contacts; // Delete the old contacts array
 contacts = temp; // Update to the new array
 contactCount++; // Increment total contact count
 cout << "Add another contact? (y/n): ";
 cin >> choice;
 } while (choice == 'y' || choice == 'Y'); // Loop as long as the user
wants to add contacts
 cout << "\nAll Contacts:\n";
 for (int i = 0; i < contactCount; i++)
 contacts[i]->display(); // Display each contact (polymorphic call!)
 // Add groups
 cout << "\n--- Create Groups ---\n";
 do {
 cout << "Enter group name: ";
 cin.ignore();
 cin.getline(groupName, 20);
 gm.addGroup(groupName); // Call the addGroup function from
GroupManager
 cout << "Add another group? (y/n): ";
 cin >> choice;
 } while (choice == 'y' || choice == 'Y');
 // Assign members to groups
 cout << "\n--- Assign Contacts to Groups ---\n";
 do {
 cout << "Enter group name: ";
 cin.ignore();
 cin.getline(groupName, 20);
 Group* g = gm.findGroup(groupName); // Find the group by name
 if (!g) { // If group not found
 cout << "Group not found!\n";
 continue; // Skip to the next iteration
 }
 cout << "Enter contact name to add: ";
 cin.getline(name, 30);
 bool found = false;
 for (int i = 0; i < contactCount; i++) {
 if (strcmp(contacts[i]->getName(), name) == 0) { // Find the
contact by name
 g->addMember(contacts[i]); // Add the contact to the found
group
 found = true;
 break;
 }
 }
 if (!found)
 cout << "Contact not found.\n";
 cout << "Add another member? (y/n): ";
 cin >> choice;
 } while (choice == 'y' || choice == 'Y');
 // Display groups
 cout << "\n--- Group Details ---\n";
 gm.displayAllGroups(); // Display all groups and their members
 // Cleanup (VERY IMPORTANT!)
 for (int i = 0; i < contactCount; i++)
 delete contacts[i]; // Delete each individual
FriendContact/WorkContact object
 delete[] contacts; // Delete the array of ContactBase pointers itself
 // The gm (GroupManager) object will automatically call its destructor
(~GroupManager())
 // at the end of main, which will clean up all the Group objects it
manages.
 return 0; // Indicates the program finished successfully
}
 int main(): This is the starting point of every C++ program.
 ContactBase** contacts = nullptr;: This declares a pointer to a pointer, which will
be used as our dynamic array to store all contacts (both Friend and Work).
 GroupManager gm;: Creates an object named gm of type GroupManager. This object will
handle all the groups.
 Input Loops (do-while): The program uses do-while loops to repeatedly ask the user to
add contacts, create groups, and assign contacts to groups until the user types 'n' or 'N'.
o cin.ignore(): This is often needed after cin >> variable; when followed by
cin.getline();. It clears the leftover newline character from the input buffer.
o cin.getline(variable, size);: Reads an entire line of text (including spaces)
from the user's input until they press Enter.
 Adding Contacts:
o It prompts the user for name, phone, and contact type.
o It dynamically creates a new FriendContact or WorkContact object using new.
o It then reallocates the contacts array (ContactBase** temp = new
ContactBase*[contactCount + 1];), copies existing contacts, adds the new
contact, deletes the old array, and updates contacts to point to the new one.
 Displaying All Contacts: It iterates through the contacts array and calls contacts[i]-
>display(). This is where polymorphism shines: depending on whether contacts[i]
points to a FriendContact or a WorkContact, the correct display() function is called.
 Creating Groups: It uses gm.addGroup(groupName); to create new groups through the
GroupManager.
 Assigning Contacts to Groups:
o It prompts for a group name and uses gm.findGroup(groupName) to locate the
specific Group object.
o It then prompts for a contact name, searches through the contacts array to find
that contact, and if found, calls g->addMember(contacts[i]); to add the contact
to the chosen group.
 Displaying Group Details: It uses gm.displayAllGroups(); to show the contents of all
created groups.
 Cleanup (delete operations): This is arguably the most crucial part for memory
management.
o for (int i = 0; i < contactCount; i++) delete contacts[i];: This
loop goes through each individual FriendContact or WorkContact object that
was created with new and deletes them. This calls their destructors.
o delete[] contacts;: After deleting the individual objects, this line deletes the
array itself that held all the ContactBase* pointers.
o gm destructor: When main finishes, the gm object goes out of scope, and its
destructor (~GroupManager()) is automatically called. As we saw, this destructor
is responsible for deleting all the Group objects that gm managed, which in turn
calls each Group's destructor (~Group()) to clean up its members array.

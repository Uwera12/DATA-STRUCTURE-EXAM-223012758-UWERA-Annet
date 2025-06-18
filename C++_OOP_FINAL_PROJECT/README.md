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













































































































































































































































































#include <iostream>
#include <vector>
using namespace std;

class Employee {
protected:
    string name, role;
    int salary, bonus, tax;
public:
    Employee(string n, int s, string r, int b,int t) : name(n), salary(s), role(r), bonus(b),tax(t) {}

    string getName() { return name; }
    string getRole() { return role; }
    int getSalary() { return salary; }
    int getBonus() { return bonus; }
    int getTax(){ return tax; }
	
};

class Manager : public Employee {
public:
    Manager(string n, int s, int b, int t) : Employee(n, s, "Manager", b,t) {}
};

class Developer : public Employee {
public:
    Developer(string n, int s, int b, int t) : Employee(n, s, "Developer", b,t) {}
};

class Intern : public Employee {
public:
    Intern(string n, int s, int b, int t) : Employee(n, s, "Intern", b,t) {}
};

class SeniorManager : public Manager {
public:
    SeniorManager(string n, int s, int b, int t) : Manager(n, s, b,t) {
        role = "Senior Manager"; 
    }
};

class PayrollSystem {
    vector<Employee> employees;
    
public:
    void addEmployee(Employee e) {
        employees.push_back(e);
    }

    void computeSalaries() {
        cout << "\n------ Payroll Summary ------\n";
        if (employees.empty()) {
            cout << "No employees registered!\n";
            return;
        }

        for (auto &e : employees) {
            int netPay = e.getSalary() + e.getBonus()-e.getTax();
            cout << "Employee: " << e.getName() << " | Role: " << e.getRole() << endl;
            cout << "Basic: $" << e.getSalary() << " | Bonus: $" << e.getBonus() << " | Net Pay: $" << netPay << "\n\n";
        }
    }

    void getUserInput() {
        int num;
        cout << "How many employees do you want to enter? ";
        cin >> num;

        for (int i = 0; i < num; i++) {
            string name, role;
            int salary, bonus, tax;

            cout << "\nEnter name of employee " << i + 1 << ": ";
            cin >> name;

            cout << "Enter salary: ";
            cin >> salary;

            cout << "Enter bonus amount: ";
            cin >> bonus;
            
            cout<< "Enter tax: ";
            cin>> tax;

            cout << "Select role (Manager, Developer, Intern, Senior Manager): ";
            cin >> role;

            if (role == "Manager") addEmployee(Manager(name, salary, bonus,tax));
            else if (role == "Developer") addEmployee(Developer(name, salary, bonus, tax));
            else if (role == "Intern") addEmployee(Intern(name, salary, bonus, tax));
            else if (role == "Senior Manager") addEmployee(SeniorManager(name, salary, bonus, tax));
            else cout << "Invalid role selection!\n";
        }
    }
};

// Main function
int main() {
    PayrollSystem payroll;

    payroll.getUserInput();  // Collecting employee details dynamically
    payroll.computeSalaries();  //  Display payroll summary

    return 0;
}

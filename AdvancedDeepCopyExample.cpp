#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

// Advanced Structure to demonstrate complex deep copying
struct Address {
    char* street;
    char* city;
    char* zipCode;

    // Constructor
    Address(const char* s = "", const char* c = "", const char* z = "") {
        street = new char[strlen(s) + 1];
        strcpy(street, s);
        
        city = new char[strlen(c) + 1];
        strcpy(city, c);
        
        zipCode = new char[strlen(z) + 1];
        strcpy(zipCode, z);
        
        cout << "  Address Constructor: Created address\n";
    }

    // Copy Constructor for nested object
    Address(const Address& other) {
        street = new char[strlen(other.street) + 1];
        strcpy(street, other.street);
        
        city = new char[strlen(other.city) + 1];
        strcpy(city, other.city);
        
        zipCode = new char[strlen(other.zipCode) + 1];
        strcpy(zipCode, other.zipCode);
        
        cout << "  Address Copy Constructor: Deep copied address\n";
    }

    // Destructor
    ~Address() {
        delete[] street;
        delete[] city;
        delete[] zipCode;
        cout << "  Address Destructor: Freed address memory\n";
    }

    void display() const {
        cout << "    " << street << ", " << city << " - " << zipCode << "\n";
    }
};

// Advanced Person class with multiple levels of nested objects
class Person {
private:
    char* name;
    int age;
    Address address;
    vector<double>* salaryHistory;  // Pointer to vector (must be deep copied)
    int* projects;                   // Pointer to array (must be deep copied)
    int projectCount;

public:
    // Constructor
    Person(const char* n, int a, const char* street, const char* city, const char* zip)
        : age(a), address(street, city, zip) {
        
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        
        salaryHistory = new vector<double>();
        projects = new int[10];
        projectCount = 0;
        
        cout << "Person Constructor: Created " << name << "\n";
    }

    // Deep Copy Constructor (Advanced)
    Person(const Person& other) 
        : age(other.age), address(other.address) {
        
        // Deep copy: name
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        cout << "Person Copy Constructor: Copying " << name << "\n";
        
        // Deep copy: salary history vector
        salaryHistory = new vector<double>();
        *salaryHistory = *other.salaryHistory;  // Copy vector contents
        cout << "  Copied salary history with " << salaryHistory->size() << " entries\n";
        
        // Deep copy: projects array
        projectCount = other.projectCount;
        projects = new int[10];
        for(int i = 0; i < projectCount; i++) {
            projects[i] = other.projects[i];
        }
        cout << "  Copied " << projectCount << " projects\n";
    }

    // Copy Assignment Operator (Advanced)
    Person& operator=(const Person& other) {
        if(this == &other) {
            cout << "Self-assignment detected. Skipping...\n";
            return *this;
        }
        
        cout << "Person Assignment Operator: Assigning " << other.name << " to " << name << "\n";
        
        // Delete old resources
        delete[] name;
        delete salaryHistory;
        delete[] projects;
        
        // Copy primitive and nested object
        age = other.age;
        address = other.address;  // Uses Address copy constructor
        
        // Deep copy: name
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        
        // Deep copy: salary history
        salaryHistory = new vector<double>();
        *salaryHistory = *other.salaryHistory;
        cout << "  Assigned salary history\n";
        
        // Deep copy: projects
        projectCount = other.projectCount;
        projects = new int[10];
        for(int i = 0; i < projectCount; i++) {
            projects[i] = other.projects[i];
        }
        cout << "  Assigned " << projectCount << " projects\n";
        
        return *this;
    }

    // Destructor
    ~Person() {
        cout << "Person Destructor: Deleting " << name << "\n";
        delete[] name;
        delete salaryHistory;
        delete[] projects;
    }

    // Add salary to history
    void addSalary(double salary) {
        salaryHistory->push_back(salary);
        cout << "Added salary: $" << salary << " (Total in history: " << salaryHistory->size() << ")\n";
    }

    // Add project ID
    void addProject(int projectID) {
        if(projectCount < 10) {
            projects[projectCount++] = projectID;
            cout << "Added project ID: " << projectID << "\n";
        }
    }

    // Update name
    void setName(const char* newName) {
        delete[] name;
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);
    }

    // Display all information
    void display() const {
        cout << "\n--- Person Details ---\n";
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Address: \n";
        address.display();
        
        cout << "Salary History: ";
        if(salaryHistory->empty()) {
            cout << "No history\n";
        } else {
            for(size_t i = 0; i < salaryHistory->size(); i++) {
                cout << "$" << (*salaryHistory)[i];
                if(i < salaryHistory->size() - 1) cout << ", ";
            }
            cout << "\n";
        }
        
        cout << "Projects: ";
        if(projectCount == 0) {
            cout << "No projects\n";
        } else {
            for(int i = 0; i < projectCount; i++) {
                cout << projects[i];
                if(i < projectCount - 1) cout << ", ";
            }
            cout << "\n";
        }
    }

    const char* getName() const { return name; }
};

// Advanced demonstration with nested classes
void demonstrateAdvancedDeepCopy() {
    cout << "========== ADVANCED DEEP COPY DEMONSTRATION ==========\n\n";

    // ========== SCENARIO 1: Copy Constructor with Nested Objects ==========
    cout << "--- SCENARIO 1: Copy Constructor with Nested Objects ---\n";
    Person person1("John Doe", 30, "123 Main St", "New York", "10001");
    person1.addSalary(50000);
    person1.addSalary(55000);
    person1.addProject(101);
    person1.addProject(102);
    person1.display();

    cout << "\n--- Creating person2 as copy of person1 ---\n";
    Person person2 = person1;  // Copy Constructor called
    person2.display();

    // ========== SCENARIO 2: Modify Copy and Check Independence ==========
    cout << "\n\n--- SCENARIO 2: Modifying person2 ---\n";
    person2.setName("Jane Smith");
    person2.addSalary(60000);
    person2.addProject(103);
    person2.display();

    cout << "\n--- person1 after person2 modifications (should be unchanged) ---\n";
    person1.display();

    // ========== SCENARIO 3: Assignment Operator ==========
    cout << "\n\n--- SCENARIO 3: Assignment Operator ---\n";
    Person person3("Bob Wilson", 25, "456 Oak Ave", "Boston", "02101");
    person3.addSalary(40000);
    person3.addProject(201);
    person3.display();

    cout << "\n--- Assigning person1 to person3 ---\n";
    person3 = person1;
    person3.display();

    cout << "\n--- Modifying person3 ---\n";
    person3.setName("Alice Wonder");
    person3.addSalary(75000);
    person3.addProject(999);
    person3.display();

    cout << "\n--- person1 after person3 modifications (should be unchanged) ---\n";
    person1.display();

    // ========== SCENARIO 4: Self-Assignment Protection ==========
    cout << "\n\n--- SCENARIO 4: Self-Assignment Protection ---\n";
    cout << "Executing: person1 = person1\n";
    person1 = person1;
    person1.display();

    // ========== SCENARIO 5: Chain Assignment ==========
    cout << "\n\n--- SCENARIO 5: Chain Assignment ---\n";
    Person person4("Default", 20, "789 Elm St", "Chicago", "60601");
    cout << "\nExecuting: person4 = person3 = person1\n";
    person4 = person3 = person1;
    person4.display();

    cout << "\n--- Modifying person4 ---\n";
    person4.setName("Charlie Brown");
    person4.addSalary(85000);
    person4.display();

    cout << "\n--- person1 and person3 should be unchanged ---\n";
    cout << "person1:\n";
    person1.display();
    cout << "\nperson3:\n";
    person3.display();

    cout << "\n\n========== DESTRUCTORS WILL BE CALLED (Reverse Order) ==========\n";
    cout << "Objects will be destroyed automatically:\n";
    cout << "person4 -> person3 -> person2 -> person1\n";
}

int main() {
    demonstrateAdvancedDeepCopy();
    
    cout << "\n========== PROGRAM ENDED ==========\n";
    return 0;
}

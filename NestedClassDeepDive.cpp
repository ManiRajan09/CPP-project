#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <typeinfo>

using namespace std;

// ============================================================================
// COMPREHENSIVE GUIDE TO NESTED CLASSES IN C++
// ============================================================================
// A nested class is a class defined within another class (outer class).
//
// Key Features:
// 1. Scope - The inner class name is scoped to outer class
// 2. Access Control - Can be public, private, or protected
// 3. Member Access - Can access outer class members (in some cases)
// 4. Naming - Referred to as OuterClass::InnerClass
// ============================================================================

cout << "\n" << string(70, '=') << "\n";
cout << "1. BASIC NESTED CLASS (Encapsulation)\n";
cout << string(70, '=') << "\n\n";

class University {
private:
    string universityName;

public:
    // NESTED CLASS - Defined inside University
    class Student {
    private:
        string name;
        int rollNumber;
        double gpa;

    public:
        Student(const string& n, int r, double g)
            : name(n), rollNumber(r), gpa(g) {
            cout << "✓ Student object created: " << name << "\n";
        }

        void display() const {
            cout << "  Student: " << name << " (Roll: " << rollNumber 
                 << ", GPA: " << fixed << gpa << ")\n";
        }

        string getName() const { return name; }
        int getRollNumber() const { return rollNumber; }
        double getGPA() const { return gpa; }
    };

    // Another NESTED CLASS
    class Course {
    private:
        string courseName;
        string courseCode;
        int credits;

    public:
        Course(const string& name, const string& code, int c)
            : courseName(name), courseCode(code), credits(c) {
            cout << "✓ Course created: " << courseName << "\n";
        }

        void display() const {
            cout << "  Course: " << courseName << " (" << courseCode 
                 << ") - " << credits << " credits\n";
        }

        string getCourseName() const { return courseName; }
        string getCourseCode() const { return courseCode; }
    };

    University(const string& name) : universityName(name) {
        cout << "✓ University created: " << universityName << "\n";
    }

    void displayInfo() const {
        cout << "University: " << universityName << "\n";
    }
};

// Usage: University::Student or University::Course

// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "2. ACCESS CONTROL IN NESTED CLASSES\n";
cout << string(70, '=') << "\n\n";

class Bank {
private:
    string bankName;

    // PRIVATE NESTED CLASS - Accessible only within Bank
    class AccountValidator {
    private:
        int minBalance;
        int maxTransactionAmount;

    public:
        AccountValidator() : minBalance(100), maxTransactionAmount(100000) {}

        bool isValidBalance(int balance) const {
            return balance >= minBalance;
        }

        bool isValidTransaction(int amount) const {
            return amount <= maxTransactionAmount && amount > 0;
        }

        int getMinBalance() const { return minBalance; }
    };

protected:
    // PROTECTED NESTED CLASS - Accessible in Bank and derived classes
    class AccountRecord {
    protected:
        string accountNumber;
        string accountHolder;
        double balance;

    public:
        AccountRecord(const string& accNo, const string& holder, double bal)
            : accountNumber(accNo), accountHolder(holder), balance(bal) {
            cout << "✓ Account created: " << accountNumber << "\n";
        }

        virtual void display() const {
            cout << "  Account: " << accountNumber << " (" << accountHolder 
                 << ") - Balance: $" << balance << "\n";
        }

        double getBalance() const { return balance; }
    };

public:
    // PUBLIC NESTED CLASS - Accessible from outside
    class SavingsAccount {
    private:
        string accountNumber;
        string accountHolder;
        double balance;
        double interestRate;

    public:
        SavingsAccount(const string& accNo, const string& holder, 
                      double bal, double rate)
            : accountNumber(accNo), accountHolder(holder), 
              balance(bal), interestRate(rate) {
            cout << "✓ Savings Account created: " << accountNumber << "\n";
        }

        void display() const {
            cout << "  Savings Account: " << accountNumber << " (" 
                 << accountHolder << ") - Balance: $" << balance 
                 << " (Rate: " << interestRate << "%)\n";
        }

        void addInterest() {
            balance += balance * (interestRate / 100.0);
            cout << "  ✓ Interest added. New balance: $" << balance << "\n";
        }
    };

    Bank(const string& name) : bankName(name) {
        cout << "✓ Bank created: " << bankName << "\n";
    }
};

// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "3. NESTED CLASS WITH ENUM\n";
cout << string(70, '=') << "\n\n";

class Company {
public:
    // NESTED ENUM - Scope limited to Company
    enum class Department {
        ENGINEERING,
        SALES,
        MARKETING,
        HR,
        FINANCE
    };

    enum class EmployeeStatus {
        ACTIVE,
        INACTIVE,
        ON_LEAVE,
        RETIRED
    };

    // NESTED CLASS using nested enums
    class Employee {
    private:
        string employeeName;
        int employeeID;
        Department department;
        EmployeeStatus status;
        double salary;

    public:
        Employee(const string& name, int id, Department dept, double sal)
            : employeeName(name), employeeID(id), department(dept), 
              status(EmployeeStatus::ACTIVE), salary(sal) {
            cout << "✓ Employee created: " << name << "\n";
        }

        void display() const {
            cout << "  Employee: " << employeeName << " (ID: " << employeeID 
                 << ")\n";
            cout << "    Department: " << getDepartmentString(department) 
                 << ", Status: " << getStatusString(status) 
                 << ", Salary: $" << salary << "\n";
        }

        void setStatus(EmployeeStatus s) {
            status = s;
            cout << "  ✓ Employee " << employeeName << " status changed to " 
                 << getStatusString(s) << "\n";
        }

        EmployeeStatus getStatus() const { return status; }
        Department getDepartment() const { return department; }
        double getSalary() const { return salary; }

    private:
        static string getDepartmentString(Department dept) {
            switch (dept) {
                case Department::ENGINEERING: return "Engineering";
                case Department::SALES: return "Sales";
                case Department::MARKETING: return "Marketing";
                case Department::HR: return "Human Resources";
                case Department::FINANCE: return "Finance";
                default: return "Unknown";
            }
        }

        static string getStatusString(EmployeeStatus status) {
            switch (status) {
                case EmployeeStatus::ACTIVE: return "Active";
                case EmployeeStatus::INACTIVE: return "Inactive";
                case EmployeeStatus::ON_LEAVE: return "On Leave";
                case EmployeeStatus::RETIRED: return "Retired";
                default: return "Unknown";
            }
        }
    };

    class Department_Info {
    private:
        string departmentName;
        int departmentCode;
        vector<Employee> employees;

    public:
        Department_Info(const string& name, int code)
            : departmentName(name), departmentCode(code) {
            cout << "✓ Department created: " << name << "\n";
        }

        void addEmployee(const Employee& emp) {
            employees.push_back(emp);
        }

        void displayAllEmployees() const {
            cout << "Department: " << departmentName << " (Code: " 
                 << departmentCode << ")\n";
            cout << "Employees:\n";
            for (const auto& emp : employees) {
                emp.display();
            }
        }
    };
};

// Usage: Company::Employee, Company::Department, Company::EmployeeStatus

// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "4. NESTED CLASS WITH CONTAINERS\n";
cout << string(70, '=') << "\n\n";

class Library {
public:
    // NESTED CLASS 1
    class Book {
    private:
        string title;
        string author;
        string isbn;
        int year;
        bool isAvailable;

    public:
        Book(const string& t, const string& a, const string& i, int y)
            : title(t), author(a), isbn(i), year(y), isAvailable(true) {}

        void display() const {
            cout << "    \"" << title << "\" by " << author << " (" << year 
                 << ") [" << (isAvailable ? "Available" : "Borrowed") << "]\n";
        }

        string getISBN() const { return isbn; }
        string getTitle() const { return title; }
        bool getAvailability() const { return isAvailable; }
        void setAvailability(bool available) { isAvailable = available; }
    };

    // NESTED CLASS 2
    class Member {
    private:
        string memberName;
        int memberID;
        vector<Book> borrowedBooks;  // Container of nested class
        int maxBooksAllowed;

    public:
        Member(const string& name, int id, int maxBooks = 5)
            : memberName(name), memberID(id), maxBooksAllowed(maxBooks) {
            cout << "✓ Member registered: " << name << "\n";
        }

        bool borrowBook(const Book& book) {
            if (borrowedBooks.size() >= maxBooksAllowed) {
                cout << "  ✗ Cannot borrow - Max limit reached\n";
                return false;
            }
            borrowedBooks.push_back(book);
            cout << "  ✓ " << memberName << " borrowed: \"" 
                 << book.getTitle() << "\"\n";
            return true;
        }

        void displayBorrowedBooks() const {
            cout << "  Member: " << memberName << " (ID: " << memberID << ")\n";
            cout << "  Borrowed Books (" << borrowedBooks.size() << "/" 
                 << maxBooksAllowed << "):\n";
            if (borrowedBooks.empty()) {
                cout << "    No books borrowed\n";
            } else {
                for (const auto& book : borrowedBooks) {
                    book.display();
                }
            }
        }

        int getBorrowedCount() const { return borrowedBooks.size(); }
    };

    // NESTED CLASS 3 - Manages collections
    class Inventory {
    private:
        string inventoryName;
        map<string, Book> books;  // Map container with nested class

    public:
        Inventory(const string& name) : inventoryName(name) {}

        void addBook(const Book& book) {
            books[book.getISBN()] = book;
            cout << "✓ Book added to inventory: \"" << book.getTitle() << "\"\n";
        }

        bool hasBook(const string& isbn) const {
            return books.find(isbn) != books.end();
        }

        void displayAllBooks() const {
            cout << "Inventory: " << inventoryName << "\n";
            if (books.empty()) {
                cout << "  No books in inventory\n";
                return;
            }
            for (const auto& [isbn, book] : books) {
                cout << "  ";
                book.display();
            }
        }

        int getTotalBooks() const { return books.size(); }
    };

    Library(const string& name) : libraryName(name) {
        cout << "✓ Library created: " << name << "\n";
    }

private:
    string libraryName;
};

// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "5. NESTED CLASS WITH MULTIPLE LEVELS (Deep Nesting)\n";
cout << string(70, '=') << "\n\n";

class Project {
public:
    class Team {
    public:
        // DOUBLE NESTED CLASS - Class within nested class
        class Developer {
        private:
            string developerName;
            string role;
            vector<string> skills;

        public:
            Developer(const string& name, const string& r)
                : developerName(name), role(r) {}

            void addSkill(const string& skill) {
                skills.push_back(skill);
            }

            void display() const {
                cout << "        Developer: " << developerName 
                     << " (" << role << ")\n";
                cout << "        Skills: ";
                for (const auto& skill : skills) {
                    cout << skill << " ";
                }
                cout << "\n";
            }
        };

        // DOUBLE NESTED CLASS 2
        class Module {
        private:
            string moduleName;
            vector<Developer> developers;

        public:
            Module(const string& name) : moduleName(name) {}

            void addDeveloper(const Developer& dev) {
                developers.push_back(dev);
            }

            void display() const {
                cout << "      Module: " << moduleName << "\n";
                cout << "      Developers:\n";
                for (const auto& dev : developers) {
                    dev.display();
                }
            }
        };

    private:
        string teamName;
        vector<Module> modules;

    public:
        Team(const string& name) : teamName(name) {}

        void addModule(const Module& module) {
            modules.push_back(module);
        }

        void display() const {
            cout << "    Team: " << teamName << "\n";
            cout << "    Modules:\n";
            for (const auto& module : modules) {
                module.display();
            }
        }
    };

private:
    string projectName;
    vector<Team> teams;

public:
    Project(const string& name) : projectName(name) {
        cout << "✓ Project created: " << name << "\n";
    }

    void addTeam(const Team& team) {
        teams.push_back(team);
    }

    void displayProjectStructure() const {
        cout << "  Project: " << projectName << "\n";
        cout << "  Teams:\n";
        for (const auto& team : teams) {
            team.display();
        }
    }
};

// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "6. NESTED CLASS WITH FRIEND RELATIONSHIP\n";
cout << string(70, '=') << "\n\n";

class BankAccount {
private:
    string accountNumber;
    double balance;
    
    // Friend declaration for nested class
    friend class Transaction;

public:
    // NESTED CLASS with access to outer class private members
    class Transaction {
    private:
        string transactionID;
        double amount;
        string type;  // "DEPOSIT" or "WITHDRAWAL"
        BankAccount* account;

    public:
        Transaction(const string& id, double amt, const string& t, 
                   BankAccount* acc)
            : transactionID(id), amount(amt), type(t), account(acc) {}

        void execute() {
            cout << "  Processing " << type << " Transaction (" 
                 << transactionID << "): $" << amount << "\n";
            cout << "  Current balance: $" << account->balance << " -> ";
            
            if (type == "DEPOSIT") {
                account->balance += amount;
            } else if (type == "WITHDRAWAL") {
                if (account->balance >= amount) {
                    account->balance -= amount;
                } else {
                    cout << "Insufficient funds!\n";
                    return;
                }
            }
            cout << "$" << account->balance << "\n";
        }

        void display() const {
            cout << "    Transaction " << transactionID << ": " << type 
                 << " $" << amount << "\n";
        }
    };

    BankAccount(const string& accNo, double initialBalance)
        : accountNumber(accNo), balance(initialBalance) {
        cout << "✓ Account " << accountNo << " created with balance: $" 
             << balance << "\n";
    }

    void executeTransaction(const Transaction& trans) {
        const_cast<Transaction&>(trans).execute();
    }

    double getBalance() const { return balance; }
};

// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "7. NESTED CLASS WITH STATIC MEMBERS\n";
cout << string(70, '=') << "\n\n";

class Game {
public:
    class Player {
    private:
        string playerName;
        int playerLevel;
        int score;
        static int totalPlayers;           // Static member
        static int highestScore;           // Static member
        static vector<string> leaderboard; // Static container

    public:
        Player(const string& name, int level)
            : playerName(name), playerLevel(level), score(0) {
            totalPlayers++;
            cout << "✓ Player created: " << name << " (Total players: " 
                 << totalPlayers << ")\n";
        }

        void addScore(int points) {
            score += points;
            cout << "  " << playerName << " earned " << points 
                 << " points. Total: " << score << "\n";
            
            if (score > highestScore) {
                highestScore = score;
                cout << "  🏆 New highest score: " << score << "\n";
            }
        }

        static void displayLeaderboard() {
            cout << "  LEADERBOARD (Highest Score: " << highestScore << ")\n";
            cout << "  Total Players: " << totalPlayers << "\n";
        }

        int getScore() const { return score; }
        string getName() const { return playerName; }

        // Static method
        static int getTotalPlayers() { return totalPlayers; }
        static int getHighestScore() { return highestScore; }
    };
};

// Static member initialization
int Game::Player::totalPlayers = 0;
int Game::Player::highestScore = 0;
vector<string> Game::Player::leaderboard;

// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "8. NESTED CLASS WITH TEMPLATES\n";
cout << string(70, '=') << "\n\n";

template <typename T>
class Container {
public:
    // TEMPLATE NESTED CLASS
    class Node {
    private:
        T data;
        Node* next;

    public:
        Node(const T& d) : data(d), next(nullptr) {}

        T getData() const { return data; }
        Node* getNext() const { return next; }
        void setNext(Node* n) { next = n; }
    };

    // Template nested class container
    class LinkedList {
    private:
        Node* head;

    public:
        LinkedList() : head(nullptr) {}

        void insert(const T& data) {
            Node* newNode = new Node(data);
            if (!head) {
                head = newNode;
            } else {
                Node* current = head;
                while (current->getNext()) {
                    current = current->getNext();
                }
                current->setNext(newNode);
            }
        }

        void display() const {
            cout << "    LinkedList: ";
            Node* current = head;
            while (current) {
                cout << current->getData() << " -> ";
                current = current->getNext();
            }
            cout << "nullptr\n";
        }

        ~LinkedList() {
            Node* current = head;
            while (current) {
                Node* temp = current;
                current = current->getNext();
                delete temp;
            }
        }
    };
};

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

void demonstrateBasicNesting() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "DEMO 1: Basic Nested Class\n";
    cout << string(70, '-') << "\n\n";

    University uni("MIT");
    
    // Create nested Student objects
    University::Student s1("Alice Johnson", 101, 3.8);
    University::Student s2("Bob Smith", 102, 3.5);
    
    // Create nested Course objects
    University::Course c1("C++ Programming", "CS101", 3);
    University::Course c2("Data Structures", "CS201", 4);
    
    s1.display();
    s2.display();
    cout << "\n";
    c1.display();
    c2.display();
}

void demonstrateAccessControl() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "DEMO 2: Access Control in Nested Classes\n";
    cout << string(70, '-') << "\n\n";

    Bank myBank("State Bank");
    
    // PUBLIC nested class - Can be accessed from outside
    Bank::SavingsAccount sa("SA001", "John Doe", 5000, 3.5);
    sa.display();
    sa.addInterest();
}

void demonstrateEnumWithNested() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "DEMO 3: Nested Class with Enum\n";
    cout << string(70, '-') << "\n\n";

    Company::Employee emp1("Alice", 1001, Company::Department::ENGINEERING, 75000);
    Company::Employee emp2("Bob", 1002, Company::Department::SALES, 60000);
    
    emp1.display();
    emp2.display();
    
    cout << "\nChanging Bob's status...\n";
    emp2.setStatus(Company::EmployeeStatus::ON_LEAVE);
    emp2.display();
}

void demonstrateContainers() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "DEMO 4: Nested Class with Containers\n";
    cout << string(70, '-') << "\n\n";

    Library myLibrary("City Library");
    
    // Create Book objects (nested class)
    Library::Book book1("The C++ Way", "Bjarne Stroustrup", "ISBN001", 2013);
    Library::Book book2("Effective C++", "Scott Meyers", "ISBN002", 2005);
    Library::Book book3("Clean Code", "Robert Martin", "ISBN003", 2008);
    
    // Create Member object (nested class with container)
    Library::Member member1("John Doe", 1001);
    
    cout << "\nMember borrowing books...\n";
    member1.borrowBook(book1);
    member1.borrowBook(book2);
    member1.borrowBook(book3);
    
    member1.displayBorrowedBooks();
}

void demonstrateDeepNesting() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "DEMO 5: Multiple Levels of Nesting\n";
    cout << string(70, '-') << "\n\n";

    Project myProject("AI Assistant");
    
    // Create double nested objects
    Project::Team::Developer dev1("Alice", "Senior");
    dev1.addSkill("C++");
    dev1.addSkill("Python");
    dev1.addSkill("Machine Learning");
    
    Project::Team::Developer dev2("Bob", "Junior");
    dev2.addSkill("C++");
    dev2.addSkill("Testing");
    
    Project::Team::Module backendModule("Backend");
    backendModule.addDeveloper(dev1);
    backendModule.addDeveloper(dev2);
    
    Project::Team devTeam("Development");
    devTeam.addModule(backendModule);
    
    myProject.addTeam(devTeam);
    myProject.displayProjectStructure();
}

void demonstrateFriendRelationship() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "DEMO 6: Nested Class with Friend Access\n";
    cout << string(70, '-') << "\n\n";

    BankAccount myAccount("ACC123", 1000);
    
    cout << "Initial balance: $" << myAccount.getBalance() << "\n\n";
    
    BankAccount::Transaction trans1("T001", 500, "DEPOSIT", &myAccount);
    myAccount.executeTransaction(trans1);
    
    BankAccount::Transaction trans2("T002", 200, "WITHDRAWAL", &myAccount);
    myAccount.executeTransaction(trans2);
    
    cout << "\nFinal balance: $" << myAccount.getBalance() << "\n";
}

void demonstrateStaticMembers() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "DEMO 7: Nested Class with Static Members\n";
    cout << string(70, '-') << "\n\n";

    Game::Player p1("Alice", 1);
    Game::Player p2("Bob", 1);
    Game::Player p3("Charlie", 1);
    
    p1.addScore(100);
    p2.addScore(150);
    p3.addScore(80);
    
    p1.addScore(200);  // Alice now has highest score
    
    Game::Player::displayLeaderboard();
    cout << "  Total Players: " << Game::Player::getTotalPlayers() << "\n";
    cout << "  Highest Score: " << Game::Player::getHighestScore() << "\n";
}

void demonstrateTemplateNesting() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "DEMO 8: Nested Template Classes\n";
    cout << string(70, '-') << "\n\n";

    Container<int>::LinkedList intList;
    intList.insert(10);
    intList.insert(20);
    intList.insert(30);
    intList.display();
    
    Container<string>::LinkedList stringList;
    stringList.insert("Hello");
    stringList.insert("Nested");
    stringList.insert("Classes");
    stringList.display();
}

void summaryAndBestPractices() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "SUMMARY: NESTED CLASSES - BEST PRACTICES\n";
    cout << string(70, '=') << "\n\n";

    cout << "1. ENCAPSULATION\n";
    cout << "   ✓ Use private nested classes to hide implementation\n";
    cout << "   ✓ Logical grouping of related functionality\n\n";

    cout << "2. SCOPE MANAGEMENT\n";
    cout << "   ✓ Inner class names don't pollute global namespace\n";
    cout << "   ✓ Reference as OuterClass::InnerClass\n\n";

    cout << "3. ACCESS CONTROL\n";
    cout << "   ✓ public: Accessible from outside\n";
    cout << "   ✓ protected: Accessible in derived classes\n";
    cout << "   ✓ private: Hidden from outside (internal use only)\n\n";

    cout << "4. WITH CONTAINERS\n";
    cout << "   ✓ Store multiple instances in vector/map/list\n";
    cout << "   ✓ Efficient memory management\n";
    cout << "   ✓ Flexible data structure design\n\n";

    cout << "5. WITH ENUMS\n";
    cout << "   ✓ Type-safe constants within class scope\n";
    cout << "   ✓ Better code organization\n";
    cout << "   ✓ Prevents value collisions\n\n";

    cout << "6. MULTI-LEVEL NESTING\n";
    cout << "   ✓ Deep nesting for complex hierarchies\n";
    cout << "   ✓ Use cautiously (can reduce readability)\n";
    cout << "   ✓ Limit to 2-3 levels for clarity\n\n";

    cout << "7. USE CASES\n";
    cout << "   ✓ Iterator classes in containers (std::vector::iterator)\n";
    cout << "   ✓ Node classes in linked lists/trees\n";
    cout << "   ✓ State classes in state machines\n";
    cout << "   ✓ Validator classes in business logic\n";
    cout << "   ✓ Transaction classes in financial systems\n\n";

    cout << "8. ADVANTAGES\n";
    cout << "   ✓ Logical encapsulation\n";
    cout << "   ✓ Namespace organization\n";
    cout << "   ✓ Access control to implementation details\n";
    cout << "   ✓ Clear relationship between classes\n\n";

    cout << "9. DISADVANTAGES\n";
    cout << "   ✗ Reduced readability if overused\n";
    cout << "   ✗ Increased complexity\n";
    cout << "   ✗ Limited reusability (tightly coupled)\n";
    cout << "   ✗ Difficult to test in isolation\n\n";

    cout << "10. COMMON MISTAKES\n";
    cout << "    ✗ Over-nesting (more than 3 levels)\n";
    cout << "    ✗ Using nested classes when composition is better\n";
    cout << "    ✗ Not declaring as friend when needed\n";
    cout << "    ✗ Forgetting access specifiers\n";
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    cout << "\n";
    cout << "╔" << string(68, '═') << "╗\n";
    cout << "║" << string(13, ' ') << "NESTED CLASSES - COMPREHENSIVE DEEP DIVE" << string(15, ' ') << "║\n";
    cout << "╚" << string(68, '═') << "╝\n";

    demonstrateBasicNesting();
    demonstrateAccessControl();
    demonstrateEnumWithNested();
    demonstrateContainers();
    demonstrateDeepNesting();
    demonstrateFriendRelationship();
    demonstrateStaticMembers();
    demonstrateTemplateNesting();
    summaryAndBestPractices();

    cout << "\n" << string(70, '=') << "\n";
    cout << "END OF NESTED CLASSES DEEP DIVE\n";
    cout << string(70, '=') << "\n\n";

    return 0;
}

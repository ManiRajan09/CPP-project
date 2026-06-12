#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>

using namespace std;

// ============================================================================
// COMPREHENSIVE GUIDE TO ALL CONSTRUCTOR TYPES IN C++
// ============================================================================

cout << "\n" << "="*70 << "\n";
cout << "1. DEFAULT CONSTRUCTOR (No parameters)\n";
cout << "="*70 << "\n\n";

class Student {
private:
    string name;
    int rollNo;
    double gpa;

public:
    // Default Constructor - Takes no arguments
    // Called when: Student s;  OR  Student s = Student();
    // Purpose: Initialize object with default values
    Student() : name("Unknown"), rollNo(0), gpa(0.0) {
        cout << "✓ Default Constructor: Created default student\n";
    }

    // Parameterized Constructor (explained below)
    Student(const string& n, int r, double g) 
        : name(n), rollNo(r), gpa(g) {
        cout << "✓ Parameterized Constructor: Created " << n << "\n";
    }

    void display() const {
        cout << "Student: " << name << " (Roll: " << rollNo << ", GPA: " << gpa << ")\n";
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "2. PARAMETERIZED CONSTRUCTOR (Takes parameters)\n";
cout << "="*70 << "\n\n";

class Car {
private:
    string brand;
    string model;
    int year;

public:
    // Parameterized Constructor - Takes arguments
    // Called when: Car c("Toyota", "Camry", 2023);
    // Purpose: Initialize object with specific values
    Car(const string& b, const string& m, int y) 
        : brand(b), model(m), year(y) {
        cout << "✓ Parameterized Constructor: Created " << b << " " << m << "\n";
    }

    void display() const {
        cout << "Car: " << brand << " " << model << " (" << year << ")\n";
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "3. COPY CONSTRUCTOR (Already covered in detail)\n";
cout << "="*70 << "\n\n";

class Account {
private:
    int* balance;

public:
    Account(int b) {
        balance = new int(b);
        cout << "✓ Constructor: Created account with balance $" << b << "\n";
    }

    // Copy Constructor - Makes independent copy
    Account(const Account& other) {
        balance = new int(*other.balance);
        cout << "✓ Copy Constructor: Copied account\n";
    }

    ~Account() {
        delete balance;
    }

    void display() const {
        cout << "Balance: $" << *balance << "\n";
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "4. MOVE CONSTRUCTOR (Already covered in detail)\n";
cout << "="*70 << "\n\n";

class DataBuffer {
private:
    int* data;
    int size;

public:
    DataBuffer(int s) : size(s) {
        data = new int[size];
        cout << "✓ Constructor: Created buffer\n";
    }

    // Move Constructor - Transfers ownership
    DataBuffer(DataBuffer&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "✓ Move Constructor: Transferred resources\n";
    }

    ~DataBuffer() {
        if (data) delete[] data;
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "5. CONVERTING CONSTRUCTOR (Single parameter conversion)\n";
cout << "="*70 << "\n\n";

class Temperature {
private:
    double celsius;

public:
    // Converting Constructor - Converts from one type to another
    // Called when: Temperature t = 98.6;  (implicit)
    // OR: Temperature t(98.6);  (explicit)
    // Purpose: Automatic type conversion
    Temperature(double c) : celsius(c) {
        cout << "✓ Converting Constructor: " << c << "°C\n";
    }

    void display() const {
        cout << "Temperature: " << celsius << "°C\n";
    }
};

// Prevent implicit conversion with 'explicit' keyword
class Salary {
private:
    double amount;

public:
    // explicit keyword prevents implicit conversion
    // Temperature t = 98.6;  ← Works (implicit)
    // Salary s = 50000;      ← Would fail without explicit keyword if we allow it
    explicit Salary(double a) : amount(a) {
        cout << "✓ Explicit Converting Constructor: $" << a << "\n";
    }

    void display() const {
        cout << "Salary: $" << amount << "\n";
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "6. DELEGATING CONSTRUCTOR (C++11 - Calls another constructor)\n";
cout << "="*70 << "\n\n";

class Rectangle {
private:
    double width, height;

    void validateDimensions() {
        if (width <= 0 || height <= 0) {
            width = height = 1.0;
        }
    }

public:
    // Main constructor with full logic
    Rectangle(double w, double h) : width(w), height(h) {
        validateDimensions();
        cout << "✓ Main Constructor: Created rectangle (" << w << "x" << h << ")\n";
    }

    // Delegating Constructor - Calls another constructor
    // Purpose: Reduce code duplication
    Rectangle() : Rectangle(1.0, 1.0) {
        cout << "✓ Delegating Constructor: Called main constructor\n";
    }

    // Another delegating constructor
    Rectangle(double side) : Rectangle(side, side) {
        cout << "✓ Delegating Constructor: Created square with side " << side << "\n";
    }

    void display() const {
        cout << "Rectangle: " << width << " x " << height << " (Area: " 
             << (width * height) << ")\n";
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "7. INITIALIZER LIST CONSTRUCTOR (C++11)\n";
cout << "="*70 << "\n\n";

class IntVector {
private:
    vector<int> data;

public:
    // Initializer List Constructor
    // Called when: IntVector v = {1, 2, 3, 4, 5};
    // OR: IntVector v{1, 2, 3, 4, 5};
    // Purpose: Initialize from initializer list
    IntVector(initializer_list<int> list) : data(list) {
        cout << "✓ Initializer List Constructor: Created vector with " 
             << data.size() << " elements\n";
    }

    void display() const {
        cout << "Vector: [";
        for (size_t i = 0; i < data.size(); i++) {
            cout << data[i];
            if (i < data.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }

    size_t size() const { return data.size(); }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "8. COPY ASSIGNMENT OPERATOR (Not strictly a constructor)\n";
cout << "="*70 << "\n\n";

class Book {
private:
    string title;
    int pages;

public:
    Book(const string& t, int p) : title(t), pages(p) {
        cout << "✓ Constructor: Created book \"" << t << "\"\n";
    }

    // Copy Assignment Operator (Not a constructor, but similar)
    Book& operator=(const Book& other) {
        if (this != &other) {
            title = other.title;
            pages = other.pages;
            cout << "✓ Copy Assignment: Assigned book\n";
        }
        return *this;
    }

    void display() const {
        cout << "Book: \"" << title << "\" (" << pages << " pages)\n";
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "9. CONVERSION BY OPERATOR (Type casting)\n";
cout << "="*70 << "\n\n";

class Distance {
private:
    double meters;

public:
    Distance(double m = 0) : meters(m) {
        cout << "✓ Distance Constructor: " << m << " meters\n";
    }

    // Conversion operator - Convert Distance to double (feet)
    // Called when: double feet = (double)distance;
    // Purpose: Define how to convert this object to another type
    operator double() const {
        return meters * 3.28084;  // Convert to feet
    }

    void display() const {
        cout << "Distance: " << meters << "m (" << (double)*this << " feet)\n";
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "10. DELETED CONSTRUCTOR (C++11)\n";
cout << "="*70 << "\n\n";

class NonCopyable {
private:
    int value;

public:
    NonCopyable(int v) : value(v) {
        cout << "✓ Constructor: Created non-copyable object\n";
    }

    // Delete copy constructor - Prevent copying
    NonCopyable(const NonCopyable&) = delete;

    // Delete copy assignment - Prevent assignment
    NonCopyable& operator=(const NonCopyable&) = delete;

    void display() const {
        cout << "Value: " << value << "\n";
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "11. DEFAULTED CONSTRUCTOR (C++11)\n";
cout << "="*70 << "\n\n";

class Simple {
private:
    int x;
    double y;

public:
    // Explicitly request compiler-generated default constructor
    // Same as writing it yourself with default values
    Simple() = default;

    Simple(int a, double b) : x(a), y(b) {
        cout << "✓ Parameterized Constructor: " << a << ", " << b << "\n";
    }

    void display() const {
        cout << "Simple: (" << x << ", " << y << ")\n";
    }
};

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "12. PRIVATE CONSTRUCTOR (Singleton pattern)\n";
cout << "="*70 << "\n\n";

class Singleton {
private:
    static Singleton* instance;
    int id;

    // Private Constructor - Can't be called from outside
    // Purpose: Control object creation (Singleton pattern)
    Singleton(int i = 0) : id(i) {
        cout << "✓ Private Constructor: Created Singleton instance\n";
    }

public:
    // Static method to get the single instance
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton(1);
        }
        return instance;
    }

    void display() const {
        cout << "Singleton ID: " << id << "\n";
    }
};

Singleton* Singleton::instance = nullptr;

// ============================================================================
cout << "\n" << "="*70 << "\n";
cout << "13. TEMPLATED CONSTRUCTOR (Template)\n";
cout << "="*70 << "\n\n";

template <typename T>
class Container {
private:
    T value;

public:
    // Templated Constructor
    // Purpose: Initialize with any type
    Container(T v) : value(v) {
        cout << "✓ Templated Constructor: Created container\n";
    }

    T getValue() const {
        return value;
    }

    void display() const {
        cout << "Container value type: ";
        if (typeid(T) == typeid(int)) cout << "int";
        else if (typeid(T) == typeid(string)) cout << "string";
        else if (typeid(T) == typeid(double)) cout << "double";
        else cout << "unknown";
        cout << "\n";
    }
};

// ============================================================================

int main() {
    cout << "\n";
    cout << "╔" << string(68, '═') << "╗\n";
    cout << "║" << string(20, ' ') << "ALL CONSTRUCTOR TYPES IN C++" << string(18, ' ') << "║\n";
    cout << "╚" << string(68, '═') << "╝\n";

    // 1. Default Constructor
    cout << "\n--- 1. DEFAULT CONSTRUCTOR ---\n";
    Student s1;
    s1.display();

    // 2. Parameterized Constructor
    cout << "\n--- 2. PARAMETERIZED CONSTRUCTOR ---\n";
    Car car("BMW", "M5", 2024);
    car.display();

    // 3. Copy Constructor
    cout << "\n--- 3. COPY CONSTRUCTOR ---\n";
    Account acc1(5000);
    Account acc2 = acc1;
    acc1.display();

    // 4. Move Constructor
    cout << "\n--- 4. MOVE CONSTRUCTOR ---\n";
    DataBuffer buf1(100);
    DataBuffer buf2 = move(buf1);

    // 5. Converting Constructor
    cout << "\n--- 5. CONVERTING CONSTRUCTOR ---\n";
    Temperature t1 = 37.5;  // Implicit conversion
    Temperature t2(98.6);   // Explicit conversion
    t1.display();

    // 6. Delegating Constructor
    cout << "\n--- 6. DELEGATING CONSTRUCTOR ---\n";
    Rectangle rect1;
    Rectangle rect2(5.0);
    Rectangle rect3(4.0, 3.0);
    rect1.display();
    rect2.display();
    rect3.display();

    // 7. Initializer List Constructor
    cout << "\n--- 7. INITIALIZER LIST CONSTRUCTOR ---\n";
    IntVector vec = {10, 20, 30, 40, 50};
    vec.display();

    // 8. Copy Assignment
    cout << "\n--- 8. COPY ASSIGNMENT OPERATOR ---\n";
    Book book1("C++ Primer", 1000);
    Book book2("Data Structures", 500);
    book2 = book1;
    book2.display();

    // 9. Conversion Operator
    cout << "\n--- 9. CONVERSION OPERATOR ---\n";
    Distance d(100);
    d.display();
    double feet = (double)d;
    cout << "Converted to feet: " << feet << "\n";

    // 10. Deleted Constructor
    cout << "\n--- 10. DELETED CONSTRUCTOR ---\n";
    NonCopyable nc(42);
    nc.display();
    // NonCopyable nc2 = nc;  ← This would fail (deleted copy constructor)

    // 11. Defaulted Constructor
    cout << "\n--- 11. DEFAULTED CONSTRUCTOR ---\n";
    Simple simp;
    simp.display();

    // 12. Private Constructor (Singleton)
    cout << "\n--- 12. PRIVATE CONSTRUCTOR (SINGLETON) ---\n";
    Singleton* single = Singleton::getInstance();
    single->display();

    // 13. Templated Constructor
    cout << "\n--- 13. TEMPLATED CONSTRUCTOR ---\n";
    Container<int> container1(42);
    Container<string> container2("Hello");
    container1.display();
    container2.display();

    cout << "\n" << string(70, '=') << "\n";
    cout << "END OF DEMONSTRATION\n";
    cout << string(70, '=') << "\n\n";

    return 0;
}

#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;
    int size;

public:
    // Constructor
    DynamicArray(int s) {
        size = s;
        data = new int[size];
        cout << "Constructor called: Allocated memory for " << size << " elements\n";
    }

    // Copy Constructor (Deep Copy)
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new int[size];  // Allocate NEW memory
        
        // Copy each element
        for(int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Copy Constructor called: Deep copy created\n";
    }

    // Assignment Operator (Deep Copy)
    DynamicArray& operator=(const DynamicArray& other) {
        if(this == &other) {  // Self-assignment check
            return *this;
        }
        
        // Delete old memory
        delete[] data;
        
        // Copy new data
        size = other.size;
        data = new int[size];
        for(int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "Assignment Operator called: Deep copy assigned\n";
        return *this;
    }

    // Destructor
    ~DynamicArray() {
        cout << "Destructor called: Freeing memory for " << size << " elements\n";
        delete[] data;
    }

    // Setter
    void set(int index, int value) {
        if(index >= 0 && index < size) {
            data[index] = value;
        }
    }

    // Getter
    int get(int index) const {
        if(index >= 0 && index < size) {
            return data[index];
        }
        return -1;
    }

    // Display array
    void display() const {
        cout << "Array: ";
        for(int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << "\n";
    }

    // Get size
    int getSize() const {
        return size;
    }
};

int main() {
    cout << "=== Deep Copy Example ===\n\n";

    // Create first object
    cout << "Creating obj1...\n";
    DynamicArray obj1(5);
    obj1.set(0, 10);
    obj1.set(1, 20);
    obj1.set(2, 30);
    obj1.set(3, 40);
    obj1.set(4, 50);
    cout << "obj1: ";
    obj1.display();

    cout << "\n--- Creating obj2 as copy of obj1 ---\n";
    DynamicArray obj2 = obj1;  // Copy Constructor called
    cout << "obj2: ";
    obj2.display();

    cout << "\n--- Modifying obj2 ---\n";
    obj2.set(0, 100);
    obj2.set(1, 200);
    cout << "obj2 after modification: ";
    obj2.display();

    cout << "\n--- Checking obj1 (should be unchanged) ---\n";
    cout << "obj1: ";
    obj1.display();

    cout << "\n--- Using Assignment Operator ---\n";
    DynamicArray obj3(3);
    obj3.set(0, 5);
    obj3.set(1, 15);
    obj3.set(2, 25);
    cout << "obj3 before assignment: ";
    obj3.display();

    cout << "\nAssigning obj1 to obj3...\n";
    obj3 = obj1;  // Assignment Operator called
    cout << "obj3 after assignment: ";
    obj3.display();

    cout << "\n--- Modifying obj3 ---\n";
    obj3.set(2, 999);
    cout << "obj3 after modification: ";
    obj3.display();

    cout << "\n--- Checking obj1 (should be unchanged) ---\n";
    cout << "obj1: ";
    obj1.display();

    cout << "\n=== End of Program ===\n";
    cout << "Destructors will be called automatically...\n";

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// ============================================================================
// RULE OF FIVE DEMONSTRATION
// ============================================================================
// The Rule of Five states: If a class needs a destructor, copy constructor,
// or copy assignment operator, it probably needs all five:
// 1. Destructor (~ClassName)
// 2. Copy Constructor (const ClassName&)
// 3. Copy Assignment Operator (operator=)
// 4. Move Constructor (ClassName&&) - C++11
// 5. Move Assignment Operator (operator=) - C++11
// ============================================================================

class DynamicBuffer {
private:
    int* data;
    int size;
    int capacity;

    // Helper function to display operation
    void logOperation(const string& operation) const {
        cout << "[" << operation << "] ";
        if (data) {
            cout << "Buffer(" << size << "/" << capacity << "): [";
            for (int i = 0; i < size; i++) {
                cout << data[i];
                if (i < size - 1) cout << ", ";
            }
            cout << "]\n";
        }
    }

public:
    // ========== 1. CONSTRUCTOR ==========
    DynamicBuffer(int initialSize = 5) : size(0), capacity(initialSize) {
        data = new int[capacity];
        cout << "✓ Constructor: Created buffer with capacity " << capacity << "\n";
    }

    // ========== 2. DESTRUCTOR ==========
    // Called when object is destroyed
    // Must deallocate dynamically allocated memory
    ~DynamicBuffer() {
        cout << "✗ Destructor: Destroying buffer";
        if (data) {
            cout << " with " << size << " elements\n";
            delete[] data;
        } else {
            cout << " (already moved)\n";
        }
        data = nullptr;
    }

    // ========== 3. COPY CONSTRUCTOR ==========
    // Called when: DynamicBuffer b2 = b1;  OR  DynamicBuffer b2(b1);
    // Makes a DEEP COPY - independent memory allocation
    // Use when you need: Two objects with independent data
    DynamicBuffer(const DynamicBuffer& other) : size(other.size), capacity(other.capacity) {
        cout << "→ Copy Constructor: Creating deep copy\n";
        data = new int[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        logOperation("After Copy Constructor");
    }

    // ========== 4. COPY ASSIGNMENT OPERATOR ==========
    // Called when: b2 = b1;  (where b2 already exists)
    // Must handle self-assignment (b = b)
    // Must deallocate old memory before assigning new
    DynamicBuffer& operator=(const DynamicBuffer& other) {
        cout << "→ Copy Assignment: Assigning from another buffer\n";
        
        // Self-assignment check
        if (this == &other) {
            cout << "  [Self-assignment detected. Skipping...]\n";
            return *this;
        }

        // Delete old memory
        delete[] data;

        // Copy new data
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        logOperation("After Copy Assignment");
        return *this;
    }

    // ========== 5. MOVE CONSTRUCTOR (C++11) ==========
    // Called when: DynamicBuffer b2 = move(b1);  OR  DynamicBuffer b2 = DynamicBuffer(...)
    // Makes a SHALLOW COPY - transfers ownership of resources
    // Use when: Source object is a temporary (rvalue) and will be destroyed
    // Advantage: MUCH FASTER - no memory allocation, just pointer transfer
    DynamicBuffer(DynamicBuffer&& other) noexcept 
        : data(other.data), size(other.size), capacity(other.capacity) {
        
        cout << "⟿ Move Constructor: Stealing resources from temporary\n";
        
        // Invalidate the source object so destructor won't delete our data
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
        
        logOperation("After Move Constructor");
    }

    // ========== 6. MOVE ASSIGNMENT OPERATOR (C++11) ==========
    // Called when: b2 = move(b1);  (where b2 already exists)
    // Transfers ownership of resources from rvalue to lvalue
    // Must handle self-assignment with move
    DynamicBuffer& operator=(DynamicBuffer&& other) noexcept {
        cout << "⟿ Move Assignment: Stealing resources from temporary\n";
        
        // Self-assignment check (unusual but possible with move)
        if (this == &other) {
            cout << "  [Self-assignment detected. Skipping...]\n";
            return *this;
        }

        // Delete old memory
        delete[] data;

        // Steal resources
        data = other.data;
        size = other.size;
        capacity = other.capacity;

        // Invalidate source
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;

        logOperation("After Move Assignment");
        return *this;
    }

    // Helper methods
    void push_back(int value) {
        if (size < capacity) {
            data[size++] = value;
        } else {
            cout << "Buffer is full!\n";
        }
    }

    void display() const {
        cout << "Buffer: [";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "] (Size: " << size << "/" << capacity << ")\n";
    }

    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
};

// ============================================================================
// DEMONSTRATION SCENARIOS
// ============================================================================

void demonstrateCopyConstructor() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "SCENARIO 1: Copy Constructor (Deep Copy - Slow but Safe)\n";
    cout << string(70, '=') << "\n\n";

    DynamicBuffer b1(5);
    b1.push_back(10);
    b1.push_back(20);
    b1.push_back(30);
    cout << "b1 created: ";
    b1.display();

    cout << "\nCreating b2 as copy of b1...\n";
    DynamicBuffer b2 = b1;  // Copy Constructor called
    cout << "b2 created: ";
    b2.display();

    cout << "\nModifying b2...\n";
    b2.push_back(40);
    cout << "b2 after modification: ";
    b2.display();

    cout << "b1 after b2 modification (unchanged): ";
    b1.display();
}

void demonstrateCopyAssignment() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "SCENARIO 2: Copy Assignment Operator (Deep Copy)\n";
    cout << string(70, '=') << "\n\n";

    DynamicBuffer b1(5);
    b1.push_back(100);
    b1.push_back(200);
    cout << "b1: ";
    b1.display();

    DynamicBuffer b2(3);
    b2.push_back(1);
    cout << "b2 before assignment: ";
    b2.display();

    cout << "\nAssigning b1 to b2 (b2 = b1)...\n";
    b2 = b1;  // Copy Assignment Operator called
    cout << "b2 after assignment: ";
    b2.display();
}

void demonstrateMoveConstructor() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "SCENARIO 3: Move Constructor (Shallow Copy - Fast!)\n";
    cout << string(70, '=') << "\n\n";

    cout << "Creating temporary buffer and moving to b1...\n";
    DynamicBuffer b1 = DynamicBuffer(5);  // Move Constructor called
    b1.push_back(111);
    b1.push_back(222);
    cout << "b1 after move: ";
    b1.display();

    cout << "\nUsing std::move to explicitly move b1 to b2...\n";
    DynamicBuffer b2 = move(b1);  // Move Constructor called
    cout << "b2 after move: ";
    b2.display();
    
    cout << "b1 after move (should be invalid): ";
    cout << "Size = " << b1.getSize() << ", isEmpty = " << (b1.isEmpty() ? "true" : "false") << "\n";
}

void demonstrateMoveAssignment() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "SCENARIO 4: Move Assignment Operator\n";
    cout << string(70, '=') << "\n\n";

    DynamicBuffer b1(5);
    b1.push_back(555);
    b1.push_back(666);
    cout << "b1: ";
    b1.display();

    DynamicBuffer b2(3);
    b2.push_back(7);
    cout << "b2 before assignment: ";
    b2.display();

    cout << "\nAssigning moved b1 to b2 (b2 = move(b1))...\n";
    b2 = move(b1);  // Move Assignment Operator called
    cout << "b2 after move assignment: ";
    b2.display();

    cout << "b1 after move (should be invalid): ";
    cout << "Size = " << b1.getSize() << "\n";
}

void demonstrateRuleOfFive() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "SCENARIO 5: Complete Rule of Five Demo\n";
    cout << string(70, '=') << "\n\n";

    DynamicBuffer original(4);
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);
    cout << "original: ";
    original.display();

    // Copy - independent copy
    cout << "\nCopy Constructor: DynamicBuffer copiedBuffer = original;\n";
    DynamicBuffer copiedBuffer = original;

    // Move - transfer ownership
    cout << "\nMove Constructor: DynamicBuffer movedBuffer = move(original);\n";
    DynamicBuffer movedBuffer = move(original);

    // Copy Assignment
    cout << "\nCopy Assignment: DynamicBuffer assigned = copiedBuffer;\n";
    DynamicBuffer assigned = DynamicBuffer(2);
    assigned = copiedBuffer;

    cout << "\nFinal state:\n";
    cout << "copiedBuffer: ";
    copiedBuffer.display();
    cout << "movedBuffer: ";
    movedBuffer.display();
    cout << "assigned: ";
    assigned.display();

    cout << "\n--- Destructors will be called in reverse order ---\n";
}

void performanceComparison() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "SCENARIO 6: Performance Comparison\n";
    cout << string(70, '=') << "\n\n";

    cout << "Copy: Allocates NEW memory, copies all data (O(n) time)\n";
    cout << "Move: Just transfers pointer (O(1) time)\n\n";

    cout << "When to use:\n";
    cout << "- Copy Constructor/Assignment: When you need independent copies\n";
    cout << "- Move Constructor/Assignment: When source is a temporary/rvalue\n";
    cout << "- Move is MUCH FASTER for large data structures!\n";
}

int main() {
    cout << "\n";
    cout << "╔" << string(68, '═') << "╗\n";
    cout << "║" << string(15, ' ') << "RULE OF FIVE & MOVE SEMANTICS DEMONSTRATION" << string(10, ' ') << "║\n";
    cout << "╚" << string(68, '═') << "╝\n";

    demonstrateCopyConstructor();
    demonstrateCopyAssignment();
    demonstrateMoveConstructor();
    demonstrateMoveAssignment();
    demonstrateRuleOfFive();
    performanceComparison();

    cout << "\n" << string(70, '=') << "\n";
    cout << "END OF DEMONSTRATION\n";
    cout << string(70, '=') << "\n\n";

    return 0;
}

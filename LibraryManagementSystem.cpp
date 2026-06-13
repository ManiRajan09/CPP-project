#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

// ============================================================================
// REAL-WORLD LIBRARY MANAGEMENT SYSTEM
// ============================================================================
// A complete library system demonstrating:
// - Nested classes for organization
// - Enums for type safety
// - Containers for data management
// - Complex relationships between entities
// - Friend classes for access control
// ============================================================================

class LibraryManagementSystem {
public:
    // ========== NESTED ENUMS ==========
    enum class BookCategory {
        FICTION,
        NON_FICTION,
        SCIENCE,
        TECHNOLOGY,
        HISTORY,
        BIOGRAPHY,
        ROMANCE,
        MYSTERY
    };

    enum class BookStatus {
        AVAILABLE,
        BORROWED,
        RESERVED,
        DAMAGED,
        LOST
    };

    enum class MembershipType {
        STANDARD,      // Can borrow 3 books
        PREMIUM,       // Can borrow 5 books
        VIP,           // Can borrow 10 books
        STUDENT,       // Can borrow 2 books, special discounts
        SENIOR         // Can borrow 3 books, free rental
    };

    enum class TransactionType {
        BORROW,
        RETURN,
        RESERVATION,
        FINE_PAYMENT,
        MEMBERSHIP_RENEWAL
    };

    // ========== NESTED CLASS 1: BOOK ==========
    class Book {
    private:
        string bookID;
        string title;
        string author;
        string isbn;
        int publicationYear;
        BookCategory category;
        BookStatus status;
        double replacementCost;
        int totalCopies;
        int availableCopies;
        string location;  // Shelf location in library

    public:
        Book(const string& id, const string& t, const string& a, 
             const string& i, int year, BookCategory cat, 
             double cost, int copies, const string& loc)
            : bookID(id), title(t), author(a), isbn(i), 
              publicationYear(year), category(cat), status(BookStatus::AVAILABLE),
              replacementCost(cost), totalCopies(copies), 
              availableCopies(copies), location(loc) {
            cout << "✓ Book registered: \"" << title << "\" by " << author << "\n";
        }

        // Getters
        string getBookID() const { return bookID; }
        string getTitle() const { return title; }
        string getAuthor() const { return author; }
        string getISBN() const { return isbn; }
        BookCategory getCategory() const { return category; }
        BookStatus getStatus() const { return status; }
        int getAvailableCopies() const { return availableCopies; }
        int getTotalCopies() const { return totalCopies; }
        double getReplacementCost() const { return replacementCost; }
        string getLocation() const { return location; }

        // Setters
        void setStatus(BookStatus s) { status = s; }
        void decreaseAvailableCopies() { 
            if (availableCopies > 0) availableCopies--; 
        }
        void increaseAvailableCopies() { 
            if (availableCopies < totalCopies) availableCopies++; 
        }

        // Display
        void display() const {
            cout << "  ┌─ Book Details ─────────────────────────────┐\n";
            cout << "  │ ID: " << bookID << "\n";
            cout << "  │ Title: \"" << title << "\"\n";
            cout << "  │ Author: " << author << "\n";
            cout << "  │ ISBN: " << isbn << "\n";
            cout << "  │ Year: " << publicationYear << "\n";
            cout << "  │ Category: " << getCategoryString(category) << "\n";
            cout << "  │ Status: " << getStatusString(status) << "\n";
            cout << "  │ Available: " << availableCopies << "/" << totalCopies << "\n";
            cout << "  │ Location: " << location << "\n";
            cout << "  │ Replacement Cost: $" << replacementCost << "\n";
            cout << "  └─────────────────────────────────────────────┘\n";
        }

    private:
        static string getCategoryString(BookCategory cat) {
            switch (cat) {
                case BookCategory::FICTION: return "Fiction";
                case BookCategory::NON_FICTION: return "Non-Fiction";
                case BookCategory::SCIENCE: return "Science";
                case BookCategory::TECHNOLOGY: return "Technology";
                case BookCategory::HISTORY: return "History";
                case BookCategory::BIOGRAPHY: return "Biography";
                case BookCategory::ROMANCE: return "Romance";
                case BookCategory::MYSTERY: return "Mystery";
                default: return "Unknown";
            }
        }

        static string getStatusString(BookStatus stat) {
            switch (stat) {
                case BookStatus::AVAILABLE: return "Available ✓";
                case BookStatus::BORROWED: return "Borrowed ✗";
                case BookStatus::RESERVED: return "Reserved ◆";
                case BookStatus::DAMAGED: return "Damaged ⚠";
                case BookStatus::LOST: return "Lost ⚠";
                default: return "Unknown";
            }
        }

        friend class LibraryManagementSystem;
    };

    // ========== NESTED CLASS 2: MEMBER ==========
    class Member {
    private:
        string memberID;
        string memberName;
        string email;
        string phone;
        MembershipType membershipType;
        time_t membershipStartDate;
        time_t membershipExpiryDate;
        vector<string> borrowedBookIDs;
        vector<string> reservedBookIDs;
        double outstandingFines;
        int maxBooksAllowed;

    public:
        Member(const string& id, const string& name, const string& e,
               const string& p, MembershipType type)
            : memberID(id), memberName(name), email(e), phone(p),
              membershipType(type), outstandingFines(0.0) {
            
            membershipStartDate = time(nullptr);
            membershipExpiryDate = membershipStartDate + (365 * 24 * 60 * 60); // 1 year
            
            // Set borrowing limits based on membership
            switch (type) {
                case MembershipType::STANDARD: maxBooksAllowed = 3; break;
                case MembershipType::PREMIUM: maxBooksAllowed = 5; break;
                case MembershipType::VIP: maxBooksAllowed = 10; break;
                case MembershipType::STUDENT: maxBooksAllowed = 2; break;
                case MembershipType::SENIOR: maxBooksAllowed = 3; break;
            }
            
            cout << "✓ Member registered: " << name << " (" 
                 << getMembershipString(type) << ")\n";
        }

        // Getters
        string getMemberID() const { return memberID; }
        string getMemberName() const { return memberName; }
        MembershipType getMembershipType() const { return membershipType; }
        vector<string> getBorrowedBooks() const { return borrowedBookIDs; }
        vector<string> getReservedBooks() const { return reservedBookIDs; }
        double getOutstandingFines() const { return outstandingFines; }
        int getMaxBooksAllowed() const { return maxBooksAllowed; }
        int getCurrentBorrowCount() const { return borrowedBookIDs.size(); }
        bool isMembershipActive() const { return time(nullptr) < membershipExpiryDate; }

        // Borrowing operations
        bool canBorrowBook() const {
            return borrowedBookIDs.size() < maxBooksAllowed && 
                   outstandingFines < 50.0 &&  // Can't borrow if fines > $50
                   isMembershipActive();
        }

        void borrowBook(const string& bookID) {
            borrowedBookIDs.push_back(bookID);
            cout << "  ✓ Book borrowed by " << memberName << "\n";
        }

        void returnBook(const string& bookID) {
            auto it = find(borrowedBookIDs.begin(), borrowedBookIDs.end(), bookID);
            if (it != borrowedBookIDs.end()) {
                borrowedBookIDs.erase(it);
                cout << "  ✓ Book returned by " << memberName << "\n";
            }
        }

        // Reservation operations
        void reserveBook(const string& bookID) {
            reservedBookIDs.push_back(bookID);
            cout << "  ✓ Book reserved by " << memberName << "\n";
        }

        void cancelReservation(const string& bookID) {
            auto it = find(reservedBookIDs.begin(), reservedBookIDs.end(), bookID);
            if (it != reservedBookIDs.end()) {
                reservedBookIDs.erase(it);
                cout << "  ✓ Reservation cancelled by " << memberName << "\n";
            }
        }

        // Fine operations
        void addFine(double amount) {
            outstandingFines += amount;
            cout << "  ⚠ Fine of $" << amount << " added to " << memberName 
                 << ". Total fines: $" << outstandingFines << "\n";
        }

        void payFine(double amount) {
            if (amount <= outstandingFines) {
                outstandingFines -= amount;
                cout << "  ✓ Fine payment of $" << amount << " received from " 
                     << memberName << ". Remaining: $" << outstandingFines << "\n";
            }
        }

        // Display
        void display() const {
            cout << "  ┌─ Member Details ───────────────────────────┐\n";
            cout << "  │ ID: " << memberID << "\n";
            cout << "  │ Name: " << memberName << "\n";
            cout << "  │ Email: " << email << "\n";
            cout << "  │ Phone: " << phone << "\n";
            cout << "  │ Type: " << getMembershipString(membershipType) << "\n";
            cout << "  │ Books Borrowed: " << borrowedBookIDs.size() 
                 << "/" << maxBooksAllowed << "\n";
            cout << "  │ Books Reserved: " << reservedBookIDs.size() << "\n";
            cout << "  │ Outstanding Fines: $" << fixed << setprecision(2) 
                 << outstandingFines << "\n";
            cout << "  │ Membership Status: " 
                 << (isMembershipActive() ? "Active ✓" : "Expired ✗") << "\n";
            cout << "  └─────────────────────────────────────────────┘\n";
        }

    private:
        static string getMembershipString(MembershipType type) {
            switch (type) {
                case MembershipType::STANDARD: return "Standard";
                case MembershipType::PREMIUM: return "Premium";
                case MembershipType::VIP: return "VIP";
                case MembershipType::STUDENT: return "Student";
                case MembershipType::SENIOR: return "Senior";
                default: return "Unknown";
            }
        }

        friend class LibraryManagementSystem;
    };

    // ========== NESTED CLASS 3: TRANSACTION ==========
    class Transaction {
    private:
        string transactionID;
        string memberID;
        string bookID;
        TransactionType type;
        time_t transactionDate;
        time_t dueDate;
        time_t returnDate;
        double amount;
        bool isCompleted;

    public:
        Transaction(const string& tID, const string& mID, const string& bID,
                   TransactionType t)
            : transactionID(tID), memberID(mID), bookID(bID), type(t),
              amount(0.0), isCompleted(false) {
            
            transactionDate = time(nullptr);
            
            // Set due date (14 days from borrow)
            if (t == TransactionType::BORROW) {
                dueDate = transactionDate + (14 * 24 * 60 * 60);
            }
            returnDate = 0;
        }

        // Getters
        string getTransactionID() const { return transactionID; }
        string getMemberID() const { return memberID; }
        string getBookID() const { return bookID; }
        TransactionType getType() const { return type; }
        double getAmount() const { return amount; }
        bool isComplete() const { return isCompleted; }
        time_t getDueDate() const { return dueDate; }

        // Setters
        void markAsCompleted() { isCompleted = true; }
        void setReturnDate(time_t date) { returnDate = date; }
        void setAmount(double amt) { amount = amt; }

        // Calculate late fine
        double calculateLateFine() const {
            if (type == TransactionType::BORROW && returnDate > 0) {
                if (returnDate > dueDate) {
                    long secondsLate = returnDate - dueDate;
                    int daysLate = secondsLate / (24 * 60 * 60);
                    return daysLate * 1.0;  // $1 per day late
                }
            }
            return 0.0;
        }

        // Display
        void display() const {
            cout << "  ┌─ Transaction Details ──────────────────────┐\n";
            cout << "  │ ID: " << transactionID << "\n";
            cout << "  │ Type: " << getTypeString(type) << "\n";
            cout << "  │ Member ID: " << memberID << "\n";
            cout << "  │ Book ID: " << bookID << "\n";
            cout << "  │ Status: " << (isCompleted ? "Completed ✓" : "Pending") << "\n";
            cout << "  │ Amount: $" << fixed << setprecision(2) << amount << "\n";
            cout << "  └─────────────────────────────────────────────┘\n";
        }

    private:
        static string getTypeString(TransactionType t) {
            switch (t) {
                case TransactionType::BORROW: return "Book Borrow";
                case TransactionType::RETURN: return "Book Return";
                case TransactionType::RESERVATION: return "Book Reservation";
                case TransactionType::FINE_PAYMENT: return "Fine Payment";
                case TransactionType::MEMBERSHIP_RENEWAL: return "Membership Renewal";
                default: return "Unknown";
            }
        }

        friend class LibraryManagementSystem;
    };

    // ========== NESTED CLASS 4: RESERVATION QUEUE ==========
    class ReservationQueue {
    private:
        string bookID;
        queue<string> memberQueue;  // Queue of member IDs waiting for book

    public:
        ReservationQueue(const string& bID) : bookID(bID) {}

        void addMemberToQueue(const string& memberID) {
            memberQueue.push(memberID);
            cout << "  ✓ Member " << memberID << " added to reservation queue for book " 
                 << bookID << " (Position: " << memberQueue.size() << ")\n";
        }

        string getNextMember() {
            if (!memberQueue.empty()) {
                string memberID = memberQueue.front();
                memberQueue.pop();
                cout << "  ✓ Book available for member " << memberID << "\n";
                return memberID;
            }
            return "";
        }

        int getQueueSize() const { return memberQueue.size(); }
        bool isEmpty() const { return memberQueue.empty(); }
        string getBookID() const { return bookID; }
    };

    // ========== NESTED CLASS 5: LIBRARY REPORT ==========
    class LibraryReport {
    private:
        map<string, Book> books;
        map<string, Member> members;
        vector<Transaction> transactions;

    public:
        LibraryReport() {}

        void addBookToReport(const Book& book) {
            books[book.getBookID()] = book;
        }

        void addMemberToReport(const Member& member) {
            members[member.getMemberID()] = member;
        }

        void addTransactionToReport(const Transaction& trans) {
            transactions.push_back(trans);
        }

        // Generate reports
        void generateInventoryReport() const {
            cout << "\n╔════════════════════════════════════════════════════╗\n";
            cout << "║          LIBRARY INVENTORY REPORT                  ║\n";
            cout << "╚════════════════════════════════════════════════════╝\n\n";

            int totalBooks = 0;
            int totalAvailable = 0;
            int totalBorrowed = 0;

            for (const auto& [id, book] : books) {
                totalBooks += book.getTotalCopies();
                totalAvailable += book.getAvailableCopies();
                totalBorrowed += (book.getTotalCopies() - book.getAvailableCopies());
            }

            cout << "Total Book Titles: " << books.size() << "\n";
            cout << "Total Copies: " << totalBooks << "\n";
            cout << "Available: " << totalAvailable << "\n";
            cout << "Borrowed: " << totalBorrowed << "\n\n";

            cout << "Detailed Inventory:\n";
            for (const auto& [id, book] : books) {
                cout << "  • " << book.getTitle() << " - " << book.getAvailableCopies() 
                     << "/" << book.getTotalCopies() << " available\n";
            }
        }

        void generateMembershipReport() const {
            cout << "\n╔════════════════════════════════════════════════════╗\n";
            cout << "║          MEMBERSHIP REPORT                         ║\n";
            cout << "╚════════════════════════════════════════════════════╝\n\n";

            cout << "Total Members: " << members.size() << "\n\n";

            map<MembershipType, int> membershipCount;
            double totalFines = 0.0;

            for (const auto& [id, member] : members) {
                membershipCount[member.getMembershipType()]++;
                totalFines += member.getOutstandingFines();
            }

            cout << "Membership Breakdown:\n";
            cout << "  • Standard: " << membershipCount[MembershipType::STANDARD] << "\n";
            cout << "  • Premium: " << membershipCount[MembershipType::PREMIUM] << "\n";
            cout << "  • VIP: " << membershipCount[MembershipType::VIP] << "\n";
            cout << "  • Student: " << membershipCount[MembershipType::STUDENT] << "\n";
            cout << "  • Senior: " << membershipCount[MembershipType::SENIOR] << "\n";

            cout << "\nTotal Outstanding Fines: $" << fixed << setprecision(2) 
                 << totalFines << "\n";
        }

        void generateTransactionReport() const {
            cout << "\n╔════════════════════════════════════════════════════╗\n";
            cout << "║          TRANSACTION REPORT                        ║\n";
            cout << "╚════════════════════════════════════════════════════╝\n\n";

            cout << "Total Transactions: " << transactions.size() << "\n\n";

            int borrows = 0, returns = 0, reservations = 0, fines = 0;
            double totalAmount = 0.0;

            for (const auto& trans : transactions) {
                switch (trans.getType()) {
                    case TransactionType::BORROW: borrows++; break;
                    case TransactionType::RETURN: returns++; break;
                    case TransactionType::RESERVATION: reservations++; break;
                    case TransactionType::FINE_PAYMENT: fines++; break;
                    default: break;
                }
                totalAmount += trans.getAmount();
            }

            cout << "Transaction Breakdown:\n";
            cout << "  • Borrows: " << borrows << "\n";
            cout << "  • Returns: " << returns << "\n";
            cout << "  • Reservations: " << reservations << "\n";
            cout << "  • Fine Payments: " << fines << "\n";
            cout << "\nTotal Amount Processed: $" << fixed << setprecision(2) 
                 << totalAmount << "\n";
        }
    };

private:
    map<string, Book> books;
    map<string, Member> members;
    vector<Transaction> transactions;
    map<string, ReservationQueue> reservationQueues;
    LibraryReport report;

public:
    LibraryManagementSystem() {
        cout << "\n╔════════════════════════════════════════════════════╗\n";
        cout << "║     LIBRARY MANAGEMENT SYSTEM INITIALIZED          ║\n";
        cout << "╚════════════════════════════════════════════════════╝\n\n";
    }

    // ========== BOOK OPERATIONS ==========
    void addBook(const Book& book) {
        books[book.getBookID()] = book;
        ReservationQueue queue(book.getBookID());
        reservationQueues[book.getBookID()] = queue;
    }

    Book* findBook(const string& bookID) {
        if (books.find(bookID) != books.end()) {
            return &books[bookID];
        }
        return nullptr;
    }

    void displayAllBooks() const {
        cout << "\n╔════════════════════════════════════════════════════╗\n";
        cout << "║          LIBRARY CATALOG                           ║\n";
        cout << "╚════════════════════════════════════════════════════╝\n\n";

        if (books.empty()) {
            cout << "No books in library.\n";
            return;
        }

        for (const auto& [id, book] : books) {
            book.display();
        }
    }

    // ========== MEMBER OPERATIONS ==========
    void registerMember(const Member& member) {
        members[member.getMemberID()] = member;
    }

    Member* findMember(const string& memberID) {
        if (members.find(memberID) != members.end()) {
            return &members[memberID];
        }
        return nullptr;
    }

    void displayAllMembers() const {
        cout << "\n╔════════════════════════════════════════════════════╗\n";
        cout << "║          REGISTERED MEMBERS                        ║\n";
        cout << "╚════════════════════════════════════════════════════╝\n\n";

        if (members.empty()) {
            cout << "No members registered.\n";
            return;
        }

        for (const auto& [id, member] : members) {
            member.display();
        }
    }

    // ========== BORROWING OPERATIONS ==========
    bool borrowBook(const string& memberID, const string& bookID) {
        cout << "\n--- BORROW OPERATION ---\n";

        Member* member = findMember(memberID);
        Book* book = findBook(bookID);

        if (!member) {
            cout << "✗ Member not found.\n";
            return false;
        }

        if (!book) {
            cout << "✗ Book not found.\n";
            return false;
        }

        if (!member->canBorrowBook()) {
            cout << "✗ Member cannot borrow book (limit reached or outstanding fines).\n";
            return false;
        }

        if (book->getAvailableCopies() <= 0) {
            cout << "✗ Book not available. Copies: 0\n";
            cout << "Would you like to reserve this book?\n";
            return false;
        }

        // Execute borrow
        member->borrowBook(bookID);
        book->decreaseAvailableCopies();
        book->setStatus(BookStatus::BORROWED);

        Transaction trans("T" + to_string(transactions.size() + 1), 
                         memberID, bookID, TransactionType::BORROW);
        trans.markAsCompleted();
        transactions.push_back(trans);

        cout << "✓ Book borrowed successfully!\n";
        cout << "  Due Date: 14 days from today\n";
        return true;
    }

    // ========== RETURN OPERATIONS ==========
    bool returnBook(const string& memberID, const string& bookID) {
        cout << "\n--- RETURN OPERATION ---\n";

        Member* member = findMember(memberID);
        Book* book = findBook(bookID);

        if (!member || !book) {
            cout << "✗ Member or book not found.\n";
            return false;
        }

        // Check if member borrowed this book
        auto borrowed = member->getBorrowedBooks();
        if (find(borrowed.begin(), borrowed.end(), bookID) == borrowed.end()) {
            cout << "✗ Member did not borrow this book.\n";
            return false;
        }

        // Execute return
        member->returnBook(bookID);
        book->increaseAvailableCopies();
        book->setStatus(BookStatus::AVAILABLE);

        // Check for late return and add fine
        double fine = 5.0;  // Simulation: assume book was returned late
        if (fine > 0) {
            member->addFine(fine);
            cout << "⚠ Late fee applied: $" << fine << "\n";
        }

        Transaction trans("T" + to_string(transactions.size() + 1),
                         memberID, bookID, TransactionType::RETURN);
        trans.setAmount(fine);
        trans.markAsCompleted();
        transactions.push_back(trans);

        cout << "✓ Book returned successfully!\n";
        return true;
    }

    // ========== RESERVATION OPERATIONS ==========
    bool reserveBook(const string& memberID, const string& bookID) {
        cout << "\n--- RESERVATION OPERATION ---\n";

        Member* member = findMember(memberID);
        Book* book = findBook(bookID);

        if (!member || !book) {
            cout << "✗ Member or book not found.\n";
            return false;
        }

        if (book->getAvailableCopies() > 0) {
            cout << "✗ Book is available. Please borrow instead of reserving.\n";
            return false;
        }

        // Add to reservation queue
        member->reserveBook(bookID);
        reservationQueues[bookID].addMemberToQueue(memberID);

        Transaction trans("T" + to_string(transactions.size() + 1),
                         memberID, bookID, TransactionType::RESERVATION);
        trans.markAsCompleted();
        transactions.push_back(trans);

        return true;
    }

    // ========== FINE OPERATIONS ==========
    void payFine(const string& memberID, double amount) {
        cout << "\n--- FINE PAYMENT ---\n";

        Member* member = findMember(memberID);
        if (!member) {
            cout << "✗ Member not found.\n";
            return;
        }

        member->payFine(amount);

        Transaction trans("T" + to_string(transactions.size() + 1),
                         memberID, "", TransactionType::FINE_PAYMENT);
        trans.setAmount(amount);
        trans.markAsCompleted();
        transactions.push_back(trans);
    }

    // ========== REPORT GENERATION ==========
    void generateReports() {
        // Update report with current data
        for (const auto& [id, book] : books) {
            report.addBookToReport(book);
        }
        for (const auto& [id, member] : members) {
            report.addMemberToReport(member);
        }
        for (const auto& trans : transactions) {
            report.addTransactionToReport(trans);
        }

        report.generateInventoryReport();
        report.generateMembershipReport();
        report.generateTransactionReport();
    }

    // ========== STATISTICS ==========
    void displayStatistics() const {
        cout << "\n╔════════════════════════════════════════════════════╗\n";
        cout << "║          LIBRARY STATISTICS                        ║\n";
        cout << "╚════════════════════════════════════════════════════╝\n\n";

        int totalBorrows = 0;
        int totalReturns = 0;
        double totalFinesCollected = 0.0;

        for (const auto& trans : transactions) {
            if (trans.getType() == TransactionType::BORROW) totalBorrows++;
            else if (trans.getType() == TransactionType::RETURN) totalReturns++;
            else if (trans.getType() == TransactionType::FINE_PAYMENT) 
                totalFinesCollected += trans.getAmount();
        }

        cout << "Total Books in System: " << books.size() << "\n";
        cout << "Total Members: " << members.size() << "\n";
        cout << "Total Transactions: " << transactions.size() << "\n";
        cout << "  • Borrows: " << totalBorrows << "\n";
        cout << "  • Returns: " << totalReturns << "\n";
        cout << "  • Fines Collected: $" << fixed << setprecision(2) 
             << totalFinesCollected << "\n";
    }
};

// ============================================================================
// DEMONSTRATION
// ============================================================================

int main() {
    LibraryManagementSystem library;

    // ========== ADD BOOKS ==========
    cout << "\n--- ADDING BOOKS TO LIBRARY ---\n";
    LibraryManagementSystem::Book book1("B001", "The C++ Programming Language", 
                                        "Bjarne Stroustrup", "ISBN001", 2013,
                                        LibraryManagementSystem::BookCategory::TECHNOLOGY, 
                                        85.99, 5, "Shelf A1");
    LibraryManagementSystem::Book book2("B002", "Clean Code",
                                        "Robert C. Martin", "ISBN002", 2008,
                                        LibraryManagementSystem::BookCategory::TECHNOLOGY,
                                        42.99, 3, "Shelf A2");
    LibraryManagementSystem::Book book3("B003", "1984",
                                        "George Orwell", "ISBN003", 1949,
                                        LibraryManagementSystem::BookCategory::FICTION,
                                        15.99, 4, "Shelf B1");
    LibraryManagementSystem::Book book4("B004", "Sapiens",
                                        "Yuval Noah Harari", "ISBN004", 2014,
                                        LibraryManagementSystem::BookCategory::HISTORY,
                                        25.99, 2, "Shelf C1");

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    library.addBook(book4);

    // ========== REGISTER MEMBERS ==========
    cout << "\n--- REGISTERING MEMBERS ---\n";
    LibraryManagementSystem::Member member1("M001", "Alice Johnson", "alice@email.com",
                                            "555-0101", LibraryManagementSystem::MembershipType::PREMIUM);
    LibraryManagementSystem::Member member2("M002", "Bob Smith", "bob@email.com",
                                            "555-0102", LibraryManagementSystem::MembershipType::STANDARD);
    LibraryManagementSystem::Member member3("M003", "Charlie Brown", "charlie@email.com",
                                            "555-0103", LibraryManagementSystem::MembershipType::STUDENT);

    library.registerMember(member1);
    library.registerMember(member2);
    library.registerMember(member3);

    // ========== DISPLAY CATALOG ==========
    library.displayAllBooks();
    library.displayAllMembers();

    // ========== PERFORM TRANSACTIONS ==========
    cout << "\n" << string(70, '=') << "\n";
    cout << "PERFORMING LIBRARY TRANSACTIONS\n";
    cout << string(70, '=') << "\n";

    // Borrowing
    library.borrowBook("M001", "B001");
    library.borrowBook("M001", "B002");
    library.borrowBook("M002", "B003");
    library.borrowBook("M003", "B004");

    // Try to borrow more than limit
    library.borrowBook("M003", "B001");  // Should fail - student limit is 2

    // ========== RETURN BOOKS ==========
    library.returnBook("M001", "B001");
    library.returnBook("M002", "B003");

    // ========== PAY FINES ==========
    library.payFine("M001", 5.00);

    // ========== RESERVATION ==========
    library.reserveBook("M002", "B001");

    // ========== DISPLAY RESULTS ==========
    cout << "\n" << string(70, '=') << "\n";
    cout << "UPDATED LIBRARY STATUS\n";
    cout << string(70, '=') << "\n";

    library.displayAllMembers();
    library.displayAllBooks();
    library.displayStatistics();
    library.generateReports();

    cout << "\n" << string(70, '=') << "\n";
    cout << "LIBRARY MANAGEMENT SYSTEM - END OF DEMONSTRATION\n";
    cout << string(70, '=') << "\n\n";

    return 0;
}

#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <chrono>
#include <memory>

using namespace std;

// ============================================================================
// SINGLETON PATTERN - COMPREHENSIVE GUIDE
// ============================================================================
// The Singleton Pattern is a creational design pattern that restricts
// the instantiation of a class to a single object.
//
// Key Characteristics:
// 1. Private Constructor - Prevent external instantiation
// 2. Static Instance - Store the single object
// 3. Static Method (getInstance) - Return the single instance
// 4. Delete Copy Operations - Prevent copying the singleton
//
// Benefits:
// ✓ Global point of access to unique resource
// ✓ Controlled object creation
// ✓ Thread-safe access (with proper implementation)
// ✓ Lazy initialization (object created on first use)
//
// Use Cases:
// ✓ Database connections
// ✓ Logging services
// ✓ Configuration managers
// ✓ Thread pools
// ============================================================================

// ============================================================================
// EXAMPLE 1: BASIC SINGLETON (Not Thread-Safe)
// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "EXAMPLE 1: BASIC SINGLETON (Simple, but Not Thread-Safe)\n";
cout << string(70, '=') << "\n\n";

class BasicLogger {
private:
    // Static pointer to hold the single instance
    static BasicLogger* instance;
    
    // Private constructor - Can't be called from outside
    BasicLogger() {
        cout << "✓ BasicLogger Constructor: Created logger instance\n";
    }

public:
    // Delete copy constructor - Prevent copying
    BasicLogger(const BasicLogger&) = delete;
    
    // Delete copy assignment - Prevent assignment
    BasicLogger& operator=(const BasicLogger&) = delete;

    // Static method to get the single instance
    // Called getInstance() every time you need the logger
    static BasicLogger* getInstance() {
        if (instance == nullptr) {
            instance = new BasicLogger();  // Create instance on first call
        }
        return instance;
    }

    void log(const string& message) {
        cout << "[LOG] " << message << "\n";
    }

    ~BasicLogger() {
        cout << "✗ BasicLogger Destructor: Logger destroyed\n";
    }
};

// Initialize static member outside the class
BasicLogger* BasicLogger::instance = nullptr;

// ============================================================================
// EXAMPLE 2: THREAD-SAFE SINGLETON (With Mutex)
// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "EXAMPLE 2: THREAD-SAFE SINGLETON (With Mutex/Lock)\n";
cout << string(70, '=') << "\n\n";

class ThreadSafeLogger {
private:
    static ThreadSafeLogger* instance;
    static mutex mtx;  // Mutex for thread synchronization
    
    int logCount;

    ThreadSafeLogger() : logCount(0) {
        cout << "✓ ThreadSafeLogger Constructor: Created logger\n";
    }

public:
    ThreadSafeLogger(const ThreadSafeLogger&) = delete;
    ThreadSafeLogger& operator=(const ThreadSafeLogger&) = delete;

    // Thread-safe getInstance with mutex lock
    // Double-checked locking pattern
    static ThreadSafeLogger* getInstance() {
        if (instance == nullptr) {  // First check (without lock) - faster
            mtx.lock();              // Acquire lock
            if (instance == nullptr) {  // Second check (with lock) - safe
                instance = new ThreadSafeLogger();
            }
            mtx.unlock();            // Release lock
        }
        return instance;
    }

    void log(const string& message) {
        logCount++;
        cout << "[Log #" << logCount << "] " << message << "\n";
    }

    int getLogCount() const {
        return logCount;
    }

    ~ThreadSafeLogger() {
        cout << "✗ ThreadSafeLogger Destructor: Logger destroyed (Total logs: " 
             << logCount << ")\n";
    }
};

ThreadSafeLogger* ThreadSafeLogger::instance = nullptr;
mutex ThreadSafeLogger::mtx;

// ============================================================================
// EXAMPLE 3: MEYERS' SINGLETON (Thread-Safe, Modern C++11)
// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "EXAMPLE 3: MEYERS' SINGLETON (Best Practice - C++11)\n";
cout << "Note: Static local variables are thread-safe in C++11\n";
cout << string(70, '=') << "\n\n";

class MeyersSingleton {
private:
    int instanceNumber;
    
    // Private constructor
    MeyersSingleton() : instanceNumber(0) {
        cout << "✓ MeyersSingleton Constructor: Created instance #" 
             << (++instanceNumber) << "\n";
    }

public:
    MeyersSingleton(const MeyersSingleton&) = delete;
    MeyersSingleton& operator=(const MeyersSingleton&) = delete;

    // Static local variable is initialized only once
    // Thread-safe guaranteed by C++ standard (magic statics)
    static MeyersSingleton& getInstance() {
        static MeyersSingleton instance;  // Created only once
        return instance;
    }

    void doSomething() {
        cout << "✓ MeyersSingleton doing something\n";
    }

    ~MeyersSingleton() {
        cout << "✗ MeyersSingleton Destructor: Cleaned up\n";
    }
};

// ============================================================================
// EXAMPLE 4: SMART POINTER SINGLETON (Modern C++)
// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "EXAMPLE 4: SMART POINTER SINGLETON (Automatic Memory Management)\n";
cout << string(70, '=') << "\n\n";

class SmartSingleton {
private:
    static unique_ptr<SmartSingleton> instance;
    static mutex mtx;
    
    string resourceName;

    SmartSingleton(const string& name = "DefaultResource") 
        : resourceName(name) {
        cout << "✓ SmartSingleton Constructor: Created with resource \"" 
             << resourceName << "\"\n";
    }

public:
    SmartSingleton(const SmartSingleton&) = delete;
    SmartSingleton& operator=(const SmartSingleton&) = delete;

    // Returns reference to the singleton (safer than raw pointer)
    static SmartSingleton& getInstance() {
        if (!instance) {
            lock_guard<mutex> lock(mtx);  // RAII lock
            if (!instance) {
                instance = make_unique<SmartSingleton>("ManagedResource");
            }
        }
        return *instance;
    }

    string getResourceName() const {
        return resourceName;
    }

    void useResource() {
        cout << "✓ Using resource: " << resourceName << "\n";
    }

    ~SmartSingleton() {
        cout << "✗ SmartSingleton Destructor: Destroyed \"" 
             << resourceName << "\" (auto-cleaned)\n";
    }
};

unique_ptr<SmartSingleton> SmartSingleton::instance = nullptr;
mutex SmartSingleton::mtx;

// ============================================================================
// EXAMPLE 5: REAL-WORLD SINGLETON - DATABASE CONNECTION
// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "EXAMPLE 5: REAL-WORLD - DATABASE CONNECTION POOL\n";
cout << string(70, '=') << "\n\n";

class DatabaseConnection {
private:
    static DatabaseConnection* instance;
    static mutex mtx;
    
    string connectionString;
    bool isConnected;
    int queryCount;

    // Private constructor - Initialize connection
    DatabaseConnection() : isConnected(false), queryCount(0) {
        connectionString = "mysql://localhost:3306/mydb";
        cout << "✓ DatabaseConnection: Initializing connection to " 
             << connectionString << "\n";
        isConnected = true;
    }

public:
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;

    // Thread-safe singleton getter
    static DatabaseConnection* getInstance() {
        if (instance == nullptr) {
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr) {
                instance = new DatabaseConnection();
            }
        }
        return instance;
    }

    // Execute a query using the shared connection
    void executeQuery(const string& query) {
        if (isConnected) {
            queryCount++;
            cout << "✓ Query #" << queryCount << " executed: " << query << "\n";
        } else {
            cout << "✗ Error: Database not connected\n";
        }
    }

    // Get connection status
    bool checkConnection() const {
        return isConnected;
    }

    // Get total queries executed
    int getTotalQueries() const {
        return queryCount;
    }

    // Close connection
    void closeConnection() {
        if (isConnected) {
            cout << "✓ Closing database connection after " << queryCount 
                 << " queries\n";
            isConnected = false;
        }
    }

    ~DatabaseConnection() {
        closeConnection();
        cout << "✗ DatabaseConnection Destructor: Connection destroyed\n";
    }
};

DatabaseConnection* DatabaseConnection::instance = nullptr;
mutex DatabaseConnection::mtx;

// ============================================================================
// EXAMPLE 6: REAL-WORLD SINGLETON - CONFIGURATION MANAGER
// ============================================================================
cout << "\n" << string(70, '=') << "\n";
cout << "EXAMPLE 6: REAL-WORLD - CONFIGURATION MANAGER\n";
cout << string(70, '=') << "\n\n";

class ConfigManager {
private:
    static ConfigManager* instance;
    
    // Configuration data
    map<string, string> configs;

    ConfigManager() {
        cout << "✓ ConfigManager: Loading configuration\n";
        
        // Simulate loading config from file
        configs["app.name"] = "MyApplication";
        configs["app.version"] = "1.0.0";
        configs["database.host"] = "localhost";
        configs["database.port"] = "3306";
        configs["debug.mode"] = "false";
    }

public:
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    static ConfigManager* getInstance() {
        if (instance == nullptr) {
            instance = new ConfigManager();
        }
        return instance;
    }

    // Get configuration value
    string getConfig(const string& key) {
        if (configs.find(key) != configs.end()) {
            return configs[key];
        }
        return "NOT_FOUND";
    }

    // Set configuration value
    void setConfig(const string& key, const string& value) {
        configs[key] = value;
        cout << "✓ Config updated: " << key << " = " << value << "\n";
    }

    // Display all configurations
    void displayAllConfigs() {
        cout << "Current Configuration:\n";
        for (const auto& [key, value] : configs) {
            cout << "  " << key << " : " << value << "\n";
        }
    }

    ~ConfigManager() {
        cout << "✗ ConfigManager Destructor: Saved configuration\n";
    }
};

ConfigManager* ConfigManager::instance = nullptr;

// ============================================================================
// DEMONSTRATION SCENARIOS
// ============================================================================

void demonstrateBasicSingleton() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "SCENARIO: Basic Singleton Usage\n";
    cout << string(70, '-') << "\n\n";

    // Get instance - created for first time
    BasicLogger* logger1 = BasicLogger::getInstance();
    logger1->log("First message");

    // Get instance again - returns same instance
    BasicLogger* logger2 = BasicLogger::getInstance();
    logger2->log("Second message");

    // Verify same instance
    cout << "\nAre they the same instance? " 
         << (logger1 == logger2 ? "YES (Correct!)" : "NO (Wrong!)") << "\n";

    // Try to copy (will fail at compile time)
    // BasicLogger logger3 = *logger1;  // ← Compile error: copy constructor deleted
}

void demonstrateThreadSafeSingleton() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "SCENARIO: Thread-Safe Singleton (Multi-threaded)\n";
    cout << string(70, '-') << "\n\n";

    ThreadSafeLogger* logger = ThreadSafeLogger::getInstance();

    // Simulate multiple threads accessing the singleton
    auto logInThread = [](int threadId) {
        for (int i = 0; i < 2; i++) {
            ThreadSafeLogger* logger = ThreadSafeLogger::getInstance();
            string msg = "Message from thread " + to_string(threadId);
            logger->log(msg);
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    };

    thread t1(logInThread, 1);
    thread t2(logInThread, 2);
    thread t3(logInThread, 3);

    t1.join();
    t2.join();
    t3.join();

    cout << "\nTotal logs recorded: " << logger->getLogCount() << "\n";
}

void demonstrateMeyersSingleton() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "SCENARIO: Meyers' Singleton (Modern C++)\n";
    cout << string(70, '-') << "\n\n";

    // First access - creates instance
    MeyersSingleton& instance1 = MeyersSingleton::getInstance();
    instance1.doSomething();

    // Second access - returns same instance
    MeyersSingleton& instance2 = MeyersSingleton::getInstance();
    instance2.doSomething();

    cout << "\nSame instance? " 
         << (&instance1 == &instance2 ? "YES" : "NO") << "\n";
}

void demonstrateSmartSingleton() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "SCENARIO: Smart Pointer Singleton\n";
    cout << string(70, '-') << "\n\n";

    SmartSingleton& singleton1 = SmartSingleton::getInstance();
    cout << "Resource: " << singleton1.getResourceName() << "\n";
    singleton1.useResource();

    SmartSingleton& singleton2 = SmartSingleton::getInstance();
    singleton2.useResource();
}

void demonstrateDatabaseSingleton() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "SCENARIO: Real-World - Database Connection\n";
    cout << string(70, '-') << "\n\n";

    // Get database connection (creates once)
    DatabaseConnection* db = DatabaseConnection::getInstance();
    
    cout << "Connection Status: " << (db->checkConnection() ? "Connected" : "Disconnected") << "\n\n";

    // Execute multiple queries using same connection
    db->executeQuery("SELECT * FROM users");
    db->executeQuery("INSERT INTO logs VALUES (...)");
    db->executeQuery("UPDATE users SET status = 'active'");
    db->executeQuery("DELETE FROM temp_data");

    // Get same instance elsewhere
    DatabaseConnection* db2 = DatabaseConnection::getInstance();
    cout << "\nSame database connection? " 
         << (db == db2 ? "YES (All queries on same connection!)" : "NO") << "\n";
    
    cout << "Total queries through singleton: " << db2->getTotalQueries() << "\n";
}

void demonstrateConfigManager() {
    cout << "\n" << string(70, '-') << "\n";
    cout << "SCENARIO: Real-World - Configuration Manager\n";
    cout << string(70, '-') << "\n\n";

    // Get config instance
    ConfigManager* config = ConfigManager::getInstance();
    
    cout << "App Name: " << config->getConfig("app.name") << "\n";
    cout << "App Version: " << config->getConfig("app.version") << "\n";
    cout << "Database Host: " << config->getConfig("database.host") << "\n";

    cout << "\n";
    config->displayAllConfigs();

    cout << "\nUpdating configuration...\n";
    config->setConfig("debug.mode", "true");
    config->setConfig("database.host", "remote.server.com");

    cout << "\nUpdated Configurations:\n";
    config->displayAllConfigs();

    // Verify same instance from different location
    ConfigManager* config2 = ConfigManager::getInstance();
    cout << "\nSame ConfigManager instance? " 
         << (config == config2 ? "YES" : "NO") << "\n";
}

void compareSingletonApproaches() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "COMPARISON OF SINGLETON APPROACHES\n";
    cout << string(70, '=') << "\n\n";

    cout << "1. BASIC SINGLETON (Pointer-based)\n";
    cout << "   ✓ Simple implementation\n";
    cout << "   ✓ Manual memory management (manually delete)\n";
    cout << "   ✗ NOT thread-safe by default\n";
    cout << "   ✗ Memory leak if not deleted\n\n";

    cout << "2. THREAD-SAFE SINGLETON (With Mutex)\n";
    cout << "   ✓ Thread-safe\n";
    cout << "   ✓ Double-checked locking pattern\n";
    cout << "   ✗ More complex code\n";
    cout << "   ✗ Potential lock overhead\n\n";

    cout << "3. MEYERS' SINGLETON (Static local variable)\n";
    cout << "   ✓ Thread-safe (guaranteed by C++11 standard)\n";
    cout << "   ✓ Elegant and simple\n";
    cout << "   ✓ Automatic cleanup when program ends\n";
    cout << "   ✓ RECOMMENDED for most cases\n\n";

    cout << "4. SMART POINTER SINGLETON (unique_ptr)\n";
    cout << "   ✓ Automatic memory management\n";
    cout << "   ✓ Thread-safe with smart pointers\n";
    cout << "   ✓ Modern C++ approach\n";
    cout << "   ✓ No manual delete needed\n\n";

    cout << "BEST PRACTICE: Use Meyers' Singleton (Example 3)\n";
    cout << "Reason: Simple, safe, automatic cleanup\n";
}

int main() {
    cout << "\n";
    cout << "╔" << string(68, '═') << "╗\n";
    cout << "║" << string(15, ' ') << "SINGLETON PATTERN - COMPREHENSIVE GUIDE" << string(13, ' ') << "║\n";
    cout << "╚" << string(68, '═') << "╝\n";

    // Run all demonstrations
    demonstrateBasicSingleton();
    demonstrateThreadSafeSingleton();
    demonstrateMeyersSingleton();
    demonstrateSmartSingleton();
    demonstrateDatabaseSingleton();
    demonstrateConfigManager();
    compareSingletonApproaches();

    cout << "\n" << string(70, '=') << "\n";
    cout << "KEY POINTS:\n";
    cout << string(70, '=') << "\n";
    cout << "✓ Singleton ensures only ONE instance exists\n";
    cout << "✓ Private constructor prevents external instantiation\n";
    cout << "✓ getInstance() provides global access point\n";
    cout << "✓ Delete copy/move operations prevent duplication\n";
    cout << "✓ Meyers' Singleton is the recommended modern approach\n";
    cout << "✓ Use cases: DB connections, loggers, config managers\n";
    cout << string(70, '=') << "\n\n";

    return 0;
}

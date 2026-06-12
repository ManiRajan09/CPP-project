#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// Callback function to handle CURL response data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to fetch joke from external API
string fetchJokeFromAPI() {
    CURL* curl = curl_easy_init();
    
    if (!curl) {
        cerr << "Error: Could not initialize CURL\n";
        return "";
    }

    string readBuffer;
    const char* url = "https://official-joke-api.appspot.com/random_joke";

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        cerr << "Error: CURL request failed: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
        return "";
    }

    curl_easy_cleanup(curl);
    return readBuffer;
}

// Function to parse JSON response and extract joke
string parseJokeResponse(const string& jsonResponse) {
    try {
        json jokeData = json::parse(jsonResponse);

        string setup = jokeData["setup"].get<string>();
        string punchline = jokeData["punchline"].get<string>();
        string jokeType = jokeData["type"].get<string>();

        return setup + "\n" + punchline + "\n[Type: " + jokeType + "]";
    } catch (const exception& e) {
        cerr << "Error parsing JSON: " << e.what() << "\n";
        return "";
    }
}

// Main function to generate and display a random joke
void generateRandomJoke() {
    cout << "Fetching a random joke from API...\n\n";

    string response = fetchJokeFromAPI();

    if (response.empty()) {
        cout << "Failed to fetch joke. Please check your internet connection.\n";
        return;
    }

    string joke = parseJokeResponse(response);

    if (joke.empty()) {
        cout << "Failed to parse joke data.\n";
        return;
    }

    cout << "========== RANDOM JOKE ==========\n";
    cout << joke << "\n";
    cout << "================================\n";
}

int main() {
    cout << "=== Random Joke Generator ===\n\n";

    int choice;
    do {
        generateRandomJoke();

        cout << "\nWould you like another joke?\n";
        cout << "1. Yes\n";
        cout << "2. No (Exit)\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n";
            continue;
        } else if (choice == 2) {
            cout << "Thanks for using Joke Generator! Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (true);

    return 0;
}

/**
 * @file DataStorage.h
 * @brief Contains the declaration of the PasswordKeeper class and its member functions.
 */

#include "DataStorage.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

/**
 * @class PasswordKeeper
 * @brief Manages password storage and operations.
 */

PasswordKeeper::PasswordKeeper() : PasswordKeeper("Login"){}

/**
     * @brief Constructor.
     * Initializes a PasswordKeeper object with the specified source file path.
     * @param filePath The path of the source file to load passwords from.
     */

PasswordKeeper::PasswordKeeper(const string& filePath) {
    sourceFilePath = filePath;
    encryptionKey = 10;
    loadPasswordsFromFile();
}

/**
 * @brief Destructor.
 * Saves the passwords to the source file before destroying the PasswordKeeper object.
 */

PasswordKeeper::~PasswordKeeper() {
    savePasswordsToFile();
}

// ADD PASSWORD
/**
     * @brief Adds a new password entry to the storage.
     * @param name The name of the password entry.
     * @param passwordText The password text.
     * @param category The category of the password entry.
     * @param website The website associated with the password entry.
     * @param login The login associated with the password entry.
     */

void PasswordKeeper::addPassword(const string& name, const string& passwordText, const string& category,
                                  const string& website, const string& login) {
    for (const auto& entry : passwords) {
        if (entry.name == name &&
            entry.password == passwordText &&
            entry.category == category &&
            entry.website == website &&
            entry.login == login) {
            cout << "This Password Entry Already Exists.\n";
            return;
        }
    }
    ofstream outputFile("My_Password", ios::app);

    if (!outputFile) {
        cerr << "Error: Opening The File!" << endl;
        return;
    }

    outputFile << "Name: " << name << endl
               << "Password: " << passwordText << endl
               << "Category: " << category << endl;

    if (!website.empty()) {
        outputFile << "Website: " << website << endl;
    }

    if (!login.empty()) {
        outputFile << "Login: " << login << endl;
    }

    outputFile << "----------" << endl;
    outputFile.close();

    auto it = find_if(passwords.begin(), passwords.end(), [&name](const KeyData& entry) {
        return entry.name == name;
    });

    if (it != passwords.end()) {
        it->password = passwordText;
        it->category = category;
        it->website = website;
        it->login = login;
        cout << "Password Entry Updated Successfully!\n";
    } else {
        // Add new password entry to the in-memory storage
        KeyData entry = {name, passwordText, category, website, login};
        passwords.push_back(entry);
        cout << "Password Entry Added Successfully!\n";
    }
}

// GENERATE PASSWORD
/**
     * @brief Generates a random password.
     * @param length The length of the generated password.
     * @param useUpper Flag indicating whether to use uppercase letters.
     * @param useLower Flag indicating whether to use lowercase letters.
     * @param useSpecial Flag indicating whether to use special characters.
     * @return The generated password.
     */

string PasswordKeeper::generatePassword(int length, bool useUpper, bool useLower, bool useSpecial) {
    string allowedChars = "";
    string password = "";

    if (useUpper) {
        allowedChars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }

    if (useLower) {
        allowedChars += "abcdefghijklmnopqrstuvwxyz";
    }

    if (useSpecial) {
        allowedChars += "!@#$%^&*()_+-=[]{}|;:,.<>?/";
    }

    srand(time(nullptr));
    for (int i = 0; i < length; i++) {
        int index = rand() % allowedChars.size();
        password += allowedChars[index];
    }
    return password;
}

// EDIT PASSWORD
/**
     * @brief Edits the password for the specified entry name.
     * @param name The name of the password entry.
     * @param newPassword The new password.
     */

void PasswordKeeper::editPassword(const string& name, const string& newPassword) {
    auto it = find_if(passwords.begin(), passwords.end(), [&name](const KeyData& entry) {
        return entry.name == name;
    });

    if (it != passwords.end()) {
        it->password = newPassword;
        cout << "Password Updated Successfully!" << endl;
    } else {
        cout << "Password Entry Not Found." << endl;
    }
}

// DELETE PASSWORD
/**
    * @brief Deletes the password entry with the specified name.
    * @param name The name of the password entry to delete.
    */

void PasswordKeeper::deletePassword(const string& name) {
    for (auto it = passwords.begin(); it != passwords.end(); ++it) {
        if (it->name == name) {
            passwords.erase(it);
            savePasswordsToFile();
            cout << "Password '" << name << "' Has Been Deleted.\n";
            return;
        }
    }
    cout << "Password '" << name << "' Not Found.\n";
}

// DELETE ALL PASSWORD
/**
     * @brief Deletes all password entries.
     */

void PasswordKeeper::deleteAllPasswords() {
    passwords.clear();
    savePasswordsToFile();
    cout << "All Passwords Have Been Deleted.\n";
}

// LOAD PASSWORD
/**
    * @brief Loads the passwords from the source file.
    */

void PasswordKeeper::loadPasswordsFromFile() {
    ifstream inputFile(sourceFilePath);

    if (!inputFile) {
        cerr << "Error Opening The File!" << endl;
        return;
    }

    string line;
    KeyData entry;
    while (getline(inputFile, line)) {
        if (line.find("Name: ") == 0) {
            entry.name = line.substr(6);
        } else if (line.find("Password: ") == 0) {
            entry.password = line.substr(10);
        } else if (line.find("Category: ") == 0) {
            entry.category = line.substr(10);
        } else if (line.find("Website: ") == 0) {
            entry.website = line.substr(9);
        } else if (line.find("Login: ") == 0) {
            entry.login = line.substr(7);
        } else if (line == "----------") {
            passwords.push_back(entry);
            entry = KeyData();
        }
    }
    inputFile.close();
}

// GET PASSWORD
/**
     * @brief Retrieves the stored passwords.
     * @return A reference to the vector containing the stored passwords.
     */

vector<KeyData>& PasswordKeeper::getPasswords() {
    return passwords;
}

// SAVE PASSWORD
/**
     * @brief Saves the passwords to the source file.
     */

void PasswordKeeper::savePasswordsToFile() {
    ofstream outputFile(sourceFilePath);
    if (!outputFile) {
        cerr << "Error Opening The File" << endl;
        return;
    }

    // Save the passwords to the file
    for (const auto& entry : passwords) {
        outputFile << "Name: " << entry.name << endl;
        outputFile << "Password: " << entry.password << endl;
        outputFile << "Category: " << entry.category << endl;
        outputFile << "Website: " << entry.website << endl;
        outputFile << "Login: " << entry.login << endl;
        outputFile << "----------" << endl;
    }

    // Get the current timestamp
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%d/%m/%Y %H:%M:%S", localTime);

    // Save the timestamp in a separate line
    outputFile << "Timestamp: " << timestamp << endl;

    outputFile.close();
}

// SEARCH PASSWORD
/**
     * @brief Searches for password entries matching the specified query.
     * @param query The search query.
     * @return A vector of KeyData entries matching the search query.
     */

vector<KeyData> PasswordKeeper::searchPasswords(const string& query) {
    vector<KeyData> results;

    for (const KeyData& entry : passwords) {
        if (entry.name.find(query) != string::npos ||
            entry.category.find(query) != string::npos ||
            entry.website.find(query) != string::npos ||
            entry.login.find(query) != string::npos ||
            entry.password.find(query) != string::npos) { // Search by password as well

            results.push_back(entry);
        }
    }
    return results;
}

// SORT PASSWORD
/**
     * @brief Sorts the passwords based on the specified criteria.
     * @param sortBy The sort criteria ("name" or "category").
     */

void PasswordKeeper::sortPasswords(const string& sortBy) {
    vector<KeyData>& passwordList = getPasswords();

    if (sortBy == "name") {
        sort(passwordList.begin(), passwordList.end(), [](const KeyData& a, const KeyData& b) {
            return a.name < b.name;
        });
    } else if (sortBy == "category") {
        sort(passwordList.begin(), passwordList.end(), [](const KeyData& a, const KeyData& b) {
            return a.category < b.category;
        });
    } else {
        cout << "Invalid Sort Criteria.\n";
        return;
    }

    cout << "Sorted Passwords:\n";
    for (const auto& entry : passwordList) {
        cout << "Name: " << entry.name << endl;
        cout << "Password: " << entry.password << endl;
        cout << "Category: " << entry.category << endl;
        cout << "Website: " << entry.website << endl;
        cout << "Login: " << entry.login << endl;
        cout << "----------\n";
    }
}

// ENCRYPT PASSWORD
/**
    * @brief Encrypts the specified password.
    * @param password The password to encrypt.
    * @return The encrypted password.
    */

string PasswordKeeper::encrypt(const string& password) {
    string encryptedPassword = password;

    for (char& i : encryptedPassword) {
        i ^= encryptionKey;
    }
    return encryptedPassword;
}

//ENCRYPT ALL PASSWORD
/**
     * @brief Encrypts all passwords and saves them to the source file.
     */

void PasswordKeeper::encryptAllPasswords() {
    for (auto& entry : passwords) {
        entry.password = encrypt(entry.password);
    }
    savePasswordsToFile();
    cout << "All Passwords Have Been Encrypted And Saved To File.\n";
}

// DECRYPT
/**
     * @brief Decrypts the specified encrypted password.
     * @param encryptedPassword The encrypted password.
     * @return The decrypted password.
     */

string PasswordKeeper::decrypt(const string& encryptedPassword) {
    string decryptedPassword = encryptedPassword;

    for (char& i : decryptedPassword) {
        i ^= encryptionKey;
    }
    return decryptedPassword;
}

// DECRYPT ALL PASSWORD
/**
     * @brief Decrypts all passwords and saves them to the source file.
     */

void PasswordKeeper::decryptAllPasswords() {
    for (auto& entry : passwords) {
        entry.password = decrypt(entry.password);
    }
    savePasswordsToFile();
    cout << "All Passwords Have Been Decrypted And Saved To File.\n";
}

// ADD CATEGORY
/**
 * @brief Adds a new category to the password storage.
 * @param categoryName The name of the category to add.
 */

void PasswordKeeper::addCategory(const string& categoryName) {
    for (const auto& entry : passwords) {
        if (entry.category == categoryName) {
            cout << "Category '" << categoryName << "' Already Exists.\n";
            return;
        }
    }
    KeyData categoryEntry;
    categoryEntry.category = categoryName;

    passwords.push_back(categoryEntry);

    cout << "Category '" << categoryName << "' Added Successfully!\n";
}

// DELETE CATEGORY

/**
 * @brief Deletes the specified category from the password storage.
 * @param categoryName The name of the category to delete.
 */

void PasswordKeeper::deleteCategory(const string& categoryName) {
    bool categoryFound = false;

    for (auto it = passwords.begin(); it != passwords.end(); ) {
        if (it->category == categoryName) {
            it = passwords.erase(it);
            categoryFound = true;
        } else {
            ++it;
        }
    }

    if (categoryFound) {
        cout << "Category '" << categoryName << "' Deleted Successfully!\n";
    } else {
        cout << "Category '" << categoryName << "' Not Found.\n";
    }
}

// SELECT SOURCE FILE
/**
     * @brief Prompts the user to select a source file for password storage.
     */

void PasswordKeeper::selectSourceFile() {
    string filePath;
    cout << "Enter The Path Of The Source File: ";
    getline(cin, filePath);

    // Check if the file exists and is accessible
    ifstream inputFile(filePath);
    if (!inputFile) {
        cout << "Error: Unable To Open The Source File." << endl;
        return ;
    }

    sourceFilePath = filePath;

    // Read the file content
    string fileContent((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    // Save the timestamp
    ofstream outputFile("Timestamps", ios::app);
    if (outputFile.is_open()) {
        time_t now = time(nullptr);
        tm* localTime = localtime(&now);

        ostringstream oss;
        oss << put_time(localTime, "%d/%m/%Y %H:%M:%S");
        string formattedTime = oss.str();

        outputFile << "Encryption/Decryption Attempt At: " << formattedTime << " - File: " << filePath << endl;
        outputFile.close();

        cout << "File Decrypted Successfully." << endl;
    } else {
        cout << "Error: Failed To Open The Timestamps File." << endl;
    }
}
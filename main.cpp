/**
 * @file main.cpp
 * @brief Main file for the password management system.
 */

#include "DataStorage.h"
#include <iostream>
#include <string>
#define COLOR_MENU "\033[1;35m"
using namespace std;

/**
 * @brief Enum representing the strength of a password.
 */

enum class PasswordStrength {
    Weak,               ///< Weak password strength
    Moderate,           ///< Moderate password strength
    Strong              ///< Strong password strength
};

PasswordKeeper keeper;                      ///< Instance of the PasswordKeeper class to manage passwords
string name, category, website, login;      ///< Variables to store user input
int length, option;                         ///< Variables to store user input
bool useUpper, useLower, useSpecial;        ///< Variables to store user input

/**
 * @brief Checks the strength of a password.
 *
 * @param password The password to check.
 * @return The strength of the password as a PasswordStrength enum value.
 */

PasswordStrength checkPasswordStrength(const string& password) {
    if (password.length() >= 6) {
        bool hasUppercase = false;
        bool hasLowercase = false;
        bool hasNumber = false;

        for (char c : password) {
            if (isupper(c)) {
                hasUppercase = true;
            } else if (islower(c)) {
                hasLowercase = true;
            } else if (isdigit(c)) {
                hasNumber = true;
            }
        }
        if (hasUppercase && (hasLowercase || hasNumber)) {
            return PasswordStrength::Strong;
        } else {
            return PasswordStrength::Moderate;
        }
    } else {
        return PasswordStrength::Weak;
    }
}

/**
 * @brief Displays the main menu.
 */

void displayMainMenu() {
    cout << COLOR_MENU << "|--------------------------------------| " << endl;
    cout << "|              MAIN MENU               |" << endl;
    cout << "| (1) Search Password                  |" << endl;
    cout << "| (2) Sort Password                    |" << endl;
    cout << "| (3) Add Password                     |" << endl;
    cout << "| (4) Edit Password                    |" << endl;
    cout << "| (5) Delete Password                  |" << endl;
    cout << "| (6) Add Category                     |" << endl;
    cout << "| (7) Delete Category                  |" << endl;
    cout << "| (8) Encrypt All Passwords            |" << endl;
    cout << "| (9) Decrypt All Passwords            |" << endl;
    cout << "| (10) Exit                            |" << endl;
    cout << "|--------------------------------------|" << endl;
    cout << "=>";
}

/**
 * @brief Adds a password to the data storage.
 */

void addPassword() {
    while (true) {
        cout << "Enter The Name: ";
        cin.ignore();
        getline(cin, name);
        if (!name.empty()) {
            break;
        }
        cout << "Error: Name Field Can Not Be Left Blank. Please Try Again." << endl;
    }
    while (true) {
        cout << "Enter The Category: ";
        getline(cin, category);
        if (!category.empty()) {
            break;
        }
        cout << "Error: Category Field Can Not Be Left Blank. Please Try Again." << endl;
    }

    cout << "Enter The Website (Optional): ";
    getline(cin, website);

    cout << "Enter The Login (Optional): ";
    getline(cin, login);

    do {
        cout << "Do You Want To Generate A Password? (1: Yes, 2: No): ";
        cin >> option;
        if (option != 1 && option != 2) {
            cout << "Invalid Option. Please Try Again." << endl;
        }
    } while (option != 1 && option != 2);

    string password;
    if (option == 1) {
        cout << "Enter The Password Length: ";
        cin >> length;

        cout << "Include Uppercase Letters? (1: Yes, 0: No): ";
        cin >> useUpper;

        cout << "Include Lowercase Letters? (1: Yes, 0: No): ";
        cin >> useLower;

        cout << "Include Special Characters? (1: Yes, 0: No): ";
        cin >> useSpecial;

        if (useUpper == 0 && useLower == 0 && useSpecial == 0) {
            cout << "Error: At Least One Option (Uppercase, Lowercase, Special Characters) "
                 << "Must Be Selected For Password Generation." << endl;
            return;
        }

        if ((useUpper + useLower + useSpecial) > length) {
            cout << "Error: The Sum Of 'Use Uppercase', 'Use Lowercase', And 'Use Special Characters' "
                 << "Can Not Be Greater Than The Password Length." << endl;
            cout << "Could Not Create Password. Please Try Again." << endl;
            return;
        }

        password = keeper.generatePassword(length, useUpper, useLower, useSpecial);
        cout << "Generated Password: " << password << endl;
    } else {
        while (true) {
            cout << "Enter The Password: ";
            cin.ignore();
            getline(cin, password);
            if (!password.empty()) {
                break;
            }
            cout << "Error: Password Field Can Not Be Left Blank. Please Try Again." << endl;
        }
    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasNumber = false;

    for (char c : password) {
        if (isupper(c)) {
            hasUppercase = true;
        } else if (islower(c)) {
            hasLowercase = true;
        } else if (isdigit(c)) {
            hasNumber = true;
        }
    }

    PasswordStrength strength = checkPasswordStrength(password);

    cout << "Password Strength: ";
    if (strength == PasswordStrength::Weak) {
        cout << "Weak" << endl;
        cout << "Your Password Is Weak. Do You Want To Continue? (y/n): ";
        char choice;
        cin >> choice;
        if (tolower(choice) != 'y') {
            // Go back to the password entry loop or take appropriate action
            system("pause");
            return;
        }
        cout << "Password Added Successfully!" << endl;
    } else if (strength == PasswordStrength::Moderate) {
        cout << "Moderate" << endl;
    } else if (strength == PasswordStrength::Strong) {
        cout << "Strong" << endl;
    }

    system("pause");

    KeyData entry;
    entry.name = name;
    entry.password = password;
    entry.category = category;
    entry.website = website;
    entry.login = login;

    keeper.addPassword(name, password, category, website, login);
    cout << "Password Added Successfully!" << endl;
}

/**
 * @brief Edits an existing password.
 */

void editPassword() {
    string nameToUpdate, newPassword;
    cin.ignore();
    cout << "Enter The Name Of The Password Entry To Update: ";
    getline(cin, nameToUpdate);

    cout << "Enter The New Password: ";
    getline(cin, newPassword);

    keeper.editPassword(nameToUpdate, newPassword);
    cout << "Password Updated Successfully!" << endl;
}

/**
 * @brief Deletes a password.
 */

void deletePassword() {
    cout << "Choose An Option:\n";
    cout << "1. Delete All Passwords\n";
    cout << "2. Delete A Specific Password\n";
    cout << "Option: ";
    cin >> option;

    if (option == 1) {
        keeper.deleteAllPasswords();
        cout << "All Passwords Deleted Successfully!" << endl;
    } else if (option == 2) {
        string name;
        cin.ignore();
        cout << "Enter The Name Of The Password To Delete: ";
        getline(cin, name);
        keeper.deletePassword(name);
        cout << "Password Deleted Successfully!" << endl;
    } else {
        cout << "Invalid Option. Please Try Again.\n";
    }
}

/**
 * @brief Searches for a password.
 */

void searchPassword() {
    cout << "Search For:\n";
    cout << "1. Password\n";
    cout << "2. Category\n";
    cout << "Enter Your Choice (1-2): ";
    cin >> option;

    if (option == 1) {
        string query;
        cin.ignore();
        cout << "Enter The Password Name: ";
        getline(cin, query);

        vector<KeyData> results = keeper.searchPasswords(query);

        if (results.empty()) {
            cout << "No Passwords Found Matching The Query.\n";
        } else {
            cout << "Found " << results.size() << " Password(s) Matching The Query:\n";
            for (const auto& entry : results) {
                cout << "Name: " << entry.name << endl;
                cout << "Password: " << entry.password << endl;
                cout << "Category: " << entry.category << endl;
                cout << "Website: " << entry.website << endl;
                cout << "Login: " << entry.login << endl;
                cout << "----------\n";
            }
        }
    } else if (option == 2) {
        string query;
        cin.ignore();
        cout << "Enter The Category Name: ";
        getline(cin, query);

        vector<KeyData> results;
        for (const auto& entry : keeper.getPasswords()) {
            if (entry.category == query) {
                results.push_back(entry);
            }
        }

        if (results.empty()) {
            cout << "No Passwords Found In The Category.\n";
        } else {
            cout << "Found " << results.size() << " Password(s) In The Category:\n";
            for (const auto& entry : results) {
                cout << "Name: " << entry.name << endl;
                cout << "Password: " << entry.password << endl;
                cout << "Category: " << entry.category << endl;
                cout << "Website: " << entry.website << endl;
                cout << "Login: " << entry.login << endl;
                cout << "----------\n";
            }
        }
    } else {
        cout << "Invalid Choice.\n";
    }
}

/**
 * @brief Sorts the passwords based on the provided sorting criteria.
 */

void sortPasswords() {
    string sortBy;
    cout << "Enter The Sorting Criteria (name Or category): ";
    cin >> sortBy;

    if (sortBy == "name" || sortBy == "category") {
        keeper.sortPasswords(sortBy);
        cout << "Passwords Sorted Successfully!\n";
    } else {
        cout << "Invalid Sorting Criteria. Please Try Again.\n";
    }
    system("pause");

}

/**
 * @brief Adds a new category.
 */

void addCategory() {
    cin.ignore();
    cout << "Enter The Category Name: ";
    getline(cin, category);
    keeper.addCategory(category);
    cout << "Category Added Successfully!" << endl;
}

/**
 * @brief Deletes a category.
 */

void deleteCategory() {
    cin.ignore();
    cout << "Enter The Category Name To Delete: ";
    getline(cin, category);
    keeper.deleteCategory(category);
    cout << "Category Deleted Successfully!" << endl;
}

/**
 * @brief Calls functions from options in the menu.
 */

void processMenuSelection(int selection) {

    switch (selection) {
        case 1:
            searchPassword();
            break;
        case 2:
            sortPasswords();
            break;
        case 3:
            addPassword();
            break;
        case 4:
            editPassword();
            break;
        case 5:
            deletePassword();
            break;
        case 6:
            addCategory();
            break;
        case 7:
            deleteCategory();
            break;
        case 8:
            keeper.encryptAllPasswords();
            system("pause");
            break;
        case 9:
            keeper.decryptAllPasswords();
            system("pause");
            break;
        case 10:
            cout << "You Logged Out!" << endl;
            exit(0);
        default:
            cout << "Invalid Choice. Please try again. (1-10)" << endl;
    }
}

/**
 * @brief Clear the screen.
 */

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief The main function of the password management system.
 *
 * @return 0 indicating successful program execution.
 */

int main() {
    keeper.selectSourceFile();
    int selection;

    while (true) {
        displayMainMenu();
        cin >> selection;
        processMenuSelection(selection);
        cout << endl;

        std::cout << "Press Any Key To Continue...";
        std::cin.get();
        clearScreen();
    }
    return 0;
}
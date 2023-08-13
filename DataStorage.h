#ifndef PASSWORDMANAGER_DATASTORAGE_H
#define PASSWORDMANAGER_DATASTORAGE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>
using namespace std;

/**
 * @brief Class representing key data for a password entry.
 */

class KeyData {
public:
    string name;            /**< Name of the password. */
    string password;        /**< Password. */
    string category;        /**< Category of the password. */
    string website;         /**< Website associated with the password. */
    string login;           /**< Login associated with the password. */
    string timestamp;       /**< Timestamp of when the password was added or modified. */
};

/**
 * @brief Class representing a password keeper.
 */

class PasswordKeeper {
private:
    vector<KeyData> passwords;      /**< Vector to store all the password entries. */
    string sourceFilePath;          /**< Path to the file storing the passwords. */
    int encryptionKey;              /**< Key used for encryption/decryption. */


public:

    /**
     * @brief Default constructor for PasswordKeeper class.
     */

    PasswordKeeper();

    /**
     * @brief Constructor for PasswordKeeper class.
     * @param filePath Path to the file storing the passwords.
     */

    PasswordKeeper(const string &filePath);

    /**
    * @brief Destructor for PasswordKeeper class.
    */

    ~PasswordKeeper();

    // ADD PASSWORD
    /**
     * @brief Adds a new password entry to the password keeper.
     * @param name Name of the password.
     * @param password Password.
     * @param category Category of the password.
     * @param website Website associated with the password.
     * @param login Login associated with the password.
     */

    void addPassword(const string &name, const string &password,
                     const string &category = "",
                     const string &website = "",
                     const string &login = "");

    // GENERATE PASSWORD
    /**
     * @brief Generates a random password.
     * @param length Length of the generated password.
     * @param useUpper Whether to include uppercase letters in the generated password.
     * @param useLower Whether to include lowercase letters in the generated password.
     * @param useSpecial Whether to include special characters in the generated password.
     * @return Generated password.
     */

    string generatePassword(int length, bool useUpper, bool useLower, bool useSpecial);

    // EDIT PASSWORD
    /**
     * @brief Edits the password of a given entry.
     * @param name Name of the password entry.
     * @param newPassword New password.
     */

    void editPassword(const string &name, const string &newPassword);

    // DELETE PASSWORD
    /**
     * @brief Deletes a password entry.
     * @param name Name of the password entry to be deleted.
     */

    void deletePassword(const string &name);

    // DELETE ALL PASSWORDS
    /**
     * @brief Deletes all password entries.
     */

    void deleteAllPasswords();

    // LOAD PASSWORD
    /**
     * @brief Loads password entries from the source file.
     */

    void loadPasswordsFromFile();

    // GET PASSWORD
    /**
     * @brief Gets the vector of password entries.
     * @return Vector of password entries.
     */

    vector<KeyData> &getPasswords();

    // SAVE PASSWORD
    /**
     * @brief Saves the password entries to the source file.
     */

    void savePasswordsToFile();

    // SEARCH PASSWORD
    /**
     * @brief Searches for password entries matching a given query.
     * @param query Query string to search for.
     * @return Vector of password entries matching the query.
     */

    vector<KeyData> searchPasswords(const string &query);

    // SORT PASSWORD
    /**
     * @brief Sorts the password entries based on a given criteria.
     * @param sortBy Criteria to sort by (e.g., "name", "category", "timestamp").
     */

    void sortPasswords(const string &sortBy);

    // ENCRYPT
    /**
     * @brief Encrypts all the password entries.
     */

    void encryptAllPasswords();

    /**
     * @brief Encrypts a given password.
     * @param password Password to encrypt.
     * @return Encrypted password.
     */

    string encrypt(const string &password);

    // DECRYPT
    /**
     * @brief Decrypts all the password entries.
     */

    void decryptAllPasswords();

    /**
     * @brief Decrypts a given encrypted password.
     * @param encryptedPassword Encrypted password.
     * @return Decrypted password.
     */

    string decrypt(const string &encryptedPassword);

    // ADD CATEGORY
    /**
     * @brief Adds a new category.
     * @param categoryName Name of the category to add.
     */

    void addCategory(const string &categoryName);

    // DELETE CATEGORY
    /**
     * @brief Deletes a category.
     * @param categoryName Name of the category to delete.
     */

    void deleteCategory(const string &categoryName);

    //SOURCE FILE
    /**
     * @brief Selects the source file for storing the passwords.
     */

    void selectSourceFile();

};
#endif //PASSWORDMANAGER_DATASTORAGE_H

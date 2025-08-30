/// Author : Mohammed Saeed
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

/*
    ------------User Authentication System (Register, Login, Delete)-------------

                - Stores user credentials in a file (database.txt)
                - Passwords are hashed for better security
                - Data stored in table format (Username | Hashed Password)

*/

// ====================== User Struct ======================
struct User {
    string username;
    string password; // hashed password
};

// ====================== Hash Function ======================
string simpleHash(const string& password)
{
    unsigned long hash = 5381;
    for (char c : password) {
        hash = ((hash << 5) + hash) + c;
    }
    return to_string(hash);
}

// ====================== Load Data From File ======================
vector<User> loadUsers(const string& filename)
{
    vector<User> users;
    ifstream file(filename);
    string username, hashed;
    string line;
    getline(file, line);
    getline(file, line);
    while (file >> username >> hashed)
    {
        users.push_back({username, hashed});
    }
    return users;
}
// ====================== Save Data into File ======================
void saveUsers(const vector<User>& users, const string& filename)
 {
    ofstream file(filename);
    file << left << setw(20) << "Username" << "Hashed Password" << "\n";
    file << "------------------------------------------\n";
    for (auto& u : users)
    {
        file << left << setw(20) << u.username << u.password << "\n";
    }
}

// ====================== Check Existancey ======================
bool userExists(const vector<User>& users, const string& username)
{
    for (auto& u : users)
    {
        if (u.username == username) return true;
    }
    return false;
}
// ====================== Register New User ======================
void registerUser(vector<User>& users, const string& filename)
 {
    string username, password;
    while (true) {
        cout << "Enter new Username: ";
        cin >> username;
        if (userExists(users, username))
        {
            cout << "Username already exists! Try another.\n";
        } else break;
    }
    cout << "Enter password: ";
    cin >> password;

    users.push_back({username, simpleHash(password)});
    saveUsers(users, filename);
    cout << "Registration successful!\n";
}
// ====================== Login Account ======================
void loginUser(const vector<User>& users)
{
    if (users.empty()) {
        cout << "No registered users yet. Please register first.\n";
        return;
    }
    string username, password;
    while (true)
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        bool success = false;
        for (auto& u : users)
            {
            if (u.username == username && u.password == simpleHash(password))
            {
                cout << "Login successful! Welcome, " << username << "!\n";
                success = true;
                break;
            }
        }
        if (success) break;
        cout << "Invalid Username or Password. Try again.\n";
    }
}

// ====================== Delete Account ======================
void deleteUser(vector<User>& users, const string& filename)
 {
    if (users.empty()) {
        cout << "No registered users yet.\n";
        return;
    }
while(true)
{
    string username, password;
    cout << "Enter username to delete: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Search for the user
    for (auto it = users.begin(); it != users.end(); ++it)
    {
        if (it->username == username && it->password == simpleHash(password)) {
            cout << "Are you sure you want to delete this account? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                users.erase(it); // remove from vector
                saveUsers(users, filename); // update file
                cout << "Account deleted successfully.\n";
            } else {
                cout << "Account deletion canceled.\n";
            }
            return;
        }
    }
    cout << "Username or Password incorrect. Deletion failed.\n";
}

}

// ====================== Main ======================
int main() {
    string filename = "database.txt";
    vector<User> users = loadUsers(filename);

    int choice;
    do {
        cout << "*********************************************\n";
        cout << "\n        Login & Registration System \n";
        cout << "\n*********************************************\n\n";
        cout << " 1. Register\n";
        cout << " 2. Login\n";
        cout << " 3. Delete Account\n";
        cout << " 4. Exit\n";
        cout << " Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(users, filename); break;
            case 2: loginUser(users); break;
            case 3: deleteUser(users, filename); break;
            case 4: cout << "Exiting... Bye!\n"; break;
            default: cout << "Invalid option.\n"; break;
        }
    } while (choice != 4);

    return 0;
}

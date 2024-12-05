#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>    
#include <algorithm>
#include <regex>
//#include <graphics.h>
using namespace std;

// Helper function to center text
void centerText(const string& text) {
    const int consoleWidth = 80; // Assuming a fixed console width (you can adjust this)
    int padding = (consoleWidth - text.length()) / 2;
    string centeredText(padding, ' '); // Add leading spaces
    centeredText += text;
    cout << centeredText << endl;
}
class Account {
public:
    Account(const string& name, char gender, int pin, double initialDeposit, const string& accountType, const string& email, const string& aadhaar);
    string getAccNo() const;
    string getName() const;
    char getGender() const;
    int getPin() const;
    double getBalance() const;
    string getAccountType() const;
    string getEmail() const;
    string getAadhaar() const;
    bool verifyPin(int enteredPin) const;
    void displayInfo() const;
    void withdraw(double amount);  // Function to withdraw money
    void deposit(double amount);   // Function to deposit money

    static int nextAccNo;

private:
    string name;
    char gender;
    int pin;
    double balance;
    string accNo;
    string accountType;
    string email;
    string aadhaar;
};

int Account::nextAccNo = 10001;

Account::Account(const string& name, char gender, int pin, double initialDeposit, const string& accountType, const string& email, const string& aadhaar) {
    this->name = name;
    this->gender = gender;
    this->pin = pin;
    this->balance = initialDeposit;
    this->accountType = accountType;
    this->email = email;
    this->aadhaar = aadhaar;
    this->accNo = "SRM" + to_string(nextAccNo++);
}

string Account::getAccNo() const {
    return accNo;
}

string Account::getName() const {
    return name;
}

char Account::getGender() const {
    return gender;
}

int Account::getPin() const {
    return pin;
}

double Account::getBalance() const {
    return balance;
}

string Account::getAccountType() const {
    return accountType;
}

string Account::getEmail() const {
    return email;
}

string Account::getAadhaar() const {
    return aadhaar;
}

bool Account::verifyPin(int enteredPin) const {
    return pin == enteredPin;
}

void Account::displayInfo() const {
    cout << "\n=====================================\n";
    cout<<("|         Account Details           |")<<endl;
    cout << "=====================================\n";
    cout << left << setw(20) << "| Bank Name: ABC private bank      " << "|\n";
    cout << left << setw(20) << "| IFSC code: bcdef10001            " << "|\n";
    cout << left << setw(20) << "| Account Number:" << setw(15) << accNo << "|\n";
    cout << left << setw(20) << "| Name:" << setw(15) << name << "|\n";
    cout << left << setw(20) << "| Gender:" << setw(15) << gender << "|\n";
    cout << left << setw(20) << "| Email:" << setw(15) << email << "|\n";
    cout << left << setw(20) << "| Aadhaar:" << setw(15) << aadhaar << "|\n";
    cout << left << setw(20) << "| Balance:" << setw(15) << fixed << setprecision(2) << balance << "|\n";
    cout << left << setw(20) << "| Account Type:" << setw(15) << accountType << "|\n";
    cout << "=====================================\n";
}

void Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        cout << "\nWithdrawal successful. New balance: " << fixed << setprecision(2) << balance << endl;
    } else if (amount <= 0) {
        cout << "Invalid withdrawal amount.\n";
    } else {
        cout << "Insufficient balance.\n";
    }
}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "\nDeposit successful. New balance: " << fixed << setprecision(2) << balance << endl;
    } else {
        cout << "Invalid deposit amount.\n";
    }
}

void updateNextAccNo(const vector<Account>& accounts) {
    for (const auto& account : accounts) {
        int accNumber = stoi(account.getAccNo().substr(3));  // Extract number part from "SRM10001"
        if (accNumber >= Account::nextAccNo) {
            Account::nextAccNo = accNumber + 1;
        }
    }
}

bool adminLogin(const string& filename) {
    ifstream inFile(filename);
    string storedUsername, storedPassword;
    string username, password;

    if (!inFile.is_open()) {
        cerr << "Error opening admin file.\n";
        return false;
    }

    inFile >> storedUsername >> storedPassword;
    inFile.close();


    cout<<("======== Admin Login ========")<<endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == storedUsername && password == storedPassword) {
        centerText("\nLogin Successful!");
        return true;
    } else {
        centerText("\nInvalid credentials. Please try again.");
        return false;
    }
}

bool isValidAadhaar(const string& aadhaar) {
    return regex_match(aadhaar, regex("\\d{12}"));
}
void addUser(const string& filename, vector<Account>& accounts) {
    string name, email, aadhaar;
    char gender;
    int pin;
    double initialDeposit;
    string accountType;

    centerText("\nEnter account details:");
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Gender (M/F): ";
    cin >> gender;
    cout << "PIN: ";
    cin >> pin;
    cout << "Initial deposit: ";
    cin >> initialDeposit;

    // Account type selection menu
    cout << "\nSelect Account Type:\n";
    cout << "1. Savings\n";
    cout << "2. Checking\n";
    cout << "3. Business\n";
    cout << "4. Loan\n";
    cout << "5. Fixed Deposit (FD)\n";
    cout << "Enter the number corresponding to the account type: ";
    
    int accountChoice;
    cin >> accountChoice;

    switch (accountChoice) {
        case 1:
            accountType = "Savings";
            break;
        case 2:
            accountType = "Checking";
            break;
        case 3:
            accountType = "Business";
            break;
        case 4:
            accountType = "Loan";
            break;
        case 5:
            accountType = "FD";
            break;
        default:
            cout << "Invalid choice, setting default account type to 'Savings'.\n";
            accountType = "Savings";
            break;
    }

    cout << "Email: ";
    cin >> email;

    do {
        cout << "Enter 12-digit Aadhaar number: ";
        cin >> aadhaar;
        if (!isValidAadhaar(aadhaar)) {
            cerr << "Invalid Aadhaar number. Please enter a 12-digit number.\n";
        }
    } while (!isValidAadhaar(aadhaar));

    Account newAccount(name, gender, pin, initialDeposit, accountType, email, aadhaar);
    accounts.push_back(newAccount);

    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        outFile << newAccount.getAccNo() << " " << newAccount.getName() << " " << newAccount.getGender() << " "
                << newAccount.getPin() << " " << newAccount.getBalance() << " " << newAccount.getAccountType() << " "
                << newAccount.getEmail() << " " << newAccount.getAadhaar() << endl;
        outFile.close();
        centerText("\nUser added successfully!");
        newAccount.displayInfo();
    } else {
        cerr << "Error opening file for writing.\n";
    }
}
bool searchUser(const vector<Account>& accounts, const string& accNo, int pin) {
    for (const auto& account : accounts) {
        if (account.getAccNo() == accNo && account.verifyPin(pin)) {
            account.displayInfo();

         bool a = true;

   /* if (a) { // Replace `true` with your condition
        initwindow(600, 500, "Display Pic");
        // Adjust the coordinates to specify the smaller size
        int left = 100, top = 100;   // Top-left corner of the image
        int right = 300, bottom = 300; // Bottom-right corner of the image
        readimagefile("pic.jpg", left, top, right, bottom);
        getch();
        closegraph();
    }
*/

            return true;
        }
    }
    centerText("\nUser not found or PIN incorrect.");
    
    return false;
}

void deleteUser(const string& filename, vector<Account>& accounts, const string& accNo) {
    auto it = remove_if(accounts.begin(), accounts.end(), [accNo](const Account& acc) {
        return acc.getAccNo() == accNo;
    });

    if (it != accounts.end()) {
        accounts.erase(it, accounts.end());
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& acc : accounts) {
                outFile << acc.getAccNo() << " " << acc.getName() << " " << acc.getGender() << " " << acc.getPin()
                        << " " << acc.getBalance() << " " << acc.getAccountType() << " "
                        << acc.getEmail() << " " << acc.getAadhaar() << endl;
            }
            outFile.close();
            centerText("\nUser deleted successfully!");
        } else {
            cerr << "Error opening file for updating.\n";
        }
    } else {
        centerText("\nAccount not found.");
    }
}

void loadAccounts(const string& filename, vector<Account>& accounts) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file for loading accounts.\n";
        return;
    }

    string name, accountType, accNo, email, aadhaar;
    char gender;
    int pin;
    double balance;

    while (inFile >> accNo >> name >> gender >> pin >> balance >> accountType >> email >> aadhaar) {
        Account account(name, gender, pin, balance, accountType, email, aadhaar);
        accounts.push_back(account);
    }

    inFile.close();
    updateNextAccNo(accounts);
}
int main() {
    string adminFile = "admin.txt";
    string userFile = "user.txt";
    vector<Account> accounts;

    loadAccounts(userFile, accounts);

    int mainChoice = 0;
    while (mainChoice != 3) {
        centerText("\n========== Welcome ==========");
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "=============================\n";

        cout << "Enter choice: ";
        cin >> mainChoice;

        if (mainChoice == 1) { // Admin Login
            if (!adminLogin(adminFile)) {
                centerText("\nAdmin login failed. Returning to main menu...");
                continue;
            }

            int adminChoice = 0;
            while (adminChoice != 6) {  // Increased the option count to 6
                centerText("\n========== Admin Menu ==========");
                cout << "1. CREATE ACCOUNT\n";
                cout << "2. SEARCH ACCOUNT\n";
                cout << "3. DELETE ACCOUNT\n";
                cout << "4. WITHDRAW\n";
                cout << "5. DEPOSIT\n";  // New option for deposit
                cout << "6. Exit to Main Menu\n";
                cout << "================================\n";

                cout << "Enter choice: ";
                cin >> adminChoice;

                switch (adminChoice) {
                    case 1:
                        addUser(userFile, accounts);
                        break;
                    case 2: {
                        string accNo;
                        int pin;
                        cout << "\nEnter account number: ";
                        cin >> accNo;
                        cout << "Enter PIN: ";
                        cin >> pin;
                        searchUser(accounts, accNo, pin);
                        break;
                    }
                    case 3: {
                        string accNo;
                        cout << "\nEnter account number to delete: ";
                        cin >> accNo;
                        deleteUser(userFile, accounts, accNo);
                        break;
                    }
                    case 4: {
                        string accNo;
                        int pin;
                        double amount;
                        cout << "\nEnter account number: ";
                        cin >> accNo;
                        cout << "Enter PIN: ";
                        cin >> pin;

                        auto it = find_if(accounts.begin(), accounts.end(), [&](const Account& account) {
                            return account.getAccNo() == accNo && account.verifyPin(pin);
                        });

                        if (it != accounts.end()) {
                            cout << "Enter withdrawal amount: ";
                            cin >> amount;
                            it->withdraw(amount);

                            ofstream outFile(userFile);
                            if (outFile.is_open()) {
                                for (const auto& acc : accounts) {
                                    outFile << acc.getAccNo() << " " << acc.getName() << " " << acc.getGender() << " "
                                            << acc.getPin() << " " << acc.getBalance() << " " << acc.getAccountType() << " "
                                            << acc.getEmail() << " " << acc.getAadhaar() << endl;
                                }
                                outFile.close();
                            } else {
                                cerr << "Error opening file for updating.\n";
                            }
                        } else {
                            centerText("\nAccount not found or PIN incorrect.");
                        }
                        break;
                    }
                    case 5: {
                        string accNo;
                        int pin;
                        double amount;
                        cout << "\nEnter account number: ";
                        cin >> accNo;
                        cout << "Enter PIN: ";
                        cin >> pin;

                        auto it = find_if(accounts.begin(), accounts.end(), [&](const Account& account) {
                            return account.getAccNo() == accNo && account.verifyPin(pin);
                        });

                        if (it != accounts.end()) {
                            cout << "Enter deposit amount: ";
                            cin >> amount;
                            it->deposit(amount);  // Calling the deposit function

                            ofstream outFile(userFile);
                            if (outFile.is_open()) {
                                for (const auto& acc : accounts) {
                                    outFile << acc.getAccNo() << " " << acc.getName() << " " << acc.getGender() << " "
                                            << acc.getPin() << " " << acc.getBalance() << " " << acc.getAccountType() << " "
                                            << acc.getEmail() << " " << acc.getAadhaar() << endl;
                                }
                                outFile.close();
                            } else {
                                cerr << "Error opening file for updating.\n";
                            }
                        } else {
                            centerText("\nAccount not found or PIN incorrect.");
                        }
                        break;
                    }
                    case 6:
                        centerText("\nReturning to Main Menu...");
                        break;
                    default:
                        centerText("\nInvalid choice. Try again.");
                }
            }
        } else if (mainChoice == 2) { // User Login
            string accNo;
            int pin;
            cout << "\nEnter account number: ";
            cin >> accNo;
            cout << "Enter PIN: ";
            cin >> pin;

            auto it = find_if(accounts.begin(), accounts.end(), [&](const Account& account) {
                return account.getAccNo() == accNo && account.verifyPin(pin);
            });

            if (it != accounts.end()) {
                int userChoice = 0;
                while (userChoice != 3) {  // Increased the option count to 3
                    centerText("\n========== User Menu ==========");
                    cout << "1. Withdraw Money\n";
                    cout << "2. Deposit Money\n";  // New option for deposit
                    cout << "3. Exit\n";
                    cout << "================================\n";

                    cout << "Enter choice: ";
                    cin >> userChoice;

                    switch (userChoice) {
                        case 1: {
                            double amount;
                            cout << "Enter withdrawal amount: ";
                            cin >> amount;
                            it->withdraw(amount);

                            ofstream outFile(userFile);
                            if (outFile.is_open()) {
                                for (const auto& acc : accounts) {
                                    outFile << acc.getAccNo() << " " << acc.getName() << " " << acc.getGender() << " "
                                            << acc.getPin() << " " << acc.getBalance() << " " << acc.getAccountType() << " "
                                            << acc.getEmail() << " " << acc.getAadhaar() << endl;
                                }
                                outFile.close();
                            } else {
                                cerr << "Error opening file for updating.\n";
                            }
                            break;
                        }
                        case 2: {
                            double amount;
                            cout << "Enter deposit amount: ";
                            cin >> amount;
                            it->deposit(amount);  // Calling the deposit function

                            ofstream outFile(userFile);
                            if (outFile.is_open()) {
                                for (const auto& acc : accounts) {
                                    outFile << acc.getAccNo() << " " << acc.getName() << " " << acc.getGender() << " "
                                            << acc.getPin() << " " << acc.getBalance() << " " << acc.getAccountType() << " "
                                            << acc.getEmail() << " " << acc.getAadhaar() << endl;
                                }
                                outFile.close();
                            } else {
                                cerr << "Error opening file for updating.\n";
                            }
                            break;
                        }
                        case 3:
                            centerText("\nExiting the system. Goodbye!");
                            break;
                        default:
                            centerText("\nInvalid choice. Try again.");
                    }
                }
            } else {
                centerText("\nLogin failed. Account not found or PIN incorrect.");
            }
        } else if (mainChoice == 3) {
            centerText("\nExiting the system. Goodbye!");
        } else {
            centerText("\nInvalid choice. Try again.");
        }
    }

    return 0;
}


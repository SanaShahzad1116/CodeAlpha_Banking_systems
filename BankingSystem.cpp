#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

class Account {
private:
    string accountNumber;
    double balance;

public:
    Account(const string& accNum) : accountNumber(accNum), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        cout << GREEN << "\n[INFO] Deposited: $" << amount << " | New Balance: $" << balance << RESET << "\n\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << RED << "\n[ERROR] Insufficient balance!" << RESET << "\n\n";
        }
        else {
            balance -= amount;
            cout << GREEN << "\n[INFO] Withdrew: $" << amount << " | New Balance: $" << balance << RESET << "\n\n";
        }
    }

    double getBalance() const {
        return balance;
    }

    string getAccountNumber() const {
        return accountNumber;
    }
};

class Customer {
private:
    string name;
    Account account;

public:
    Customer(const string& name, const string& accNum) : name(name), account(accNum) {}

    void deposit(double amount) {
        account.deposit(amount);
    }

    void withdraw(double amount) {
        account.withdraw(amount);
    }

    void displayBalance() const {
        cout << CYAN << "\n[INFO] " << name << "'s Balance: $" << fixed << setprecision(2) << account.getBalance() << RESET << "\n\n";
    }

    string getAccountNumber() const {
        return account.getAccountNumber();
    }
};

class BankingSystem {
private:
    vector<Customer> customers;

public:
    void addCustomer(const string& name, const string& accNum) {
        customers.push_back(Customer(name, accNum));
        cout << GREEN << "\n[SUCCESS] Customer added: " << name << " | Account No: " << accNum << RESET << "\n\n";
    }

    Customer* getCustomer(const string& accNum) {
        for (auto& customer : customers) {
            if (customer.getAccountNumber() == accNum) {
                return &customer;
            }
        }
        return nullptr;
    }
};

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void menu() {
    cout << BOLD << BLUE;
    cout << "\n***************************************************\n";
    cout << "*          WELCOME TO THE BANKING SYSTEM          *\n";
    cout << "***************************************************\n";
    cout << "*    1. Deposit                                  *\n";
    cout << "*    2. Withdraw                                 *\n";
    cout << "*    3. Show Balance                             *\n";
    cout << "*    4. Exit                                     *\n";
    cout << "***************************************************\n";
    cout << "Select an option: " << RESET;
}

int main() {
    BankingSystem bank;
    int num;

    clearScreen();

    cout << CYAN << "\nEnter number of customers: " << RESET;
    cin >> num;

    for (int i = 0; i < num; i++) {
        string name, accNum;
        cout << YELLOW << "Enter name: " << RESET;
        cin >> name;
        cout << YELLOW << "Enter account number: " << RESET;
        cin >> accNum;
        bank.addCustomer(name, accNum);
    }

    string accNum;
    cout << CYAN << "\nEnter account number for further transactions: " << RESET;
    cin >> accNum;

    Customer* customer = bank.getCustomer(accNum);
    if (customer) {
        int choice;
        do {
            clearScreen();
            menu();
            cin >> choice;
            switch (choice) {
            case 1: {
                double amount;
                cout << YELLOW << "Enter deposit amount: " << RESET;
                cin >> amount;
                customer->deposit(amount);
                break;
            }
            case 2: {
                double amount;
                cout << YELLOW << "Enter withdrawal amount: " << RESET;
                cin >> amount;
                customer->withdraw(amount);
                break;
            }
            case 3:
                customer->displayBalance();
                break;
            case 4:
                cout << GREEN << "\n[INFO] Exiting..." << RESET << "\n\n";
                break;
            default:
                cout << RED << "\n[ERROR] Invalid choice! Try again." << RESET << "\n\n";
            }
            if (choice != 4) {
                cout << YELLOW << "\nPress Enter to continue..." << RESET;
                cin.ignore();
                cin.get();
            }
        } while (choice != 4);
    }
    else {
        cout << RED << "\n[ERROR] Account not found!" << RESET << "\n\n";
    }

    return 0;
}

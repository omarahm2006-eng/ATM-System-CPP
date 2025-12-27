#include <iostream>
#include <string>
using namespace std;

class ATM {
private:
	double balance;
	int pin;

public:
	ATM(double initialBalance, int initialPin) {
		balance = initialBalance;
		pin = initialPin;
	}
	void checkBalance() {
		cout << "\n[Balance] your current balance is :" << balance << "$" << endl;
	}
	void deposit(double amount) {
		if (amount > 0) {
			balance += amount;
			cout << "Successfully deposited :" << amount << "$" << endl;
		}
		else {
			cout << "Error: Deposit amount must be positive!" << endl;
		}
	}
	void withdraw(double amount, int enteredPin) {
		if (enteredPin != pin) {
			cout << "Error: Incorrect PIN. Access Denied!" << endl;
			return;
		}
		if (amount > balance) {
			cout << "Error: Insufficient funds! You only have " << balance << "$" << endl;
		}
		else if (amount <= 0) {
			cout << "Error: Invalid withdrawal amount!" << endl;
		}
		else {
			balance -= amount;
			cout << "Successfully withdrew: " << amount << "$" << endl;
			cout << "Remaining balance: " << balance << "$" << endl;
		}
	}
};

int main() {
	// Pointer to ATM object, initially pointing to nothing (null)
	ATM* myAcc = nullptr;
	int mainChoice;
	// Boolean flag to track if the user is authenticated
	bool loggedIn = false;

	cout << "Welcome to the Banking System" << endl;

	do {
		// Step 1: Check if an account needs to be created
		if (myAcc == nullptr) {
			cout << "\n1.Create New Account " << endl;
			cout << "2.Exit" << endl;
			cout << "Choice: ";
			cin >> mainChoice;

			if (mainChoice == 1) {
				double initBalance;
				int newPin;

				cout << "Enter initial balance: ";
				cin >> initBalance;
				cout << "Set your secret PIN: ";
				cin >> newPin;

				// Allocate memory dynamically for a new ATM object
				myAcc = new ATM(initBalance, newPin);
				cout << "\nAccount Created Successfully!" << endl;
			}
			else {
				break; // Terminate loop if user chooses Exit
			}
		}

		// Step 2: Handle login if account exists but user isn't logged in
		if (myAcc != nullptr && !loggedIn) {
			int loginPin;
			cout << "\n--- Login System ---" << endl;
			cout << "Enter your PIN to access your account: ";
			cin >> loginPin;

			cout << "Verifying..." << endl;
			loggedIn = true; // Set login status to true
		}

		// Step 3: Display operations menu after successful login
		if (loggedIn) {
			int action;
			cout << "\n--- Welcome back! ---" << endl;
			cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Logout\nEnter action: ";
			cin >> action;

			if (action == 1) {
				myAcc->checkBalance(); // Use '->' to access members via pointer
			}
			else if (action == 2) {
				double dep;
				cout << "Amount to deposit: "; cin >> dep;
				myAcc->deposit(dep);
			}
			else if (action == 3) {
				double draw;
				int p;
				cout << "Amount to withdraw: "; cin >> draw;
				cout << "Confirm PIN for security: "; cin >> p;
				myAcc->withdraw(draw, p);
			}
			else if (action == 4) {
				loggedIn = false; // Reset login status
				cout << "Logged out successfully." << endl;
			}
		}

	} while (mainChoice != 2);

	// Clean up: Free the dynamically allocated memory
	if (myAcc != nullptr) {
		delete myAcc;
		myAcc = nullptr; // Reset pointer to avoid "dangling pointer"
	}

	return 0;
}
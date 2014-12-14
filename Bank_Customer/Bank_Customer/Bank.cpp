#include "Bank.h"

//Getters
const vector<Customer*>& Bank::getCustomers() const { return pCustomers; } //Changed to const for iter

const vector<Account*>& Bank::getAccounts() const { return pAccounts; } //Changed to const for

const vector<Transaction*>& Bank::getTransactions() const { return pTransactions; }

Date Bank::getCurrentDate() { return current_date; }

const int Bank::getCurrentUser() const { return current_user; }

//Setters
void Bank::setCustomer(Customer* Customer) { pCustomers.push_back(Customer); }

void Bank::setAccount(Account* Account) { pAccounts.push_back(Account); }

void Bank::setTransaction(Transaction* Transaction){ pTransactions.push_back(Transaction); }

void Bank::setCurrentDate(Date currentDate) { current_date = currentDate; }

void Bank::setCurrentUser(int customer_id) { current_user = customer_id; }


//File Reading Functions

//Read customers file and store information into bank's customers vector
void Bank::readCustomers() {
	ifstream customer_file("customer_input.txt");
	if (!customer_file) {
		cout << "customer_input.txt not found." << endl;
		exit(0);
	}
	while (!customer_file.eof()) {
		customer_file >> pCustomers;
	}
}

//Read account file and store information into bank's accounts vector
void Bank::readAccounts() {
	ifstream account_file("accounts_input.txt");
	if (!account_file) {
		cout << "accounts_input.txt not found." << endl;
	}
	while (!account_file.eof()) {
		account_file >> pAccounts;
	}
}

//Read transaction file and store transactions into proper account
void Bank::readTransactions() {
	ifstream transaction_file("transactions_input.txt");
	if (!transaction_file) {
		cout << "transactions_input.txt not found." << endl;
	}
	while (!transaction_file.eof()) {
		transaction_file >> pTransactions;
	}
	//Loop through transaction pointers and store into proper account
	vector<Transaction*>::const_iterator transaction_iter;
	vector<Account*>::const_iterator account_iter;
	for (transaction_iter = pTransactions.begin();
		transaction_iter != pTransactions.end(); ++transaction_iter) {
		int transaction_account = (*transaction_iter)->getAccount();

		for (account_iter = pAccounts.begin();
			account_iter != pAccounts.end(); ++account_iter) {
			int account = (*account_iter)->getNumber();
			if (account == transaction_account) {
				(*account_iter)->setTransaction(*transaction_iter);
			}
		}
	}
}

//Read association file to associate customers with accounts
void Bank::readAssociation() {
	ifstream association_file("account_association.txt");
	if (!association_file) {
		cout << "account_association.txt not found." << endl;
	}
	//Create Iterators
	vector<Customer*>::const_iterator customer_iter;
	vector<Account*>::const_iterator account_iter;

	//Loop through accounts and store into customers
	while (!association_file.eof()) {
		int customer_number, account_number;
		association_file >> customer_number >> account_number;

		//Loop through customers and add pointer to owner vector of proper account
		for (customer_iter = pCustomers.begin(); customer_iter != pCustomers.end(); ++customer_iter) {
			if ((*customer_iter)->getId() == customer_number) {
				Customer* pCustomer = (*customer_iter);
				for (account_iter = pAccounts.begin(); account_iter != pAccounts.end(); ++account_iter) {
					if ((*account_iter)->getNumber() == account_number) {
						(*account_iter)->setOwner(pCustomer);
					}
				}
			}
		}

		//Loop through accounts and add pointer to account vector of proper customer
		for (account_iter = pAccounts.begin(); account_iter != pAccounts.end(); ++account_iter) {
			if ((*account_iter)->getNumber() == account_number) {
				Account* pAccount = (*account_iter);
				for (customer_iter = pCustomers.begin(); customer_iter != pCustomers.end(); ++customer_iter) {
					if ((*customer_iter)->getId() == customer_number) {
						(*customer_iter)->setAccount(pAccount);
					}
				}
			}
		}
	}
}

//Calculation Functions
void Bank::calculateFees() {
	vector<Account*>::const_iterator account_iter;
	for (account_iter = pAccounts.begin(); account_iter != pAccounts.end(); ++account_iter) {
		if ((*account_iter)->getType() == 1) {
			int months = (*account_iter)->calculate_months(current_date, (*account_iter)->getDate());
			int year = (*account_iter)->getDate().getYear();
			int month = (*account_iter)->getDate().getMonth();
			for (int i = 0; i < months; i++) {
				int day = calculateDays(month);
				Date fee_date = Date(day, month, year, '/');
				Transaction* new_transaction = new Transaction((*account_iter)->getNumber(), "w", 5.00, fee_date, "Account Fee");
				(*account_iter)->setTransaction(new_transaction);
				if (month == 12) { month = 1; year += 1; }
				else { month += 1; }
			}
		}
	}
}

void Bank::calculateInterest() {
	vector<Account*>::const_iterator account_iter;
	for (account_iter = pAccounts.begin(); account_iter != pAccounts.end(); ++account_iter) {
		if (((*account_iter)->getType() == 2) || ((*account_iter)->getType() == 3) || ((*account_iter)->getType() == 4)) {
			int months = (*account_iter)->calculate_months(current_date, (*account_iter)->getDate());
			int year = (*account_iter)->getDate().getYear();
			int month = (*account_iter)->getDate().getMonth();
			for (int i = 0; i < months; i++) {
				int day = calculateDays(month);
				Date interest_date = Date(day, month, year, '/');
				//Hard coding this shit, change it later
				double interest = (*account_iter)->calculate_total() * (0.03 / 12);
				Transaction* new_transaction = new Transaction((*account_iter)->getNumber(), "d", interest, interest_date, "Monthly Interest");
				(*account_iter)->setTransaction(new_transaction);
				if (month == 12) { month = 1; year += 1; }
				else { month += 1; }
			}
		}
	}
}

bool Bank::customer_validification(int id, string password) {
	int customer_id;
	string customer_password;
	ifstream login_file("login_information.txt");
	if (!login_file) {
		cout << "login_information.txt not found." << endl;
	}
	while (!login_file.eof()) {
		login_file >> customer_id >> customer_password;
		if (customer_id == id) {
			if (customer_password == password) {
				return true;
			}
		}
	} 
	return false;

}

//Menu Functions

void Bank::welcome_menu() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int month = timePtr->tm_mon + 1;
	int year = timePtr->tm_year + 1900;
	int day = timePtr->tm_mday;
	Date System_Date = Date(day, month, year, '/');
	current_date = System_Date;
	cout << "--Welcome to the Michelangelo Banking System--" << endl;
	cout << "Today's date is " << current_date << endl << endl;
}

void Bank::login_menu() {
	cout << "Before viewing your information we need you to login." << endl;
	cout << "Note: Password is case-senstive" << endl << endl;
	int customer_id;
	string customer_password;
	cout << "Please enter your customer number. "; 	cin >> customer_id;
	cout << "Please enter your password. ";  cin >> customer_password;
	if (customer_validification(customer_id, customer_password)) {
		setCurrentUser(customer_id);
		main_menu();
	}
	else {
		cout << "Invalid customer number/password" << endl;
		login_menu();
	}
	
}

//Main Menu
void Bank::main_menu() {
	cout << "--Main Menu--" << endl;
	cout << "Enter 1 to view your monthly statement." << endl;
	cout << "Enter 2 to view total of an account." << endl;
	cout << "Enter 3 to make a payment on your loan." << endl;
	cout << "Enter 4 to change your password." << endl;
	cout << "Enter 0 to exit application." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		exit(0);
	case 1:
		print_customer_statements();
	case 2:
		customer_total();
	case 3:
		customer_payment();
	case 4:
		change_password();
	}

}



//Customer Info Menu
void Bank::customer_info_menu() {
	cout << "--Customer Information Menu--" << endl << endl;
	vector<Account*>::const_iterator account_iter;
	vector<Customer*>::const_iterator iter;
	for (iter = pCustomers.begin();
		iter != pCustomers.end(); ++iter) {
		// We could probably overload an operator for this long bit
		cout << (*iter)->getId() << " " << (*iter)->getSocial() << " " <<
			(*iter)->getFirst() << " " << (*iter)->getLast() << " " << (*iter)->getAddress() << endl;
	}
	main_menu();
}

//View a statement for an account
void Bank::print_customer_statements() {
	int account_number, month, year;
	cout << "--View Your Monthly Statement--" << endl;
	cout << "This menu will allow you to view current and all past monthly statements." << endl;
	cout << "Enter Your Account Number: ";
	cin >> account_number;
	cout << "What Month (XX)? ";
	cin >> month;
	cout << "What Year (XXXX)? ";
	cin >> year;
	cout << endl << "--Statement from " << month << "/" << year << "--" << endl << endl;
	vector<Account*>::const_iterator account_iter;
	vector<Transaction*>::const_iterator transaction_iter;
	for (account_iter = pAccounts.begin();
		account_iter != pAccounts.end(); ++account_iter) {
		if ((*account_iter)->getNumber() == account_number) {
			//for each transaction, print it to screen
			for (transaction_iter = (*account_iter)->getTransactions().begin();
				transaction_iter != (*account_iter)->getTransactions().end();
				++transaction_iter) {
				//Sort the transactions before they get printed
				sort((*account_iter)->getTransactions().begin(), (*account_iter)->getTransactions().end(), sort_transactions);

				if ((*transaction_iter)->getDate().getMonth() == month && (*transaction_iter)->getDate().getYear() == year) {
					cout << (*transaction_iter)->getDate();
					if ((*transaction_iter)->getType() == "d") {
						cout << " Deposit, $" << (*transaction_iter)->getAmount() <<
							" from " << (*transaction_iter)->getInfo() << "." << endl;
					}
					else {
						cout << " Withdrawal, $" << (*transaction_iter)->getAmount() <<
							" to " << (*transaction_iter)->getInfo() << "." << endl;
					}
				}
			}
		}
	}
	cout << "--End of Statement--" << endl << endl;
	cout << "Enter 1 View Another Monthly Statement." << endl;
	cout << "Enter 0 to Return to the Main Menu." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		main_menu();
	case 1:
		print_customer_statements();
	}
}

// View the total of an account
void Bank::customer_total() {
	cout << "--View the Total of Your Account--" << endl << endl;
	cout << "This menu will allow you to view the total of any of your accounts." << endl;
	int account;
	cout << "Account to view total of: "; cin >> account;
	vector<Account*>::const_iterator account_iter;
	vector<Customer*>::const_iterator customer_iter;
	bool match = false;
	for (account_iter = pAccounts.begin();
		account_iter != pAccounts.end(); ++account_iter) {
		if ((*account_iter)->getNumber() == account) {
			for (customer_iter = (*account_iter)->getOwners().begin();
				customer_iter != (*account_iter)->getOwners().end();
				++customer_iter) {
				if ((*customer_iter)->getId() == current_user) {
					match = true;
					double total = (*account_iter)->calculate_total();
					cout << "Account Number: " << (*account_iter)->getNumber() << " " << " Account Total: $" << total << endl << endl;
				}
			}
		}
	}
	if (!match) {
		cout << endl << "You do not own this account or this account does not exist." << endl << endl;
	}
	cout << "Enter 1 View Another Total for a Different Account." << endl;
	cout << "Enter 0 to Return to the Main Menu." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		main_menu();
	case 1:
		customer_total();
	}
}


//Make a payment on a loan
void Bank::customer_payment() {
	cout << "--Make a Payment on Your Loan--" << endl << endl;
	cout << "This menu will allow you to make a payment on your loan." << endl;
	int account;
	string type, info;
	double amount;
	Date date;
	cout << "Account to apply to: "; cin >> account;
	cout << "Amount: $"; cin >> amount;
	date = current_date;
	type = "d";
	info = "Loan Payment";
	Transaction* new_transaction = new Transaction(account, type, amount, date, info);
	pTransactions.push_back(new_transaction);

	// Adds new transaction to transaction text file
	fstream newTransaction;
	newTransaction.open("transactions_input.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	newTransaction << endl << account << " " << type << " " << amount << " " << date << " " << info;
	newTransaction.close();

	//Loop through accounts and store transaction pointer into proper one
	vector<Account*>::const_iterator account_iter;
	for (account_iter = pAccounts.begin(); account_iter != pAccounts.end(); ++account_iter) {
		if ((*account_iter)->getNumber() == account) {
			(*account_iter)->setTransaction(new_transaction);
		}
	}

	cout << "--Successfully Added Payment--" << endl;
	cout << "Enter 1 to Add Another Payment." << endl;
	cout << "Enter 0 to Return to the Main Menu." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		main_menu();
	case 1:
		customer_payment();
	}
}

void Bank::change_password() {
	string line, old_password, new_password1, new_password2;
	int customer_id;
	cout << "Please enter your customer ID: "; cin >> customer_id;
	cout << "Please enter your old password: "; cin >> old_password;
	string delete_line = to_string(customer_id) + " " + old_password;
	if (customer_validification(customer_id, old_password)) {
		cout << "Please enter your new password: "; cin >> new_password1;
		cout << "Please enter your new password again for verification: "; cin >> new_password2;
		if (new_password1 == new_password2){
			ifstream in("login_information.txt");
			if (!in.is_open()){
				cout << "Input file failed to open \n";
			}
			ofstream out("outfile.txt");
			while (getline(in, line)) {
				if (line != delete_line) {
					out << line << endl;
				}
			}
			in.close();
			out.close();
			// delete original file
			remove("login_information.txt");
			// rename old to new
			rename("outfile.txt", "login_information.txt");
			// Adds new password to login file
			fstream newPassword;
			newPassword.open("login_information.txt", std::fstream::in | std::fstream::out | std::fstream::app);
			newPassword << customer_id << " " << new_password1;
			newPassword.close();
			cout << "--Successfully Changed Password--" << endl;
		}
		else {
			cout << "The passwords you entered to not match please try again" << endl;
			change_password();
		}
	}
	else {
		cout << "Invalid customer number/password" << endl;
		change_password();
	}
	main_menu();
}

//Other Functions

//Get Input
int Bank::get_input() {
	int option;
	cin >> option;
	return option;
}
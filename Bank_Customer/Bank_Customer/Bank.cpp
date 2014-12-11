#include "Bank.h"

//Getters
const vector<Customer*>& Bank::getCustomers() const { return pCustomers; } //Changed to const for iter

const vector<Account*>& Bank::getAccounts() const { return pAccounts; } //Changed to const for

const vector<Transaction*>& Bank::getTransactions() const { return pTransactions; }

Date Bank::getCurrentDate() { return current_date; }

//Setters
void Bank::setCustomer(Customer* Customer) { pCustomers.push_back(Customer); }

void Bank::setAccount(Account* Account) { pAccounts.push_back(Account); }

void Bank::setTransaction(Transaction* Transaction){ pTransactions.push_back(Transaction); }

void Bank::setCurrentDate(Date currentDate) { current_date = currentDate; }

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
					if ((*account_iter)->getNumber() == customer_number) {
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

//Menu Functions

void Bank::welcome_menu() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int month = timePtr->tm_mon + 1;
	int year = timePtr->tm_year + 1900;
	int day = timePtr->tm_mday;
	Date System_Date = Date(day, month, year, '/');
	current_date = System_Date;
	cout << "--Welcome to Boner Incorporated Banking System--" << endl;
	cout << "Today's date is " << current_date << endl << endl;
}

//Main Menu
void Bank::main_menu() {
	cout << "--Main Menu--" << endl;
	cout << "Enter 1 to add a new customer." << endl;
	cout << "Enter 2 to add a new account." << endl;
	cout << "Enter 3 to add a transaction to an existing account." << endl;
	cout << "Enter 4 to view customer information." << endl;
	cout << "Enter 5 to associate accounts." << endl;
	cout << "Enter 6 to print customer account statements." << endl;
	cout << "Enter 7 to print total values of a certain account." << endl;
	cout << "Enter 8 to print customer totals." << endl;
	cout << "Enter 0 to exit application." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		exit(0);
	case 1:
		customer_input_menu();
	case 2:
		account_input_menu();
	case 3:
		transaction_input_menu();
	case 4:
		customer_info_menu();
	case 5:
		account_association_menu();
	case 6:
		print_customer_statements();
	case 7:
		print_total();
	case 8:
		customer_summary_menu();
	}
}

//Customer Input Menu
void Bank::customer_input_menu() {
	cout << "--Customer Input Menu--" << endl << endl;
	cout << "This menu will allow you to add a new customer to the bank." << endl << endl;
	int new_id, new_ssn;
	string new_first, new_last, new_address;
	cout << "First Name: "; cin >> new_first;
	cout << "Last Name: "; cin >> new_last;
	cout << "Social Security Number: "; cin >> new_ssn;
	cout << "Address: "; getline(cin, new_address); getline(cin, new_address);
	//We should check if ID is valid and unused
	cout << "Customer ID Number: "; cin >> new_id;
	Customer* new_customer = new Customer(new_id, new_ssn, new_first, new_last, new_address);
	pCustomers.push_back(new_customer);

	//Adds new customer to customer text file
	fstream newCustomer;
	newCustomer.open("customer_input.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	newCustomer << endl << new_id << " " << new_ssn << " " << new_first << " " << new_last << " " << new_address;
	newCustomer.close();

	cout << "Successfully added customer." << endl;
	cout << "Enter 1 to add another customer." << endl;
	cout << "Enter 0 to return to the main menu." << endl;

	int option = get_input();
	switch (option) {
	case 0:
		main_menu();
	case 1:
		customer_input_menu();
	}
}

//Transaction Input Menu
void Bank::transaction_input_menu() {
	cout << "--Transaction Input Menu--" << endl << endl;
	cout << "This menu will allow you to add a new transaction." << endl;
	int account;
	string type, info;
	double amount;
	Date date;
	cout << "Account to apply to: "; cin >> account;
	cout << "Transaction type (d or w): "; cin >> type;
	cout << "Amount "; cin >> amount;
	cout << "Date of transaction: "; cin >> date;
	cout << "Description: "; getline(cin, info); getline(cin, info);
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

	cout << "--Successfully added transaction--" << endl;
	cout << "Enter 1 to add another transaction." << endl;
	cout << "Enter 0 to return to the main menu." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		main_menu();
	case 1:
		transaction_input_menu();
	}
}

//Account Input Menu
void Bank::account_input_menu() {
	cout << "--Account Input Menu--" << endl << endl;
	cout << "This menu will allow you to create a new account with opening balance" << endl;
	//Variables
	int number;
	int type;
	double balance;
	double interestRate = 0.03;
	Date date = current_date;
	cout << "Please enter the type of account you would like." << endl;
	cout << "	1. Checking" << endl;
	cout << "	2. Savings" << endl;
	cout << "	3. Certificate Deposit" << endl;
	cout << "   4. Loan" << endl << endl;
	cin >> type;
	cout << "Please Enter New Account Number: "; cin >> number;
	cout << "Please Enter Opening Balance: "; cin >> balance;
	if (type == 1) {
		Checking_Account* new_account = new Checking_Account(number, balance, date);
		pAccounts.push_back(new_account);
		//Adds new account to account text file
		fstream newAccount;
		newAccount.open("accounts_input.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		newAccount << endl << type << " " << number << " " << balance << " " << date;
		newAccount.close();
	}
	else if (type == 2){
		Savings_Account* new_account = new Savings_Account(number, balance, date);
		pAccounts.push_back(new_account);
		//Adds new account to account text file
		fstream newAccount;
		newAccount.open("accounts_input.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		newAccount << endl << type << " " << number << " " << balance << " " << date;
		newAccount.close();
	}
	else if (type == 3) {
		Date maturityDate;
		cout << "What is the maturity date? " << endl;
		cin >> maturityDate;
		CD_Account* new_account = new CD_Account(number, balance, date, interestRate, maturityDate);
		pAccounts.push_back(new_account);
		//Adds new account to account text file
		fstream newAccount;
		newAccount.open("accounts_input.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		newAccount << endl << type << " " << number << " " << balance << " " << date << " " << interestRate << " " << maturityDate;
		newAccount.close();
	}
	else if (type == 4) {
		balance = balance * -1;
		Loan* new_account = new Loan(number, balance, date, interestRate);
		pAccounts.push_back(new_account);
		//Adds new account to account text file
		fstream newAccount;
		newAccount.open("accounts_input.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		newAccount << endl << type << " " << number << " " << balance << " " << date << " " << interestRate << " ";
		newAccount.close();
	}

	cout << "--Successfully added account--" << endl;
	cout << "Enter 1 to add another account." << endl;
	cout << "Enter 0 to return to the main menu." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		main_menu();
	case 1:
		account_input_menu();
	}
}

//Associate accounts
void Bank::account_association_menu() {
	int customerNumber, accountNumber;
	vector<Customer*>::const_iterator customer_iter;
	vector<Account*>::const_iterator account_iter;
	cout << "--Account Association Menu--" << endl << endl;
	cout << "This menu will allow you to create a customer" << endl;
	cout << "number that is associated with given account number." << endl << endl;
	cout << "Enter Customer Number: ";
	cin >> customerNumber;
	cout << "Enter an Account Number: ";
	cin >> accountNumber;
	//Loop through customers and add pointer to owner vector of proper account
	for (customer_iter = pCustomers.begin(); customer_iter != pCustomers.end(); ++customer_iter) {
		if ((*customer_iter)->getId() == customerNumber) {
			Customer* pCustomer = (*customer_iter);
			for (account_iter = pAccounts.begin(); account_iter != pAccounts.end(); ++account_iter) {
				if ((*account_iter)->getNumber() == customerNumber) {
					(*account_iter)->setOwner(pCustomer);
				}
			}
		}
	}
	//Loop through accounts and add pointer to account vector of proper customer
	for (account_iter = pAccounts.begin(); account_iter != pAccounts.end(); ++account_iter) {
		if ((*account_iter)->getNumber() == accountNumber) {
			Account* pAccount = (*account_iter);
			for (customer_iter = pCustomers.begin(); customer_iter != pCustomers.end(); ++customer_iter) {
				if ((*customer_iter)->getId() == customerNumber) {
					(*customer_iter)->setAccount(pAccount);
				}
			}
		}
	}
	// Adds new transaction to transaction text file
	fstream newAssociation;
	newAssociation.open("account_association.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	newAssociation << endl << customerNumber << " " << accountNumber;
	newAssociation.close();

	cout << endl << "Successfully associated customer number " << customerNumber << " with account number " << accountNumber << "." << endl << endl;
	cout << "Enter 1 to add another account." << endl;
	cout << "Enter 0 to return to the main menu." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		cout << endl;
		main_menu();
	case 1:
		account_association_menu();
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

//Print Customer Statements
void Bank::print_customer_statements() {
	int account_number, month, year;
	cout << "--Print a Customer Statement--" << endl;
	cout << "Enter Account Number: ";
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
	cout << "Enter 1 to print another customer statement" << endl;
	cout << "Enter 0 to return to the main menu." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		main_menu();
	case 1:
		print_customer_statements();
	}
}

//Print account totals
void Bank::print_total() {
	int account_type;
	double total = 0;
	cout << "--Print Total Values--" << endl;
	cout << "Enter 1 for Checking Accounts" << endl;
	cout << "Enter 2 for Savings Accounts" << endl;
	cout << "Enter 3 for CD Accounts" << endl;
	cout << "Enter 4 for Loan Accounts" << endl;
	cin >> account_type;
	vector<Account*>::const_iterator account_iter;
	vector<Transaction*>::const_iterator transaction_iter;
	for (account_iter = pAccounts.begin();
		account_iter != pAccounts.end(); ++account_iter) {
		if ((*account_iter)->getType() == account_type) {
			total += (*account_iter)->calculate_total();
		}

	}
	cout << total << endl;
	main_menu();
}

// Prints customer name and the total value of their accounts
void Bank::customer_summary_menu() {
	cout << "--Customer Summary Menu--" << endl << endl;
	vector<Account*>::const_iterator account_iter;
	vector<Customer*>::const_iterator iter;
	for (iter = pCustomers.begin();
		iter != pCustomers.end(); ++iter) {
		cout << "Customer ID: " << (*iter)->getId() << " " << "Customer Name: " << (*iter)->getFirst() << " " << (*iter)->getLast() << endl;
		for (account_iter = (*iter)->getAccounts().begin();
			account_iter != (*iter)->getAccounts().end(); ++account_iter) {
			double total = 0;
			total += (*account_iter)->calculate_total();
			cout << "Account Number: " << (*account_iter)->getNumber() << " " << " Account Total: $" << total << endl << endl;
		}
	}
	cout << "--Customer Summary Complete--" << endl << endl;
	cout << "Enter 1 to print the summary again." << endl;
	cout << "Enter 0 to return to the main menu." << endl;
	int option = get_input();
	switch (option) {
	case 0:
		main_menu();
	case 1:
		customer_summary_menu();
	}
}

//Other Functions

//Get Input
int Bank::get_input() {
	int option;
	cin >> option;
	return option;
}
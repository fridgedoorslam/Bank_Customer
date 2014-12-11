#include "Account.h"
#include "Bank.h"
#include "Customer.h"
#include "Date.h"
#include "Transaction.h"
#include "Savings_Account.h"
#include "Checking_Account.h"
#include "CD_Account.h"
#include <iomanip>

int main() {
	cout << setprecision(2) << fixed;

	Bank bank = Bank();

	//Read text files
	bank.welcome_menu();
	bank.readCustomers();
	bank.readAccounts();
	bank.readTransactions();
	bank.readAssociation();

	//Run calculation functions
	bank.calculateFees();
	bank.calculateInterest();

	//Display main menu
	bank.main_menu();
	return 0;
}
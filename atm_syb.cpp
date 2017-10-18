#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#include <algorithm>
#include <limits.h>

/* C++ Programming - Professor Minkyu Ahn **
**       Bank ATM System Application      **
** 2017-09-28      21300139 Young Eun Kim */

using namespace std;

void executeATM();
void menuSwitch();
void openAccount();
int login(int e);
void deposit();
void checkBalance();
void transfer();
void withdraw();
void display(string str, int amount);
int blockneginput(int amount, string str);
int blocknegexceed(int amount, string str);
void confirmation(string str, int amount);
int digitlimit(string str, int limit);
int match(string str);
bool cistrcmp(const string& str1, const string& str2);
void endmsg();

string name[500];			// string array for the name of the customers
int current, accnum = 0;	// current as to use as an index for name[], pins[], and blance[]. accnum ++ each time account is opened
int pins[50], days[50], balance[50];	// pins[] for the pins of the customers, days[] for the dob of customers, balance[] for balance of the customers

int main(int argc, char** argv) {
	fill_n(balance, 50, 100000);	// initialize all value of balance[] with 100000
	
	executeATM();	// execution of the ATM machine
	
	return 0;
}

void executeATM() {
	int initreq;	// initial request input from the user
	
  label:	// goto loop
	do{		// do while loop to display menu repetitively until the user inputs 0
		cout << "\n*********** Welcome to SUNG YOUNG BANK! ************\n";		//welcome menu display
		cout << "*                                                  *\n";
		cout << "*  1. Open a Bank Account                          *\n";
		cout << "*  2. Log in as a User                             *\n";
		cout << "*  0. Exit the SYB Banking System                  *\n";
		cout << "*                                                  *\n";
		cout << "****************************************************\n";
		
		cout << "\nPlease select from above (0~2) : ";
		
		cin >> initreq;
		while (cin.fail()) {	// to filter the input which is not an integer type value
			    cin.clear();	// clear input buffer to restore cin to a usable state
			    cin.ignore(INT_MAX, '\n');	// ignore last input
			    cout << "You can only enter numbers from 0 to 2.\n";
			    cout << "Please select from above (0~2) : ";
			    cin >> initreq;
		}
		
		switch(initreq) { 	// switch for the welcome menu
			case 1:
				cin.ignore();
				openAccount();	// open account function
				break;
			case 2:
				cin.ignore();
				if(accnum>0) {	// checks if there exists more than 1 account in the bank
					initreq = login(initreq);	// if log in is successful, initreq is set as 2, else, initreq is set as 0 and skips the menuSwitch function and displays the welcome menu
				}
				else {	// no account opened yet
					cout << "No account is opened yet. Please open an account first.\n";
					sleep(1);
					goto label;		// goto loop to 
				}
				break;
			case 0:
				endmsg();	// displays the end message as the user exits
				return;
		}
		if(initreq < 3 && initreq >= 1) {	// for case 1 and 2, proceed to the menuSwitch for transactions
		  menuSwitch();
		}
	} while(1);
}

void menuSwitch() {		// transaction platform
	int request;
	
  functions:	// goto loop
	do {		// do while loop to display menu repetitively until the user inputs 0
		cout << "\n****************************************************\n";
		cout << "*                                                  *\n";
		cout << "*  1. Deposit Cash                                 *\n";
		cout << "*                                                  *\n";
		cout << "*  2. Check Account Balance                        *\n";
		cout << "*                                                  *\n";
		cout << "*  3. Transfer to Another Account                  *\n";
		cout << "*                                                  *\n";
		cout << "*  4. Withdraw Cash                                *\n";
		cout << "*                                                  *\n";
		cout << "*  0. Log Out                                      *\n";
		cout << "*                                                  *\n";
		cout << "****************************************************\n\n";
		
		cout << "Please select a number from above (0~4) : ";
		cin >> request;
		while (cin.fail()) {	// to filter the input which is not an integer type value
		    cin.clear();		// clear input buffer to restore cin to a usable state
		    cin.ignore(INT_MAX, '\n');	// ignore last input
		    cout << "You can only enter numbers from 0 to 4.\n";
		    cout << "Please select a number from above (0~4) : ";
		    cin >> request;
		}
		
		switch(request) {	// switch for the transaction menu
	    case 1 :
	    	cin.ignore();
			deposit();	// deposit transaction
			break;
		case 2 :
	    	cin.ignore();
			checkBalance();	// displays current balance
			break;
		case 3 :
	    	cin.ignore();
	    	if(accnum<2) {	// checks if only one account is open, if so, display the message and goes back to the transaction menu
	    		cout << "Only one account opened so far. There is no recepient to transfer to yet.\n";
	    		sleep(1);
	    		goto functions;
			}
			transfer();	// transfer transaction
			break;
		case 4 :
	    	cin.ignore();
			withdraw();	// withdraw transaction
			break;
		}
		cout << endl;
	} while(request != 0);
	cout << "You are logged out.\n";
	current = -1;
	sleep(1);
	return;
}

void openAccount() {	// open account with user's name, date of birth, and set a PIN number. Assign a 2-digit account number.
	string owner, birth, pin;
	int cnt, bday, pinno;
	
	cout << "Please fill in the form below.\n";
	cout << "Name : ";
	do {
		getline(cin, owner);
		if(string::npos != owner.find_first_of("0123456789")) {		// checks if any numeric value is in the name string
			cout << "Digit(s) found! A Name cannot contain a number.\n";
			cout << "Name : ";
		}
		else {
			name[accnum] = owner;		// put the input name into the name array
			cout << "\nWelcome! " << owner << ".\n\n";
		}
	} while(string::npos != owner.find_first_of("0123456789"));		// while any numeric value is in the name string
	
	do {
		cout << "Date of birth (YYMMDD) : ";
		cin >> birth;
		cin.ignore();
		cnt = 0;
		cnt = digitlimit(birth, 6);		// limit the digit of number input
	} while(cnt != 6);
	
	istringstream ss(birth);
	ss >> bday;
	
	do {
		cout << "Please set a 4-digits PIN : ";
		cin >> pin;
		cin.ignore();
		cnt = 0;
		cnt = digitlimit(pin, 4);		// limit the digit of number input
	} while(cnt != 4);
	
	istringstream iss(pin);
	iss >> pinno;
	
	accnum++;	// add 1 to the total number of account
	days[accnum-1] = bday;	// new user's b-day into the days array
	pins[accnum-1] = pinno;	// new user's pin no. into the pins array
	cout << "\nYour account has been opened. Your account number is \'" << setw(2) << setfill('0') << accnum << "\'.\n"		// give 2 digits account number
		<< "You have initial deposit of 100000 won.\n";
	sleep(1);
	cout << "\nYou are logged in.\n";
	current = accnum-1;  // set current as current user's index
	sleep(1);
	
	return;
}

int login(int e) {		// log in method switch
	int ans, accno, pin, error = 0;
	char exit;
	string logname;
	
	cout << "\nLog in by 1.Account Number + PIN / 2.Name + PIN : ";	// Log in by either one pair of information
	cin >> ans;
	cin.ignore();
	
	switch(ans) {		// switch for login method
		case 1:
		  second:
		  	cout << "\nPlease enter your Account Number : ";
			cin >> accno;		// get account number
			cin.ignore();
			cout << "Please enter your 4-digit PIN : ";
			cin >> pin;			// get PIN number
			cin.ignore();
			if(accno>0 && accno<=accnum && pin == pins[accno-1]) { 	// checks if account number input is not negative, account number input doesn't exceed total number of accounts, and PIN input and PIN for the corresponding account match
				cout << "\nWelcome back, " << name[accno-1] << "! You are logged in.\n";	// log in successful
				current = accno-1;	// set as current user when proceeding into the transaction menu
				sleep(1);
				break;
			}
			else {	// if any of the above condition is not true, show error message
				cout << "The Account Number or the PIN is incorrect. ";
				if(error>=2) {	// counts errors and lets the user input a pair of account number and PIN for 3 times
					cout << "(3/3)\n\nYou have exceeded the maximum number of login attempts. Session expired.\n";
					sleep(1);
					return 0;
				}
				error++;
				cout << "Please Try Again. (" << error << "/3)\n\n";
				goto second;	// goto loop
			}
			break;
		case 2:
		  third:
		  	cout << "\nPlease enter your Name : ";
			do {
				getline(cin, logname);
				if(string::npos != logname.find_first_of("0123456789")) {		// checks if any numeric value is in the name string
					cout << "Digit(s) found! A Name cannot contain a number.\n";
					cout << "Please enter your Name : ";
				}
			} while(string::npos != logname.find_first_of("0123456789"));
		  	
			accno = match(logname);		// check if the input name exists in the list, and returns the index as the corresponding account number to the name, if no match, returns -1
			cout << "Please enter your 4-digit PIN : ";
			cin >> pin;
			cin.ignore();
			if(accno != -1 && pin == pins[accno]) {		// checks if name doesn't exist, and the PIN input matches the PIN for the corresponding account
				cout << "\nWelcome back, " << name[accno] << "! You are logged in.\n";		// Log in successful
				current = accno;	// set as current user when proceeding into the transaction menu
				sleep(1);
				break;
			}
			else {	// if either of the above condition is not true, show error message
				cout << "The Name or the PIN is incorrect. ";
				if(error>=2) {	// counts errors and lets the user input a pair of account number and PIN for 3 times
					cout << "(3/3)\n\nYou have exceeded the maximum number of login attempts. Session expired.\n";
					sleep(1);
					return 0;
				}
				error++;
				cout << "Please Try Again. (" << error << "/3)\n\n";
				goto third;
			}
			break;			
	}
	return 2;
}

void deposit() {
	int deposit;
	string confirm;
	cout << "\nEnter the Amount to Deposit : ";		// deposit amount input
	cin >> deposit;
	while(cin.fail()) {	// to filter the input which is not an integer type value
		cin.clear();
		cin.ignore();
		cout << "Please input numbers only. Enter the Amount to deposit : " << endl;
		cin >> deposit;
	}
	deposit = blockneginput(deposit, "deposit");	// block negative input for deposit amount
	display("Deposit", deposit);	// display transaction type + amount on the screen
  again:
	cin >> confirm;
	cin.ignore();
	if(cistrcmp(confirm, "y")) {
		cout << "Transaction confirmed. Deposit Successful.\n";
		balance[current] += deposit;	// add amount to the balance
		checkBalance();
		sleep(1);
	}
	else if(cistrcmp(confirm, "n")) {		// stop transaction and go back to the transaction menu
		cout << "Transaction withdrawn.\n";
		sleep(1);
	}
	else {
		confirmation("deposit", deposit);		// if input is not "y" or "n", display reconfirmation message
		goto again;
	}
	return;
}

void checkBalance() {		// display balance after each transaction
	cout << "\n*****************************************\n\n";
	cout << "     Current Balance : " << balance[current] <<" won\n\n";
	cout << "*****************************************\n";
	sleep(1);
}

void transfer() {		// transfer to another customer of the bank
	int receip, transfer;	// recip for recipient's account number, transfer for transfer amount
	string confirm;		// confirm string with "y" or "n"
  here:
	cout << "\nEnter the Account Number of the recepient : ";
	cin >> receip;
	cin.ignore();
	if(receip == current+1) {	// check if the recipient's index is equal to current user's index
		cout << "This is your own account number. ";
		goto here;
	}
	else if(receip > accnum || receip < 1) {	// if the account number is not in account the range
		cout << "The recipient account number doesn't exist. Please try again.\n";
		goto here;
	}
	else {
		cout << "Enter the Amount to transfer : ";
		cin >> transfer;
		while(cin.fail()) {		// gets only numeric value in
			cin.clear();
		    cin.ignore();
		    cout << "Please input numbers only. Enter the Amount to transfer : " << endl;
		    cin >> transfer;
		}
		transfer = blocknegexceed(transfer, "transfer");	// check if the amount is negative or exceeding balance
	}
	cout << "\n*****************************************\n\n";		// transfer display specifying the amount and the recipient
	cout << "          SUNG YOUNG BANK LTD.\n\n";
	cout << "    Transfer " << transfer <<" won to " << name[receip-1] << "\n\n";
	cout << "*****************************************\n\n";
	sleep(1);
	cout << "You want to transfer " << transfer << " won to " << name[receip-1] << ". Is this correct? (y/n) : ";
  reask:
	cin >> confirm;
	cin.ignore();
	if(cistrcmp(confirm, "y")) {
		cout << "Transaction confirmed. Transfer Successful.\n";
		balance[current] -= transfer;	// deduct amount from the current user
		balance[receip-1] += transfer;	// add amount to the recipient
		checkBalance();		// display the current user's remaining balance
		sleep(1);
	}
	else if(cistrcmp(confirm, "n")) {
		cout << "Transaction withdrawn.\n";		// stop transaction and go back to the transaction menu
		sleep(1);
	}
	else {
		cout << "Please answer with 'y' or 'n'.\nYou want to transfer " << transfer << " won to "<< name[receip] <<". Is this correct? (y/n) : ";  // reconfirm if input is not 'y' nor 'n'
		goto reask;
	}
	return;
}

void withdraw() {
	int withdraw;	// withdraw amount
	string confirm;	// to confirm using "y" or "n"

	cout << "\nEnter the Amount to Withdraw : ";
	cin >> withdraw;
	
	while(cin.fail()) {		// check if the amount is only numeric value
	cin.clear();
    cin.ignore();
    cout << "Please input numbers only. Enter the Amount to Withdraw : " << endl;
    cin >> withdraw;
	}
	withdraw = blocknegexceed(withdraw, "withdraw");
	display("Withdraw", withdraw);
  redo:
	cin >> confirm;
	cin.ignore();
	if(cistrcmp(confirm, "y")) {	// if the confirm string input is "y"
		cout << "Transaction confirmed. Withdrawal Successful.\n";
		balance[current] -= withdraw;	// deduct amount from the balance
		sleep(1);
	}
	else if(cistrcmp(confirm, "n")) {	// if the confirm string input is "n"
		cout << "Transaction withdrawn.\n";		// stop transaction and go back to transaction menu
		sleep(1);
	}
	else {
		confirmation("withdraw", withdraw);		// if input is not "y" or "n", display reconfirmation message
		goto redo;
	}
	checkBalance();
	sleep(1);
	return;
}

void display(string str, int amount) {		// display template for deposit and withdraw, with an initial confirm message
	cout << "\n*****************************************\n\n";
	cout << "          SUNG YOUNG BANK LTD.\n\n";
	cout << "           "<< str << " " << amount <<" won\n\n";
	cout << "*****************************************\n\n";
	sleep(1);
	cout << "You want to " << str << " " << amount << " won. Is this correct? (y/n) : ";
	return;
}

int blockneginput(int amount, string str) {		// block negative amount input
	while (amount < 0 || cin.fail()) {
		cout << "Please input positive amount. Enter the Amount to " << str << " : ";
		cin >> amount;
		cin.ignore();
	}
	return amount;
}

int blocknegexceed(int amount, string str) {	// block negative amount input and exeeding amount
	bool a, b;
	a = amount < 0;
	b = amount > balance[current];
	while (a || b || cin.fail()) {
		if(a) {		// if amount is negative
			amount = blockneginput(amount, str);
		}
		else if(b) {	// if amount exceeds the current balance
			cout << "The amount exceeds your current balance.\nYour current balance is " << balance[current] << " won. Enter the Amount to " << str << " : ";
			cin >> amount;
			cin.ignore();
		}
		a = amount < 0;		// reset the boolean value
		b = amount > balance[current];
	}
	return amount;
}

void confirmation(string str, int amount) {		// reconfirm if input is not "y" or "n"
	cout << "Please answer with 'y' or 'n'.\nYou want to " << str << " " << amount << " won. Is this correct? (y/n) : ";
	return;
}

int digitlimit(string str, int limit) {		// limit digit of the number
	int i = 0;
	int cnt = 0;
	while (str[i] != 0) {
		if (string::npos == str.find_first_of("0123456789")) {	// checks if there is numeric value in the string
			break;
		}
	    else if ( str[i] >= '0' && str[i] <= '9') {		// count digits consisting of 0~9
			cnt++;	// add count
			i++;
		}
	}
	if(cnt != limit) {	// if the number digit exceeds the limit
		cout << "You can only enter " << limit << "-digit number.\n";
	}
	return cnt;
}

int match(string str) {		//to compare the name and check if it's on the list
	for(int i = 0; i<accnum; i++) {
		if(cistrcmp(name[i], str)) {	// case insensitive string comparison
			return i;
		}
	}
	return -1;
}

bool cistrcmp(const string& str1, const string& str2) {		//case insensitive comparison of the strings
    if (str1.size() != str2.size()) {		//doesn't match if the size is different
        return false;
    }
    for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
        if (tolower(*c1) != tolower(*c2)) {		//change both to lowercase to compare
            return false;
        }
    }
    return true;
}

void endmsg() {		// display ending message, show all account details with remaining balance
	cout << "\nTotal Number of Accounts : " << accnum << endl;
	
	cout << "\n*********************************************\n\n";
	cout << "           SUNG YOUNG BANK LTD.\n\n";
	cout << "Acc No.	Name		DOB	Balance\n";
	for(int i=0;i<accnum;i++) {
		cout << setw(2) << i+1 << "	";
		if(name[i].size()<8) {
			cout << name[i] << "		";
		}
		else {cout << name[i] << "	";}
		cout << setw(6) << days[i] << "	";
		cout << balance[i] << " won\n";
	}
	cout << "\n*********************************************\n\n";
	sleep(1);	
	cout << "\nThank you for using SUNG YOUNG BANK banking system.\nGood-bye!\n";
	return;
}

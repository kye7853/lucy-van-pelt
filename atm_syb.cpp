#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#include <algorithm>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

void openAccount();
int login(int e);
void deposit();
void checkBalance();
void transfer();
void withdraw();
void record();
void display(string str, int amount);
void blockneginput();
int digitlimit(string str, int limit);
int match(string str);
bool cistrcmp(const string& str1, const string& str2);

string name[500];
int current, accnum = 0;
int pins[50], days[50], balance[50];

int main(int argc, char** argv) {

	fill_n(balance, 50, 100000);
	int initreq, request;

label:
	do{
		cout << "\n*********** Welcome to SUNG YOUNG BANK! ************\n";
		cout << "*                                                  *\n";
		cout << "*  1. Open a Bank Account                          *\n";
		cout << "*  2. Log in as a User                             *\n";
		cout << "*  0. Exit the SYB Banking System                  *\n";
		cout << "*                                                  *\n";
		cout << "****************************************************\n";

		cout << "\nPlease select from above (0~2) : ";

		cin >> initreq;
		while (cin.fail()) {
			    cin.clear();	// clear input buffer to restore cin to a usable state
			    cin.ignore(INT_MAX, '\n');	// ignore last input
			    cout << "You can only enter numbers from 0 to 2.\n";
			    cout << "Please select from above (0~2) : ";
			    cin >> initreq;
		}

		switch(initreq) {
			case 1:
				cin.ignore();
				openAccount();
				break;
			case 2:
				cin.ignore();
				if(accnum>0) {
					initreq = login(initreq);
				}
				else {
					cout << "No account is opened yet. Please open an account first.\n";
					goto label;
				}
				break;
			case 0:
				cout << "\nTotal Number of Accounts : " << accnum << endl;
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
				sleep(1);

				cout << "\nThank you for using SUNG YOUNG BANK banking system.\nGood-bye!\n";

				return 0;
		}
		if(initreq < 3 && initreq >= 1) {
		  functions:
			do {
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
				cout << "*  5. Transaction Record Enquiry                   *\n";
				cout << "*                                                  *\n";
				cout << "*  0. Log Out                                      *\n";
				cout << "*                                                  *\n";
				cout << "****************************************************\n\n";

				cout << "Please select a number from above (0~5) : ";
				cin >> request;
				while (cin.fail()) {
				    cin.clear();	// clear input buffer to restore cin to a usable state
				    cin.ignore(INT_MAX, '\n');	// ignore last input
				    cout << "You can only enter numbers from 0 to 5.\n";
				    cout << "Please select a number from above (0~5) : ";
				    cin >> request;
				}

				switch(request) {
			    case 1 :
			    	cin.ignore();
					deposit();
					break;
				case 2 :
			    	cin.ignore();
					checkBalance();
					break;
				case 3 :
			    	cin.ignore();
			    	if(accnum<2) {
			    		cout << "Only one account opened so far. There is no recepient to transfer to yet.\n";
			    		sleep(1);
			    		goto functions;
					}
					transfer();
					break;
				case 4 :
			    	cin.ignore();
					withdraw();
					break;
				case 5 :
			    	cin.ignore();
					record();
					break;
				}
				cout << endl;
			} while(request != 0);
			cout << "You are logged out.\n";
			current = -1;
			sleep(1);
		}
	} while(1);
}

void openAccount() {
	string owner, birth, pin;
	int cnt, bday, pinno;

	cout << "Please fill in the form below.\n";
	cout << "Name : ";
	do {
		getline(cin, owner);
		if(string::npos != owner.find_first_of("0123456789")) {
			cout << "Digit(s) found! A Name cannot contain a number.\n";
			cout << "Name : ";
		}
		else {
			name[accnum] = owner;
			cout << "\nWelcome! " << owner << ".\n\n";
		}
	} while(string::npos != owner.find_first_of("0123456789"));

	do {
		cout << "Date of birth (YYMMDD) : ";
		cin >> birth;
		cin.ignore();
		cnt = 0;
		cnt = digitlimit(birth, 6);
	} while(cnt != 6);

	istringstream ss(birth);
	ss >> bday;

	do {
		cout << "Please set a 4-digits PIN : ";
		cin >> pin;
		cin.ignore();
		cnt = 0;
		cnt = digitlimit(pin, 4);
	} while(cnt != 4);

	istringstream iss(pin);
	iss >> pinno;

	accnum++;
	days[accnum-1] = bday;
	pins[accnum-1] = pinno;
	cout << "\nYour account has been opened. Your account number is \'" << setw(2) << setfill('0') << accnum << "\'.\n"
		<< "You have initial deposit of 100,000 won.\n";
	sleep(1);
	cout << "\nYou are logged in.\n";
	current = accnum-1;
	sleep(1);

	return;
}

int login(int e) {
	int ans, accno, pin, error = 0;
	char exit;
	string logname;

	cout << "\nLog in by 1.Account Number + PIN / 2.Name + PIN : ";
	cin >> ans;
	cin.ignore();

	switch(ans) {
		case 1:
		  second:
		  	cout << "\nPlease enter your Account Number : ";
			cin >> accno;
			cin.ignore();
			if(accno > accnum || accno < 1) {
				cout << "The account number doesn't exist. Please try again.\n";
				goto second;
			}
			cout << "Please enter your 4-digit PIN : ";
			cin >> pin;
			cin.ignore();
			if(pin == pins[accno-1]) {
				cout << "\nWelcome back, " << name[accno-1] << "! You are logged in.\n";
				current = accno-1;
				sleep(1);
				break;
			}
			else {
				cout << "Your PIN doesn't match your Account Number. ";
				if(error>=2) {
					cout << "(3/3)\n\nToo many false inputs. Session expired.\n";
					return 0;
				}
				error++;
				cout << "Please Try Again. (" << error << "/3)\n\n";
				goto second;
			}
			break;
		case 2:
		  third:
		  	cout << "\nPlease enter your Name : ";
			cin >> logname;
			cin.ignore();
			accno = match(logname);
			if(accno==-1) {
				cout << "Input Name does not exist. Please try again.\n";
				goto third;
			}
			cout << "Please enter your 4-digit PIN : ";
			cin >> pin;
			cin.ignore();
			if(pin == pins[accno]) {
				cout << "\nWelcome back, " << name[accno] << "! You are logged in.\n";
				current = accno;
				sleep(1);
				break;
			}
			else {
				cout << "Your PIN doesn't match your Account Number. ";
				if(error>=2) {
					cout << "(3/3)\n\nToo many false inputs. Session expired.\n";
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
	cout << "\nEnter the Amount to Deposit : ";
	cin >> deposit;
	cin.ignore();
	display("Deposit", deposit);
  again:
	cin >> confirm;
	cin.ignore();
	if(cistrcmp(confirm, "y")) {
		cout << "Transaction confirmed. Deposit Successful.\n";
		balance[current] += deposit;
		checkBalance();
		sleep(1);
	}
	else if(cistrcmp(confirm, "n")) {
		cout << "Transaction withdrawn.\n";
		sleep(1);
	}
	else {
		cout << "Please answer with 'y' or 'n'.\nYou want to deposit " << deposit << " won. Is this correct? (y/n) : ";
		goto again;
	}
	return;
}

void checkBalance() {
	cout << "\nYour current balance is " << balance[current] << " won.\n";
	sleep(1);
}

void transfer() {
	int receip, transfer;
	string confirm;
  here:
	cout << "\nEnter the Account Number of the recepient : ";
	cin >> receip;
	cin.ignore();
	if(receip == current+1) {
		cout << "This is your own account number. ";
		goto here;
	}
	else if(receip > accnum || receip < 1) {
		cout << "The account number doesn't exist. Please try again.\n";
		goto here;
	}
	else {
		cout << "Enter the Amount to transfer : ";
		cin >> transfer;
		while(cin.fail()) {
			cin.clear();
		    cin.ignore();
		    cout << "Please input numbers only. Enter the Amount to Withdraw : " << endl;
		    cin >> withdraw;
		}
	}
	display("Transfer", transfer);
  reask:
	cin >> confirm;
	cin.ignore();
	if(cistrcmp(confirm, "y")) {
		cout << "Transaction confirmed. Transfer Successful.\n";
		balance[current] -= transfer;
		balance[transfer-1] += transfer;
		checkBalance();
		sleep(1);
	}
	else if(cistrcmp(confirm, "n")) {
		cout << "Transaction withdrawn.\n";
		sleep(1);
	}
	else {
		cout << "Please answer with 'y' or 'n'.\nYou want to transfer " << deposit << " won. Is this correct? (y/n) : ";
		goto reask;
	}
	return;
}

void withdraw() {
	int withdraw;
	string confirm;

	cout << "\nEnter the Amount to Withdraw : ";
	cin >> withdraw;

	while(cin.fail()) {
	cin.clear();
    cin.ignore();
    cout << "Please input numbers only. Enter the Amount to Withdraw : " << endl;
    cin >> withdraw;
	}
	display("Withdraw", withdraw);
  redo:
	cin >> confirm;
	cin.ignore();
	if(cistrcmp(confirm, "y")) {
		cout << "Transaction confirmed. Withdrawal Successful.\n";
		balance[current] -= withdraw;
		sleep(1);
	}
	else if(cistrcmp(confirm, "n")) {
		cout << "Transaction withdrawn.\n";
		sleep(1);
	}
	else {
		cout << "Please answer with 'y' or 'n'.\nYou want to withdraw " << deposit << " won. Is this correct? (y/n) : ";
		goto redo;
	}
	checkBalance();
	sleep(1);
	return;
}

void record() {
	//이건 어디에 쓰는 건가요?
}

void display(string str, int amount) {
	cout << endl << "*****************************************\n\n";
	cout << "           SUNG YOUNG BANK LTD.\n\n";
	cout << "            "<< str << amount <<" won\n\n";
	cout << "*****************************************\n\n";
	sleep(1);
	cout << "You want to " << str << " " << amount << " won. Is this correct? (y/n) : ";
	return;
};

void blockneginput() {

}

int digitlimit(string str, int limit) {
	int i = 0;
	int cnt = 0;
	while (str[i] != 0) {
		if (string::npos == str.find_first_of("0123456789")) {
			break;
		}
	    else if ( str[i] >= '0' && str[i] <= '9') {
			cnt++;
			i++;
		}
	}
	if(cnt != limit) {
		cout << "You can only enter " << limit << "-digit number.\n";
	}
	return cnt;
}

int match(string str) {		//to compare the name and check if it's on the list
	for(int i = 0; i<accnum; i++) {
		if(cistrcmp(name[i], str)) {
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

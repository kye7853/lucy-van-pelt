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
		cout << "\n*********** Welcome to Sung Young Bank! ************\n";
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
					cout << days[i] << "	";
					cout << balance[i] << " won\n";
				}
				sleep(1);
				
				cout << "\nThank you for using SYB banking system.\nGood-bye!\n";
				
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
	int i, cnt, bday, pinno;
	
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
		i = 0;
		while (birth[i] != 0) {
			if (string::npos == birth.find_first_of("0123456789")) {
				break;
			}
		    else if ( birth[i] >= '0' && birth[i] <= '9') {
				cnt++;
				i++;
			}
		}
		if(cnt != 6) {
			cout << "You can only enter 6-digit numbers.\n";
		}
	} while(cnt != 6);
	
	istringstream ss(birth);
	ss >> bday;
	
	do {
		cout << "Please set a 4-digits PIN : ";
		cin >> pin;
		cin.ignore();
		cnt = 0;
		i = 0;
		while (pin[i] != 0) {
		    if (string::npos == pin.find_first_of("0123456789")) {
				break;
			}
		    else if ( pin[i] >= '0' && pin[i] <= '9') {
				cnt++;
				i++;
			}
		}
		if(cnt != 4) {
			cout << "You must enter a 4-digit numbers.\n";
		}
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
		  	cout << "Please enter your Account Number : ";
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
		  	cout << "Please enter your Name : ";
			cin >> logname;
			cin.ignore();
			accno = match(logname);
			if(accno==0) {
				cout << "Input Name does not exist. Please try again.\n";
				goto third;
			}
			cout << "Please enter your 4-digit PIN : ";
			cin >> pin;
			cin.ignore();
			if(pin == pins[accno]) {
				cout << "\nWelcome back, " << name[accno] << "! You are logged in.\n";
				current = accno;
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
	cout << "Enter the Amount of cash to Deposit : ";
	cin >> deposit;
	cin.ignore();
	cout << "You want to deposit " << deposit << " won. Is this correct? (y/n) : ";
  again:
	cin >> confirm;
	cin.ignore();
	if(cistrcmp(confirm, "y")) {
		cout << "Transaction confirmed. Deposit Successful.";
		balance[current] += deposit;
		sleep(1);
	}
	else if(cistrcmp(confirm, "n")) {
		cout << "Transaction withdrawn.";
		sleep(1);
	}
	else {
		cout << "Please answer with 'y' or 'no'.\nYou want to deposit " << deposit << " won. Is this correct? (y/n) : ";
		goto again;
	}
	return;
}

void checkBalance() {
	cout << "\nYour current balance is " << balance[current] << " won.\n";
	sleep(1);
}

void transfer() {
	int transfer, amount;
	string confirm;
  here:
	cout << "Enter the Account Number of the recepient : ";
	cin >> transfer;
	cin.ignore();
	if(transfer == current+1) {
		cout << "This is your own account number. ";
		goto here;
	}
	else if(transfer > accnum || transfer < 1) {
		cout << "The account number doesn't exist. Please try again.\n";
		goto here;
	}
	else {
		cout << "Enter the Amount of cash to transfer : ";
		cin >> amount;
		cin.ignore();
	}
	
	cout << "You want to transfer " << amount << " won to '" << name[transfer-1] << "'. Is this correct? (y/n) : ";
  reask:
	cin >> confirm;
	cin.ignore();
	if(cistrcmp(confirm, "y")) {
		cout << "Transaction confirmed. Transfer Successful.";
		balance[current] -= amount;
		balance[transfer-1] += amount;
		sleep(1);
	}
	else if(cistrcmp(confirm, "n")) {
		cout << "Transaction withdrawn.";
		sleep(1);
	}
	else {
		cout << "Please answer with 'y' or 'no'.\nYou want to deposit " << deposit << " won. Is this correct? (y/n) : ";
		goto reask;
	}
	return;
}

void withdraw() {
	int withdraw;
	string confirm;
	cout << "Enter the Amount of cash to Withdraw : ";
	cin >> withdraw;
	cin.ignore();
	cout << "You want to withdraw " << withdraw << " won. Is this correct? (y/n) : ";
  redo:
	cin >> confirm;
	cin.ignore();
	if(cistrcmp(confirm, "y")) {
		cout << "Transaction confirmed. Withdrawal Successful.";
		balance[current] -= withdraw;
		sleep(1);
	}
	else if(cistrcmp(confirm, "n")) {
		cout << "Transaction withdrawn.";
		sleep(1);
	}
	else {
		cout << "Please answer with 'y' or 'no'.\nYou want to withdraw " << deposit << " won. Is this correct? (y/n) : ";
		goto redo;
	}
	return;
}

void record() {
}

int match(string str) {		//to compare the name and check if it's on the list
	for(int i = 0; i<accnum; i++) {
		if(cistrcmp(name[i], str)) {
			return i;
		}
	}
	return 0;
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

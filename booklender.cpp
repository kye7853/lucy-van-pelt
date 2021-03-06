#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <map>
#include <functional>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

/*Struct*/
struct Book;

/*Functions*/
/*Start & Basic*/
void commandSwitch();
void callFunction(istream& in);
bool valiidateCommand(vector<string> commandVector);
void notifyUnreturnedBooks();
/*Load*/
void load();
void showBookList();
void loadBookFromTxtFile(ifstream& myFile);
void parseBookInfo(string s, int lineCount);
/*Insert*/
void insert(string s);
/*lend*/
void lend(string s);
/*save*/
void save(string s);
/*returned*/
void returned(string s);
/*passDay*/
void passDay();
void showLentBooks();
/*print*/
void print();
/*exit*/
void eexit();

/*Display*/
void showBookList();
void showSuccess(string function, Book book);
void showLentBooks();

/*Util*/
vector<string> parseInput(string s, int i);
vector<string> split(string s, string delim);
string toLowerCase(string str);
ostream& operator<<(ostream &strm, const vector<Book> &v);
ostream& operator<<(ostream &strm, const Book &b);

/*variables*/
vector<Book> bookVector;
vector<Book> booksNeedToBeReturned;
map<string, function<void(string)>> functionMapWithParam =
{
	{ "insert", insert },
	{ "lend", lend },
	{ "save", save },
	{ "returned", returned }
};
map<string, function<void()>> functionMapWithoutParam =
{
	{ "load", load },
	{ "print", print },
	{ "passday", passDay },
	{ "exit", eexit }
};

/***********Book struct***********/
struct Book {
	string title;
	string author;
	string pubYear;
	string edition;
	string borrower;
	string lentDays;

	Book(string title, string author, string pubYear, string edition, string borrower, string lentDays) :
		title(title), author(author), pubYear(pubYear), edition(edition), borrower(borrower), lentDays(lentDays) {}

	Book(string title, string author, string pubYear, string edition) :
		title(title), author(author), pubYear(pubYear), edition(edition), borrower("None"), lentDays("0") {}
};

/***********Main***********/
int main(int argc, char** argv) {
	load();

	do {
		commandSwitch();
		callFunction(cin);
	} while (1);

	return 0;
}

/*********Start & Basic*********/
void commandSwitch() {
	cout << "\n============== Available Commands & Format ==============\n\n";
	cout << "1. INSERT BookTitle; Author; PubYear; Edition\n";
	cout << "2. LEND BookTitle; Person Borrowing; How many days\n";
	cout << "3. SAVE new_filename.txt\n";
	cout << "4. RETURNED BookTitle\n";
	cout << "5. PASSDAY\n";
	cout << "6. PRINT\n";
	cout << "7. EXIT\n\n";
	cout << "---------------------------------------------------------\n";
	cout << ">>";

	return;
}

void callFunction(istream& in) {
	string command = "";
	vector<string> commandVector;
	getline(in, command);
	int size = (split(command, " ")).size();

	bool b = false;

	//	cout << "**********************************" << size;   //Test


	commandVector.resize(size);
	commandVector = split(command, " ");
	commandVector[0] = toLowerCase(commandVector[0]);
	b = valiidateCommand(commandVector);

	if (b == true) {
		if (size == 2) {
			cout << commandVector[1] << endl;
			functionMapWithParam[commandVector[0]](commandVector[1]);
		}
		else {
			functionMapWithoutParam[commandVector[0]]();
		}
		notifyUnreturnedBooks();
	}
	else {
		cout << "Please check the action and parameter, and try again.\n";
		return;
	}
}

bool valiidateCommand(vector<string> commandVector) {
	string functionsWithoutParam[] = { "load", "print", "passday", "exit" };
	string functionsWithParam[] = { "insert", "save", "lend", "returned" };
	bool valid = true;
	bool bool1 = find(begin(functionsWithoutParam), end(functionsWithoutParam), commandVector[0]) != end(functionsWithoutParam);
	bool bool2 = find(begin(functionsWithParam), end(functionsWithParam), commandVector[0]) != end(functionsWithParam);
	if (bool1 || bool2) {
		if ((bool1 && commandVector.size() != 1) || (bool2 && commandVector.size() != 2)) {
			valid = false;
		}

	}
	else {
		valid = false;
	}

	return valid;
}

void notifyUnreturnedBooks() {
	string notifyMessage;
	notifyMessage = "";
	//cout << "*************************" << notifyMessage;
	if (booksNeedToBeReturned.empty()) {
		return;
	}
	else {
		for (Book b : booksNeedToBeReturned) {
			if (b.lentDays == "0") {
				notifyMessage.append(b.title + " should be returned by " + b.borrower + " by today. \n");
			}
			else {
				notifyMessage.append(b.title + " SHOULD HAVE BEEN ALREADY RETURNED BY " + b.borrower + ".\n");
			}
		}
	}

	if (!notifyMessage.empty()) {
		cout << notifyMessage;
	}

}

/***********Load***********/
void load() {
	ifstream myFile("lenders.txt");		//input file stream
	if (myFile.is_open())
	{
		loadBookFromTxtFile(myFile);
		showBookList();
		myFile.close();
	}
	else cout << "Unable to open file";		//message when file not opened
}

void loadBookFromTxtFile(ifstream& myFile) {
	string bookInfoString = "";
	int lineCount = 0;

	for (int i = 0; getline(myFile, bookInfoString); i++) {
		//getline(myFile, bookInfoString);
		parseBookInfo(bookInfoString, lineCount);
		lineCount++;
	}
}

void parseBookInfo(string s, int lineCount) {

	string delimiter = "; ";
	vector<string> bookInfoVector(6);
	int j = 0;
	size_t last = 0;
	size_t next = 0;

	bookInfoVector = parseInput(s, 6);
	Book book = { bookInfoVector[0], bookInfoVector[1], bookInfoVector[2], bookInfoVector[3], bookInfoVector[4], bookInfoVector[5] };
	bookVector.resize(lineCount + 1, book);

}

/***********INSERT BookTitle; Author; PubYear; Edition***********/
void insert(string s) {
	vector<string> insertBookInfoVector(4);
	insertBookInfoVector = parseInput(s, 4);

	Book newBook = { insertBookInfoVector[0], insertBookInfoVector[1], insertBookInfoVector[2], insertBookInfoVector[3] };
	bookVector.resize(bookVector.size() + 1, newBook);
	showBookList();
}

/***********LEND BookTitle; Person Borrowing; How many days***********/
void lend(string s) {
	vector<string> lendBookInfoVector(3);
	lendBookInfoVector = parseInput(s, 3);
	string bookTitle = lendBookInfoVector[0];
	vector<Book>::iterator it = find_if(bookVector.begin(), bookVector.end(), [&bookTitle](const Book& obj) {return obj.title == bookTitle; });
	string errorMessage = "";
	if (lendBookInfoVector[2].empty()) {
		errorMessage.append("Please input in the correct format");
	}
	if (it == bookVector.end()) {
		errorMessage.append("NO SUCH BOOK\n");
	}
	if (stoi(lendBookInfoVector[2]) < 1) {
		errorMessage.append("Lend for more days!\n");
	}
	if (errorMessage.empty()) {
		(*it).borrower = lendBookInfoVector[1];
		(*it).lentDays = lendBookInfoVector[2];
		showSuccess("Lent", *it);
	}

	if (!errorMessage.empty()) {
		cout << errorMessage;
	}
}

/***********SAVE new_filename.txt***********/
void save(string s) {
	ofstream wfile;
	wfile.open(s);      //open and write to the file
	wfile << bookVector;
	wfile.close();
}

/***********RETURNED BookTitle***********/
void returned(string s) {
	vector<Book>::iterator it = find_if(bookVector.begin(), bookVector.end(), [&s](const Book& obj) {return obj.title == s; });
	string errorMessage = "";

	if (it != bookVector.end())
	{
		if ((*it).borrower == "None") {
			errorMessage.append("\n That book is not borrowed!");
		}
		else {
			(*it).borrower = "None";
			(*it).lentDays = "0";
			showSuccess("Returned", *it);
		}
	}
	else {
		errorMessage.append("\n NO SUCH BOOK!");
	}

	if (!errorMessage.empty()) {
		cout << errorMessage;
	}

}

/***********PASSDAY***********/
void passDay() {
	int lentDaysInt = 0;
	for (int i = 0; i < bookVector.size(); i++) {
		if (bookVector[i].borrower != "None") {
			lentDaysInt = stoi(bookVector[i].lentDays);
			lentDaysInt -= 1;
			bookVector[i].lentDays = to_string(lentDaysInt);
			string bookTitle = bookVector[i].title;
			if (lentDaysInt == 0) {
				booksNeedToBeReturned.push_back(bookVector[i]);
			}
			else if (lentDaysInt < 0) {
				vector<Book>::iterator it = find_if(booksNeedToBeReturned.begin(), booksNeedToBeReturned.end(), [&bookTitle](const Book& obj) {return obj.title == bookTitle; });
				(*it).lentDays = to_string(lentDaysInt);
			}
		}
	}
	showLentBooks();
}

/***********PRINT***********/
void print() {
	showBookList();
}

/***********EXIT***********/
void eexit() {
	cout << "You are exiting the application.\n";
	system("pause");
	exit(0);
}

/***********Display***********/
void showBookList() {
	cout << "\n======================================== Book Catalog ========================================\n";
	cout << "Title\t\t\tAuthor\t\tPublished Year\tEdition\tBorrower\tDays Borrowed\n";
	cout << bookVector;
	cout << "============================================ End =============================================\n";

	return;
}

void showSuccess(string function, Book book) {
	cout << "\n======================================== Book Catalog ========================================\n";
	cout << "Title\t\t\tAuthor\t\tPublished Year\tEdition\tBorrower\tDays Borrowed\n";
	cout << book;
	cout << "============================================ End =============================================\n";

	return;
}

void showLentBooks() {
	cout << "\n======================================== Book Catalog ========================================\n";
	cout << "Title\t\t\tAuthor\t\tPublished Year\tEdition\tBorrower\tDays Borrowed\n";
	for (Book b : bookVector) {
		if (b.borrower != "None") {
			cout << b;
		}
	}
	cout << "============================================ End =============================================\n";
}

/***********Utils***********/

//parse input string to return vector of parameters
vector<string> parseInput(string s, int i) {
	string delimiter = "; ";
	int j = 0;
	size_t last = 0;
	size_t next = 0;
	vector<string> bookInfoVector(i);

	while ((next = s.find(delimiter, last)) != string::npos) {
		bookInfoVector[j] = s.substr(last, next - last);
		last = next + 1;
		j++;
	}
	bookInfoVector[j] = s.substr(last);

	return bookInfoVector;
}

vector<string> split(string s, string delim) {
	vector<string> tokens;
	size_t pos = 0;
	string token;
	pos = s.find(delim);

	if (pos != string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + delim.length());
		tokens.push_back(token);
	}
	tokens.push_back(s);

	return tokens;
}

string toLowerCase(string str) {
	int i = 0;
	char c;
	while (str[i])
	{
		c = str[i];
		str[i] = tolower(c);
		i++;
	}
	return str;
};

ostream& operator<<(ostream &strm, const vector<Book> &v) {
	for (int i = 0; i < v.size(); i++) {
		strm << v[i];
	}
	return strm;
}

ostream& operator<<(ostream &strm, const Book &b) {
	strm << b.title <<
		"\t" << b.author <<
		"\t" << b.pubYear <<
		"\t\t" << b.edition <<
		"\t" << b.borrower <<
		"\t" << b.lentDays << "\n";
	return strm;
}

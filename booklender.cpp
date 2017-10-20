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
/*Start Message*/
void commandSwitch();
string toLowerCase(string str);

/*Load*/
void load();
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
/*print*/
void print();
/*exit*/
void eexit();
/*Util*/
ostream& operator<<(ostream &strm, const vector<Book> &v);
ostream& operator<<(ostream &strm, const Book &b);
vector<string> parseInput(string s, int i);
map<string, function<void(string)>> createFunctionMapWithParam();
map<string, function<void()>> createFunctionMapWithoutParam();
/*variables*/
vector<Book> bookVector;
vector<Book> booksNeedToBeReturned;

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
	string command;

	commandSwitch();
	cin >> command;
	cout << toLowerCase(command);

	return 0;
}

/*********Start Message*********/
void commandSwitch() {
	cout << "============== Available Commands & Format ==============\n\n";
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

/***********Load***********/
void load() {
	ifstream myFile("lenders.txt");		//input file stream
	if (myFile.is_open())
	{
		loadBookFromTxtFile(myFile);
		cout << bookVector;
		myFile.close();
	}
	else cout << "Unable to open file";		//message when file not opened
}

void loadBookFromTxtFile(ifstream& myFile) {
	string bookInfoString = "";
	int lineCount = 0;

	for (int i = 0; !myFile.eof(); i++) {
		getline(myFile, bookInfoString);
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
	bookVector.resize(lineCount, book);

}

/***********INSERT BookTitle; Author; PubYear; Edition***********/
void insert(string s) {
	vector<string> insertBookInfoVector(4);
	insertBookInfoVector = parseInput(s, 4);

	Book newBook = { insertBookInfoVector[0], insertBookInfoVector[1], insertBookInfoVector[2], insertBookInfoVector[3] };
	bookVector.resize(bookVector.size() + 1, newBook);
	cout << bookVector;
}

/***********LEND BookTitle; Person Borrowing; How many days***********/
void lend(string s) {
	vector<string> lendBookInfoVector(3);
	string bookTitle = lendBookInfoVector[0];
	vector<Book>::iterator it = find_if(bookVector.begin(), bookVector.end(), [&bookTitle](const Book& obj) {return obj.title == bookTitle; });
	string errorMessage = "";

	if (stoi(lendBookInfoVector[2]) < 1) {
		errorMessage.append("Lend for more days!");
	}

	if (it != bookVector.end())
	{
		if (errorMessage.empty()) {
			(*it).borrower = lendBookInfoVector[1];
			(*it).lentDays = lendBookInfoVector[2];
			//int index = distance(bookVector.begin(), it);
			cout << *it;
		}
	}
	else {
		errorMessage.append("\n NO SUCH BOOK!");
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
			cout << "Return Successful \n" << *it;
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
		lentDaysInt = stoi(bookVector[i].lentDays);
		lentDaysInt -= 1;
		bookVector[i].lentDays = to_string(lentDaysInt);
		if (lentDaysInt < 1) {
			booksNeedToBeReturned.push_back(bookVector[i]);
		}
		bookVector[i].lentDays = to_string(lentDaysInt);
	}
}

/***********PRINT***********/
void print() {
	cout << bookVector;
}

/***********EXIT***********/
void eexit() {
	cout << "You are exiting the application";
	return;
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

map<string, function<void(string)>> createFunctionMapWithParam() {
	map<string, function<void(string)>> functionMap1 =
	{
		{ "insert", insert },
		{ "lend", lend },
		{ "save", save },
		{ "returned", returned }
	};

	return functionMap1;
}

map<string, function<void()>> createFunctionMapWithoutParam() {
	map<string, function<void()>> functionMap =
	{
		{ "load", load },
		{ "print", print },
		{ "passday", passDay },
		{ "exit", eexit }
	};

	return functionMap;
}

ostream& operator<<(ostream &strm, const vector<Book> &v) {
	for (int i = 0; i < v.size(); i++) {
		strm << v[i];
	}
	return strm;
}

ostream& operator<<(ostream &strm, const Book &b) {
	strm << "title: " << b.title <<
		"\t pubYear: " << b.pubYear <<
		"\t author: " << b.author <<
		"\t edition: " << b.edition <<
		"\t borrower: " << b.borrower <<
		"\t lentDays: " << b.lentDays << "\n";
	return strm;
}

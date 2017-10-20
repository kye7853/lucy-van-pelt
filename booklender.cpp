#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <vector>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

/*Struct*/
struct Book;

/*Functions*/
/*Load*/
void load();
void loadBookFromTxtFile(ifstream& myFile);
void parseBookInfo(string s, Book* tempBookList, int lineCount);
/*passDay*/
void passDay();

/*Util*/
ostream& operator<<(ostream &strm, const vector<Book> &v);
vector<string> parseInput(string s, int i);

/*variables*/
vector<Book> bookVector;

/***********Book struct***********/
struct Book {
	string title;
	string pubYear;
	string author;
	string edition;
	string borrower;
	string lentDays;
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
	Book* tempBookList = new Book[200];
	string bookInfoString = "";
	int lineCount = 0;

	for (int i = 0; !myFile.eof(); i++) {
		getline(myFile, bookInfoString);
		parseBookInfo(bookInfoString, tempBookList, lineCount);
		lineCount++;
	}

	bookVector.resize(lineCount);
	bookVector.assign(tempBookList, tempBookList + lineCount);
	delete tempBookList;
}
void parseBookInfo(string s, Book* tempBookList, int lineCount) {

	string delimiter = "; ";
	vector<string> bookInfoVector(6);
	int j = 0;
	size_t last = 0;
	size_t next = 0;

	bookInfoVector = parseInput(s, 6);
	Book bookInfo = {bookInfoVector[0], bookInfoVector[1], bookInfoVector[2], bookInfoVector[3], bookInfoVector[4], bookInfoVector[5]};
	tempBookList[lineCount] = bookInfo;

}

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

/***********INSERT BookTitle; Author; PubYear; Edition***********/
/***********LEND BookTitle; Person Borrowing; How many days***********/
/***********SAVE new_filename.txt***********/
/***********RETURNED BookTitle***********/
/***********PASSDAY***********/
void passDay() {
	int lentDaysInt = 0;
	for (int i = 0; i < bookVector.size(); i++) {
		lentDaysInt = stoi(bookVector[i].lentDays);
		lentDaysInt -= 1;
		bookVector[i].lentDays = to_string(lentDaysInt);
	}
}
/***********PRINT***********/
/***********EXIT***********/

/***********Utils***********/
ostream& operator<<(ostream &strm, const vector<Book> &v) {
	for (int i = 0; i < v.size() ; i++) {
		Book b = v[i];
		strm << "title: " << b.title <<
			"\t pubYear: " << b.pubYear <<
			"\t author: " << b.author <<
			"\t edition: " << b.edition <<
			"\t borrower: " << b.borrower <<
			"\t lentDays: " << b.lentDays << "\n";
	}
	return strm;
}
/***********Main***********/
int main(int argc, char** argv) {


	return 0;
}

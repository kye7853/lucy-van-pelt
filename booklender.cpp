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

struct Book{
	string title;
	string pubYear;
	string author;
	string edition;
	string borrower;
	string lentDays;
};

const string delims(";,:. \n\t");
inline bool isDelim(char c) {
    for (int i = 0; i < delims.size(); ++i)
        if (delims[i] == c)
            return true;
    return false;
}

inline string parseBookInfo(string s,Book* tempBookList,int lineCount) {

	string delimiter = "; ";
	vector<string> bookInfoVector(3);
//	char* bookInfoArray = new char[6];
	size_t pos = 0;
	string info;
	int j = 0;

	while ((pos = s.find(delimiter)) != string::npos) {
	    info = s.substr(0, pos);
		bookInfoVector[j] = info;
	//	char* infoChar = new char[info.length()];
	//	strcpy(infoChar, info);
	//	bookInfoArray[j] = infoChar;
	//	delete infoChar;
		j++;
	   // cout << info << endl;
	    s.erase(0, pos + delimiter.length());
	}

	Book bookInfo = {bookInfoVector[0], bookInfoVector[1], bookInfoVector[2], bookInfoVector[3], bookInfoVector[4], bookInfoVector[5]};
	//delete bookInfoArray;
	tempBookList[lineCount] = bookInfo;

}

int main(int argc, char** argv) {

	//string line[500];
	Book* tempBookList = new Book[200];
	string bookInfoString = "";
	int lineCount = 0;			//to count the lines of the text file

	ifstream myFile("lenders.txt");		//input file stream
	if (myFile.is_open())
	{
		for(int i=0; !myFile.eof(); i++) {
			getline(myFile,bookInfoString);
			parseBookInfo(bookInfoString,tempBookList,lineCount);
			//getline(myfile, line[i]);
			//cout << line[i] << "\n";
	    	lineCount++;
	    }
		myFile.close();
		vector<Book> bookList(lineCount);
		//Book* bookList = new Book[lineCount];
	//	copy(tempBookList[0],tempBookList[lineCount], bookList);
	//	delete tempBookList;
	//	cout <<bookList[0].title;
	cout << tempBookList[0].title;
	}
    else cout << "Unable to open file";		//message when file not opened

	return 0;
}

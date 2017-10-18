#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

struct Book{
	string title;
	int pubYear;
	string author;
	int edition;
	string borrower;
	int lentDays;
};

const string delims(";,:. \n\t");
inline bool isDelim(char c) {
    for (int i = 0; i < delims.size(); ++i)
        if (delims[i] == c)
            return true;
    return false;
}

inline string parseBookinfo(string s) {

	string delimiter = "; ";
	char* bookInfoArray = new string[6];
	size_t pos = 0;
	string info;
	int j = 0;

	while ((pos = s.find(delimiter)) != string::npos) {
	    info = s.substr(0, pos);
		bookInfoArray[j] = info;
		j++;
	   // cout << info << endl;
	    s.erase(0, pos + delimiter.length());
	}

	Book bookInfo = {bookInfoArray[0], bookInfoArray[1], bookInfoArray[2], bookInfoArray[3], bookInfoArray[4], bookInfoArray[5]};
	delete bookInfoArray;
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
			parseBookInfo(bookInfoString);
			//getline(myfile, line[i]);
			//cout << line[i] << "\n";
	    	lineCount++;
	    }
		myFile.close();
		Book* bookList = new Book[lineCount];
		copy(tempBookList,tempBookList[lineCount], bookList);
		delete tempBookList;
		printf(bookList[0]);
	}
    else cout << "Unable to open file";		//message when file not opened

	return 0;
}

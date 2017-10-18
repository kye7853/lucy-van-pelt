#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

struct Borrowbooks{
	string title;
	int pubyear;
	string author;
	int edition;
	string borrower;
	int lentdays;
};

const string delims(";,:. \n\t");
inline bool isDelim(char c) {
    for (int i = 0; i < delims.size(); ++i)
        if (delims[i] == c)
            return true;
    return false;
}

int main(int argc, char** argv) {
	
	string line[500];
	int linecount = 0;			//to count the lines of the text file
	
	ifstream myfile("lenders.txt");		//input file stream
	if (myfile.is_open())
	{
		for(int i=0; !myfile.eof(); i++) {
			getline(myfile, line[i]);
			cout << line[i] << "\n";
	    	linecount++;
	    }
		myfile.close();
	}
    else cout << "Unable to open file";		//message when file not opened

	string delim = "; ";
	
	return 0;
}

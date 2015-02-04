// Program : CS161 HW #10
// Name    : Brandan Tyler Lasley
// Date    : 12/8/2013 19:48
// Description: Searches or displays a libary database part 2 from ASSIGN 9
// Sources : None

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//these declarations should be at file scope
const int ARRAY_SIZE = 1000; //defines the static space allocated for the array

struct Book {
	string bookTitle;
	string Author;
};
Book books [ARRAY_SIZE];

int totalRecords = 0; //totalRecords

//function prototypes
int loadData(string pathname);  
int SearchAuthor (int count, string name);
int SearchTitle (int count, string title);
void sortByTitle();
void sortByAuthor();
void showAll();

int main (){
	//initialize variables
	string name;
	string title;
	string pathname;
	int count = 0;
    char reply;

	//prompt the user
	cout << "Welcome to Brandan's Library Database." << endl;

	cout << "Please, enter the full pathname to the data file on disk: " << endl;
	cin >> pathname;

	while (loadData(pathname) == -1) {
		// Prompt user for filename
		cout << "Please, enter the full pathname to the data file on disk: " << endl;
		cin >> pathname;
	}
	
	//display result if records loaded successfully
	cout << totalRecords << " records loaded successfully." << endl; //*loadData(string pathname)

    do{ //do
        cout << "Enter Q to (Q)uit, Search (A)uthor, Search (T)itle, (S)how All: ";
        cin >> reply; //enter q, a, t or s
        switch (reply){
               
            //"	A or a: Search by Author. The program displays all records which contain the designated text somewhere in the author field. You should use a function with the following signature for this purpose: int showBooksByAuthor (int count, string name). This function should display all books whose author field contains the string passed in the parameter called name. It returns the number of books displayed. count specifies the number of books in the database.
            case 'a': case 'A':
				cout << "Please enter Author to search for: ";
				cin >> name;
                cout << SearchAuthor (count, name) << " Records found." << endl; //showBooksByAuthor function
                break;
 
            //"	T or t: Search by Title. The program displays all records which contain the designated text somewhere in the title field. You should use a function with the following signature for this purpose: int showBooksByTitle (int count, string title). This function should display all books whose title field contains the string passed in the parameter called title. It returns the number of books displayed. count specifies the number of books in the database.
            case 't': case 'T':
				cout << "Please enter title to search for: ";
				cin >> title;
                cout << SearchTitle (count, title) << " Records found." << endl; //showBooksByTitle function
                break;
                
            //"	S or s: The program displays all the records in the database using the function showAll you have already developed in step (1).
            case 's': case 'S':
                showAll(); //showAll funtion
                break;
        } 
    } while (reply != 'q' && reply != 'Q'); //Step (2) - "	Q or q: Quit. The program terminates.

	// Exit
	return 0;
}

//Function Loads file data
int loadData(string pathname){
	ifstream data;

	// Open file
	data.open(pathname);

	// Exit on I/O error
	 if (!data.is_open()) {
		 cout << "Error opening file!" << endl;
		return -1;
	 }

	// Refresh buffer line thing
	data.seekg(0);

	int i = 0;
	 // Read Data
     while(!data.eof()) {
		 string tmpbook;
		 getline(data, books[i].bookTitle);
		 getline(data, books[i].Author);
		i++;
		totalRecords++;
     }

	return 0;
}

int SearchAuthor(int count, string name){
	int found = 0;
	sortByAuthor();
	for (int i = 0; i <  totalRecords; i++) {
		if (books[i].Author.find(name) != string::npos) {
			cout << books[i].bookTitle << " (" << books[i].Author << ")" << endl;
			found++;
		}
	}
	return found;
}

int SearchTitle(int count, string title){
	int found = 0;
	sortByTitle();
	for (int i = 0; i <  totalRecords; i++) {
		if (books[i].bookTitle.find(title) != string::npos) {
			cout << books[i].bookTitle << " (" << books[i].Author << ")" << endl;
			found++;
		}
	}
	return found;
}

void showAll(){
	sortByTitle();
	for (int i = 0; i <  totalRecords; i++) {
		cout << books[i].bookTitle << " (" << books[i].Author << ")" << endl;
	}
}

void sortByTitle () {
	Book temp;
	int i;  int j;

    for (i=0; i<totalRecords; i++) {
        for (j=i+1; j<totalRecords; j++) {
            if (strcmp(books[i].bookTitle.c_str(), books[j].bookTitle.c_str()) > 0) {
                temp=books[i];
                books[i]=books[j];
                books[j]=temp;
            }
        }
    }
}

 void sortByAuthor () {
	Book temp;
	int i;  int j;

    for (i=0; i<totalRecords; i++) {
        for (j=i+1; j<totalRecords; j++) {
            if (strcmp(books[i].Author.c_str(), books[j].Author.c_str()) > 0) {
                temp=books[i];
                books[i]=books[j];
                books[j]=temp;
            }
        }
    }
}
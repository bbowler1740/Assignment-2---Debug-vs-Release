#define _CRT_SECURE_NO_WARNINGS 
#define MAX_NAME_SIZE 50
#define PRERELEASE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef struct STUDENT_DATA {

    char* firstName;
    char* lastName;
#ifdef PRERELEASE
    char* email;
#endif

} DATA, *PDATA;

#ifdef PRERELEASE

PDATA createStudentDataRecord(char* first, char* last, char* email) {

    PDATA studentRecordPtr = (PDATA)malloc(sizeof(DATA));

    studentRecordPtr->firstName = new char[MAX_NAME_SIZE];
    strcpy(studentRecordPtr->firstName, first);

    studentRecordPtr->lastName = new char[MAX_NAME_SIZE];
    strcpy(studentRecordPtr->lastName, last);

    studentRecordPtr->email = new char[MAX_NAME_SIZE];
    strcpy(studentRecordPtr->email, email);

    return studentRecordPtr;

}

#endif

PDATA createStudentDataRecord(char* first, char* last) {

    PDATA studentRecordPtr = (PDATA)malloc(sizeof(DATA));

    studentRecordPtr->firstName = new char[MAX_NAME_SIZE];
    strcpy(studentRecordPtr->firstName, first);

    studentRecordPtr->lastName = new char[MAX_NAME_SIZE];
    strcpy(studentRecordPtr->lastName, last);

    return studentRecordPtr;

}

void printStudentDataRecord(PDATA record) {

    cout << "Name: " << record->firstName << " " << record->lastName << endl;

#ifdef PRERELEASE
    cout << "Email: " << record->email << endl;
#endif

}

int main() {

#ifdef PRERELEASE
    cout << "Running the program in Pre-release mode." << endl;
#else
    cout << "Running the program in standard mode."
#endif

    string fileLine;
    string fileDelimiter = ",";

#ifdef PRERELEASE
    ifstream studentDataFile("StudentData_Emails.txt", ios::in);
#else
    ifstream studentDataFile("StudentData.txt", ios::in);
#endif

    vector<PDATA> studentDataVector;

    if (studentDataFile.is_open()) {

        //Read a line from the StudentData.txt file
        while (getline(studentDataFile, fileLine))
        {
            //Parse the line based on the comma delimiter. Last name precedes the comma and will be the first item parsed. First name is after the comma (i.e. Bowler,Brayden).
            size_t pos = fileLine.find(fileDelimiter); // Determine the position of the comma in the current line.
            string token = fileLine.substr(0, pos);
            char* tempLastName = new char[token.length() + 1];
            strcpy(tempLastName, token.c_str());
            
            fileLine.erase(0, pos + fileDelimiter.length()); //fileLine now only contains the last name.
            pos = fileLine.find(fileDelimiter);
            token = fileLine.substr(0, pos);
            char* tempFirstName = new char[token.length() + 1];
            strcpy(tempFirstName, token.c_str());

#ifdef PRERELEASE
            fileLine.erase(0, pos + fileDelimiter.length()); //fileLine now only contains the last name.
            char* tempEmail = new char[fileLine.length() + 1];
            strcpy(tempEmail, fileLine.c_str());
#endif

            //Create a struct with the parsed first name and last name.
#ifdef PRERELEASE
            PDATA tempStudentDataPtr = createStudentDataRecord(tempFirstName, tempLastName, tempEmail);
#else
            PDATA tempStudentDataPtr = createStudentDataRecord(tempFirstName, tempLastName);
#endif

            //Push each STUDENT_DATA struct ptr to a vector of STUDENT_DATA struct ptrs.
            studentDataVector.push_back(tempStudentDataPtr);
            
#ifdef _DEBUG

            printStudentDataRecord(tempStudentDataPtr);

#endif
            
        }

    }

    else cout << "Unable to open file." << endl;

    return 1;
}

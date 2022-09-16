#define _CRT_SECURE_NO_WARNINGS 
#define MAX_NAME_SIZE 50

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef struct STUDENT_DATA {

    char* firstName;
    char* lastName;

} DATA, *PDATA;

PDATA createStudentDataRecord(char* first, char* last) {

    PDATA studentRecordPtr = (PDATA)malloc(sizeof(DATA));

    studentRecordPtr->firstName = new char[MAX_NAME_SIZE];
    strcpy(studentRecordPtr->firstName, first);

    studentRecordPtr->lastName = new char[MAX_NAME_SIZE];
    strcpy(studentRecordPtr->lastName, last);

    return studentRecordPtr;

}

void printStudentDataRecord(PDATA record) {

    cout << record->firstName << " " << record->lastName << endl;

}

int main() {

    string fileLine;
    string fileDelimiter = ",";
    ifstream studentDataFile("StudentData.txt", ios::in);
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
            char* tempFirstName = new char[fileLine.length() + 1];
            strcpy(tempFirstName, fileLine.c_str());
            //Create a struct with the parsed first name and last name.
            
            PDATA tempStudentDataPtr = createStudentDataRecord(tempFirstName, tempLastName);

            //Push each STUDENT_DATA struct ptr to a vector of STUDENT_DATA struct ptrs.
            studentDataVector.push_back(tempStudentDataPtr);
            
#ifdef _DEBUG

            printStudentDataRecord(tempStudentDataPtr);

#endif
            
        }

    }

    else cout << "Unable to open file." << endl;
    
    //Push each STUDENT_DATA struct to a vector of STUDENT_DATA structs.

    return 1;
}

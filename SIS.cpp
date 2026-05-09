#include<iomanip> //setwidth and boxwidth 
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>   // added for file I/O
using namespace std;

const int MaxStudents = 200;
int year = 2026;

struct Student {
    string Name;
    string ID;
    string NationalID;
    char Gender;
    string DOB;
    string PhoneNumber;
    string Program;
    int Level;
    double GPA;
};

Student students[MaxStudents];
int StudentCount = 0;


void saveStudents() {
    ofstream file("students.txt"); //CASE SENSITIVE OFFSTREAM OUTPUT FDILE STREAM OUTPUT INTO THE FILE
    if (!file.is_open()) {
        cout << "Warning: could not open students.txt for saving.\n"; //ERROR IF FILE NOT FOUND
        return;
    }
    file << StudentCount << "\n";
    for (int i = 0; i < StudentCount; i++) { //ARRAY OF STRUCT
        file << students[i].Name << "\n";
        file << students[i].ID << "\n";
        file << students[i].NationalID << "\n";
        file << students[i].Gender << "\n";
        file << students[i].DOB << "\n";
        file << students[i].PhoneNumber << "\n";
        file << students[i].Program << "\n";
        file << students[i].Level << "\n";
        file << students[i].GPA << "\n";
    }
    file.close(); //SAVES THE FILE
}

void loadStudents() {
    ifstream file("students.txt"); // INPUT TO THE FILE
    if (!file.is_open()) {
        // No file yet — that's fine on first run
        return;
    }
    file >> StudentCount; //READS EVERYTHING AS A STRING (YENFA3 TAKHOD 8EIR STRING BS BETET3EMEL B FLE.IGNORE\N W HAYKOON FYHA MOSHKELA EN FILE MSH BEYE2RA SPACES
    file.ignore(); // consume the newline after the count IGNORE NEWLINE SPP IT DOESNT ENTER THE DOE BENE2RA MN FIKE BADAL CONSOLE
    for (int i = 0; i < StudentCount; i++) {
        getline(file, students[i].Name);
        getline(file, students[i].ID);
        getline(file, students[i].NationalID);
        string genderStr; //mabye2drash yedakhal strings 3adi so we need to do that MSH 3AMLENHOM ALREADY STRINGS BS FILE INPUT BEYE2RA KOL 7AGA 3ALATOOL FA GETLINE MSH HAYE2RAHA
        getline(file, genderStr);
        students[i].Gender = genderStr.empty() ? 'M' : genderStr[0]; //IF NO GENDER ADDED ASSUME ITS A MALE ELSE KHOD AWEL WA7DA
        getline(file, students[i].DOB);
        getline(file, students[i].PhoneNumber);
        getline(file, students[i].Program);
        string levelStr;
        getline(file, levelStr);
        students[i].Level = stoi(levelStr); //STRING TO INTEGER LEVEL AS AN INTEGER
        string gpaStr;
        getline(file, gpaStr);
        students[i].GPA = stod(gpaStr); // STORE THE GPA AS FLOAT STRING TO DOUBLE
    }
    file.close();
    if (StudentCount > 0)
        cout << "Loaded " << StudentCount << " student(s) from students.txt\n";
}


bool NameValidation(string Name) {
    int words = 0;
    bool WordFlag = false;
    for (int i = 0; i < (int)Name.size(); i++) {
        if (Name[i] == ' ') {
            WordFlag = false;
        }
        else {
            if (!WordFlag) {
                words++;
                WordFlag = true;
            }
        }
    }
    return words == 2;
}

void printformat(const Student& s) {

    const int boxWidth = 50;

    cout << "\n" << (char)201;
    for (int i = 0; i < boxWidth; i++) cout << (char)205;
    cout << (char)187 << endl;

    cout << (char)186 << " " << left << setw(boxWidth - 1) << ("Name: " + s.Name) << (char)186 << endl;
    cout << (char)186 << " " << left << setw(boxWidth - 1) << ("ID: " + s.ID) << (char)186 << endl;
    cout << (char)186 << " " << left << setw(boxWidth - 1) << ("National ID: " + s.NationalID) << (char)186 << endl;

    string genderStr(1, s.Gender);
    cout << (char)186 << " " << left << setw(boxWidth - 1) << ("Gender: " + genderStr) << (char)186 << endl;

    cout << (char)186 << " " << left << setw(boxWidth - 1) << ("DOB: " + s.DOB) << (char)186 << endl;

    cout << (char)186 << " " << left << setw(boxWidth - 1) << ("Program: " + s.Program) << (char)186 << endl;

    cout << (char)186 << " " << left << setw(boxWidth - 1) << ("Level: " + to_string(s.Level)) << (char)186 << endl;
    cout << (char)186 << " " << left << setw(boxWidth - 1) << ("GPA: " + to_string(s.GPA)) << (char)186 << endl;

    cout << (char)200;
    for (int i = 0; i < boxWidth; i++) cout << (char)205;
    cout << (char)188 << endl;
}


string generateID(int year, int sequence) {
    int shortYear = year % 100;
    string id = to_string(shortYear) + "P";
    if (sequence < 1000) id += "0";
    if (sequence < 100) id += "0";
    if (sequence < 10) id += "0";

    id += to_string(sequence);
    return id;
}

bool NatIDValidation(string NationalID) {
    if (NationalID.size() != 14) {
        return false;
    }
    if (NationalID[0] == '0') {
        return false;
    }
    for (int i = 0; i < (int)NationalID.size(); i++) {
        if (!(NationalID[i] >= '0' && NationalID[i] <= '9')) {
            return false;
        }
    }
    return true;
}

bool UniqueNatID(string NationalID) {
    for (int i = 0; i < StudentCount; i++)
        if (students[i].NationalID == NationalID)
            return false;
    return true;
}

bool PhoneNOValidation(string PhoneNumber) {

    if (PhoneNumber.size() != 11) {
        return false;
    }
    if (PhoneNumber[0] != '0' || PhoneNumber[1] != '1') {
        return false;
    }
    for (int i = 0; i < (int)PhoneNumber.size(); i++) {
        if (!(PhoneNumber[i] >= '0' && PhoneNumber[i] <= '9')) {
            return false;
        }
    }
    return true;
}

bool GenderValidation(char Gender) {
    if (Gender == 'M' || Gender == 'F' || Gender == 'f' || Gender == 'm') {
        return true;
    }
    else {
        return false;
    }
}

bool DOBValidation(string DOB) {
    if (DOB.size() != 10) {
        return false;
    }
    if (DOB[2] != '/' || DOB[5] != '/') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            continue;
        }
        if (!(DOB[i] >= '0' && DOB[i] <= '9')) {
            return false;
        }
    }
    int day = (DOB[0] - '0') * 10 + (DOB[1] - '0');
    int month = (DOB[3] - '0') * 10 + (DOB[4] - '0');
    int year = (DOB[6] - '0') * 1000 + (DOB[7] - '0') * 100 + (DOB[8] - '0') * 10 + (DOB[9] - '0');

    if (month < 1 || month >12) {
        return false;
    }
    if (day < 1 || day>31) {
        return false;
    }
    int currentYear = 2026;
    if (currentYear - year < 17) {
        return false;
    }
    return true;
}
bool ProgramValidation(string& Program) {
    for (int i = 0; i < (int)Program.size(); i++) {
        if (Program[i] >= 'a' && Program[i] <= 'z') {
            Program[i] = Program[i] - 32;
        }

    }
    if (Program == "CSE" || Program == "CCE" || Program == "MCT")
        return true;
    return false;
}



void AddStudent() {
    cout << "\n=== Add Student ===" << endl;
    if (StudentCount >= MaxStudents) {
        cout << "The maximum number of students has been reached ";
        return;
    }

    Student s;
    string input;

    while (true) {
        cout << "Enter Student Name: ";
        getline(cin, s.Name);
        if (NameValidation(s.Name)) {
            break;
        }
        cout << "Name must be exatly 2 words (first and last name) " << endl;
    }

    while (true) {
        cout << "Enter National ID: ";
        getline(cin, s.NationalID);
        if (!NatIDValidation(s.NationalID)) {
            cout << "The National ID must be 14 digits, with no leading zero" << endl;
            continue;
        }
        if (!UniqueNatID(s.NationalID)) {
            cout << "This National ID already exists" << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter the Gender (M/F): ";
        getline(cin, input);
        if (input.size() == 1 && GenderValidation(input[0])) {
            s.Gender = input[0];
            break;
        }
        cout << "Gender must be M or F " << endl;
    }

    while (true) {
        cout << "Enter Date of Birth (DD/MM/YYYY): ";
        getline(cin, s.DOB);
        if (DOBValidation(s.DOB)) {
            break;
        }
        cout << "Invalid date or Age (the student must be 17 or older) " << endl;
    }

    while (true) {
        cout << "Enter Phone Number: ";
        getline(cin, s.PhoneNumber);
        if (PhoneNOValidation(s.PhoneNumber)) {
            break;
        }
        cout << "The phone number must be 11 digits starting with 01 " << endl;
    }

    while (true) {
        cout << "Enter Your Program (CSE/CCE/MCT): ";
        getline(cin, s.Program);
        if (ProgramValidation(s.Program)) {
            break;
        }
        cout << "Program must be CSE, CCE, or MCT " << endl;
    }

    while (true) {
        cout << "Enter your Academic Level (1-4): ";
        getline(cin, input);
        s.Level = input[0] - '0';
        if (s.Level >= 1 && s.Level <= 4) {
            break;
        }
        cout << "Level must be 1, 2, 3, or 4 " << endl;
    }

    s.ID = generateID(year, StudentCount + 1);
    s.GPA = 0.0;

    students[StudentCount] = s;
    StudentCount++;

    saveStudents(); // saves student in the file

    cout << "\nStudent added sucessfully!" << endl;
    cout << "Student ID: " << s.ID << endl;
}
void searchStudent() {
    if (StudentCount == 0) {
        cout << "\nNo students registered yet." << endl;
        return;
    }

    string choiceInput, SearchCriteria;

    while (true) {
        bool found = false;

        cout << "\n=== Search Student ===\n";

        // ONLY ask for the choice here
        cout << "1. Search by ID\n2. Search by Name\n3. Search by NationalID\n4. Back\n\nEnter your choice: ";
        getline(cin, choiceInput);

        if (choiceInput.empty() || choiceInput == "4") return;

        switch (choiceInput[0]) {
        case '1':
            cout << "\nEnter ID: "; // Specific prompt
            getline(cin, SearchCriteria); // Only one input call
            for (int i = 0; i < StudentCount; i++) {
                if (students[i].ID == SearchCriteria) {
                    printformat(students[i]);
                    found = true;
                    break;
                }
            }
            break;

        case '2':

            while (true) { // Loop until a valid name is entered or user cancels
                cout << "Enter Student Full Name (First and Last): ";
                int matchesFound = 0;
                getline(cin, SearchCriteria);

                if (NameValidation(SearchCriteria)) {
                    for (int i = 0; i < StudentCount; i++) {
                        if (students[i].Name == SearchCriteria) {
                            matchesFound++;
                        }
                    }if (matchesFound > 0) {
                        cout << "Found " << matchesFound << " student(s): ";
                    }

                    for (int i = 0; i < StudentCount; i++) {
                        if (students[i].Name == SearchCriteria) {
                            printformat(students[i]);

                            found = true;
                        }
                    }
                    break;
                }

                cout << "Invalid format! Name must be exactly 2 words. Try again." << endl;


            }
            break;


        case '3':
            cout << "Enter National ID: ";
            getline(cin, SearchCriteria);

            if (!NatIDValidation(SearchCriteria)) {
                cout << "Invalid ID! Please Enter a valid ID\n";
                break;
            }
            for (int i = 0; i < StudentCount; i++) {
                if (students[i].NationalID == SearchCriteria) {
                    printformat(students[i]);
                    found = true;
                    break;
                }
            }
            break;

        default:

            return;
        }

        if (!found) {
            cout << "No matching records found." << endl;
        }
    }
}
void displayStudentTable(Student students[], int StudentCount) {
    if (StudentCount == 0) {
        cout << "No students to display" << endl;
        return;
    }

    cout << "\nTotal Students: " << StudentCount << endl;
    cout << (char)201; // Top-left corner
    for (int i = 0; i < 73; i++) cout << (char)205; // Long horizontal line
    cout << (char)187 << endl; // Top-right corner

    // 2. Header Row
    cout << (char)186 << " " << left << setw(10) << "ID"
        << " " << (char)186 << " " << setw(20) << "Name"
        << " " << (char)186 << " " << setw(15) << "Program"
        << " " << (char)186 << " " << setw(8) << "Level"
        << " " << (char)186 << " " << setw(6) << "GPA" << " " << (char)186 << endl;


    cout << (char)204;
    for (int i = 0; i < 73; i++) cout << (char)205;
    cout << (char)185 << endl;

    // 4. Data Rows
    for (int i = 0; i < StudentCount; i++) {
        cout << (char)186 << " " << left << setw(10) << students[i].ID
            << " " << (char)186 << " " << setw(20) << students[i].Name
            << " " << (char)186 << " " << setw(15) << students[i].Program
            << " " << (char)186 << " " << setw(8) << students[i].Level
            << " " << (char)186 << " " << fixed << setprecision(2) << setw(6) << students[i].GPA << " " << (char)186 << endl;
    }


    cout << (char)200;
    for (int i = 0; i < 73; i++) cout << (char)205;
    cout << (char)188 << endl;
}


void sortByName(Student students[], int StudentCount) {
    for (int i = 0; i < StudentCount - 1; i++) {
        for (int j = 0; j < StudentCount - i - 1; j++) {
            if (students[j].Name > students[j + 1].Name) {

                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    displayStudentTable(students, StudentCount);
}
void sortByID(Student students[], int StudentCount) {
    for (int i = 0; i < StudentCount - 1; i++) {
        for (int j = 0; j < StudentCount - i - 1; j++) {
            if (students[j].ID > students[j + 1].ID) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    displayStudentTable(students, StudentCount);
}
void sortByGPA(Student students[], int StudentCount) {
}


void listAllStudents() {
    int choice;
    string choiceinput;
    cout << "\n=== List all students ===" << endl;
    cout << "Sort by:\n1. Student ID\n2. Name (A - Z)\n3. GPA (Highest First)\n4. Back" << endl;
    cout << "\nEnter your choice: ";
    getline(cin, choiceinput);
    if (choiceinput.empty()) return;
    choice = choiceinput[0] - '0';
    switch (choice) {
    case 1: sortByID(students, StudentCount);  break;
    case 2: sortByName(students, StudentCount); break;
    case 3: sortByGPA(students, StudentCount); break;
    case 4: return;
    default: cout << "lesaa";


    }

}
void studentManagement() {
    int choice;
    string choiceInput;
    while (true) {
        cout << "\n=== Student Management ===";
        cout << "\n1. Add Student\n2. Search Student\n3. Update Student\n4. Delete Student\n5. List All Students\n6. Back to Main Menu\n\n";
        cout << "Enter your choice: ";
        getline(cin, choiceInput);
        choice = choiceInput[0] - '0';
        switch (choice) {
        case 1:
            AddStudent();
            break;
        case 2:
            searchStudent(); break;
        case 3:
            cout << "Milestone 2!"; break;
        case 4:
            cout << "Milestone 2!"; break;
        case 5:
            listAllStudents(); break;
        case 6: return;

        default:
            cout << "Please choose a number from 1 to 6";
            break;
        }
    }

}


int main() {

    loadStudents(); // <-- auto-load saved students on startup

    cout << char(201);
    for (int i = 0; i < 36; i++) {
        cout << char(205);
    }cout << char(187) << endl;

    cout << char(186) << setw(37) << char(186) << endl;
    cout << char(186) << "     STUDENT INFORMATION SYSTEM     " << char(186) << endl;
    cout << char(186) << setw(37) << char(186) << endl;

    cout << char(200);
    for (int i = 0; i < 36; i++) {
        cout << char(205);
    }cout << char(188) << endl << endl;


    string ChoiceInput;
    int choice;
    while (true) {
        cout << "1. Student Management" << endl;
        cout << "2. Course Management" << endl;
        cout << "3. Grades Management" << endl;
        cout << "4. Exit" << endl;
        cout << "\nEnter your choice: ";
        getline(cin, ChoiceInput);
        choice = ChoiceInput[0] - '0';

        switch (choice) {
        case 1:
            studentManagement();
            break;
        case 2:
            cout << "Milestone 2" << endl;
            break;
        case 3:
            cout << "Milestone 2" << endl;
            break;
        case 4:
            cout << "Goodbye! " << endl;
            return 0;
        default:
            cout << "Please choose a number from 1 to 4\n\n";
            break;
        }
    }
}
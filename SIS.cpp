#include<iomanip> //setwidth and boxwidth 
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>   // added for file I/O
using namespace std;

const int MaxStudents = 200;
const int MaxCourses = 50;
const int MaxGrades = 500;

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

struct Course {
    string Code;
    string Name;
    int Credits;
};

struct Grade {
    string StudentID;
    string CourseCode;
    double Midterm;
    double Final;
    double Total;
};

struct User {
    string Username;
    string Password;
    string StudentID;
    bool isAdmin;
};

Student students[MaxStudents];
int StudentCount = 0;

Course courses[MaxCourses];
int CourseCount = 0;

Grade grades[MaxGrades];
int GradeCount = 0;

User users[MaxStudents + 1];
int UserCount = 0;

string loggedInStudentID = "";

bool isIntegerString(string value) {
    if (value.empty()) {
        return false;
    }
    for (int i = 0; i < (int)value.size(); i++) {
        if (!(value[i] >= '0' && value[i] <= '9')) {
            return false;
        }
    }
    return true;
}

bool isDecimalString(string value) {
    if (value.empty()) {
        return false;
    }
    bool decimalPointFound = false;
    bool digitFound = false;
    for (int i = 0; i < (int)value.size(); i++) {
        if (value[i] >= '0' && value[i] <= '9') {
            digitFound = true;
        }
        else if (value[i] == '.' && !decimalPointFound) {
            decimalPointFound = true;
        }
        else {
            return false;
        }
    }
    return digitFound;
}

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
        // No file yet � that's fine on first run
        return;
    }
    int savedStudentCount;
    file >> savedStudentCount; //READS EVERYTHING AS A STRING (YENFA3 TAKHOD 8EIR STRING BS BETET3EMEL B FLE.IGNORE\N W HAYKOON FYHA MOSHKELA EN FILE MSH BEYE2RA SPACES
    file.ignore(); // consume the newline after the count IGNORE NEWLINE SPP IT DOESNT ENTER THE DOE BENE2RA MN FIKE BADAL CONSOLE
    if (savedStudentCount < 0) {
        cout << "Warning: invalid student count in students.txt\n";
        return;
    }
    if (savedStudentCount > MaxStudents) {
        savedStudentCount = MaxStudents;
        cout << "Warning: students.txt has more students than the program can load\n";
    }

    StudentCount = 0;
    for (int i = 0; i < savedStudentCount; i++) {
        if (!getline(file, students[i].Name)) break;
        if (!getline(file, students[i].ID)) break;
        if (!getline(file, students[i].NationalID)) break;
        string genderStr; //mabye2drash yedakhal strings 3adi so we need to do that MSH 3AMLENHOM ALREADY STRINGS BS FILE INPUT BEYE2RA KOL 7AGA 3ALATOOL FA GETLINE MSH HAYE2RAHA
        if (!getline(file, genderStr)) break;
        students[i].Gender = genderStr.empty() ? 'M' : genderStr[0]; //IF NO GENDER ADDED ASSUME ITS A MALE ELSE KHOD AWEL WA7DA
        if (!getline(file, students[i].DOB)) break;
        if (!getline(file, students[i].PhoneNumber)) break;
        if (!getline(file, students[i].Program)) break;
        string levelStr;
        if (!getline(file, levelStr) || !isIntegerString(levelStr)) break;
        students[i].Level = stoi(levelStr); //STRING TO INTEGER LEVEL AS AN INTEGER
        string gpaStr;
        if (!getline(file, gpaStr) || !isDecimalString(gpaStr)) break;
        students[i].GPA = stod(gpaStr); // STORE THE GPA AS FLOAT STRING TO DOUBLE
        StudentCount++;
    }
    file.close();
    if (StudentCount > 0)
        cout << "Loaded " << StudentCount << " student(s) from students.txt\n";
}

void saveGrades() {
    ofstream file("grades.txt");
    if (!file.is_open()) {
        cout << "Warning: could not open grades.txt for saving.\n";
        return;
    }
    file << GradeCount << "\n";
    for (int i = 0; i < GradeCount; i++) {
        file << grades[i].StudentID << "\n";
        file << grades[i].CourseCode << "\n";
        file << grades[i].Midterm << "\n";
        file << grades[i].Final << "\n";
        file << grades[i].Total << "\n";
    }
    file.close();
}

void loadGrades() {
    ifstream file("grades.txt");
    if (!file.is_open()) {
        return;
    }
    int savedGradeCount;
    file >> savedGradeCount;
    file.ignore();
    if (savedGradeCount < 0) {
        cout << "Warning: invalid grade count in grades.txt\n";
        return;
    }
    if (savedGradeCount > MaxGrades) {
        savedGradeCount = MaxGrades;
        cout << "Warning: grades.txt has more grades than the program can load\n";
    }

    GradeCount = 0;
    for (int i = 0; i < savedGradeCount; i++) {
        if (!getline(file, grades[GradeCount].StudentID)) break;
        if (!getline(file, grades[GradeCount].CourseCode)) break;
        string midtermStr, finalStr, totalStr;
        if (!getline(file, midtermStr) || !isDecimalString(midtermStr)) break;
        if (!getline(file, finalStr) || !isDecimalString(finalStr)) break;
        if (!getline(file, totalStr) || !isDecimalString(totalStr)) break;
        grades[GradeCount].Midterm = stod(midtermStr);
        grades[GradeCount].Final = stod(finalStr);
        grades[GradeCount].Total = stod(totalStr);
        GradeCount++;
    }
    file.close();
    if (GradeCount > 0)
        cout << "Loaded " << GradeCount << " grade(s) from grades.txt\n";
}

void saveCourses() {
    ofstream file("courses.txt");
    if (!file.is_open()) {
        cout << "Warning: could not open courses.txt for saving.\n";
        return;
    }
    file << CourseCount << "\n";
    for (int i = 0; i < CourseCount; i++) {
        file << courses[i].Code << "\n";
        file << courses[i].Name << "\n";
        file << courses[i].Credits << "\n";
    }
    file.close();
}

void loadCourses() {
    ifstream file("courses.txt");
    if (!file.is_open()) {
        return;
    }
    int savedCourseCount;
    file >> savedCourseCount;
    file.ignore();
    if (savedCourseCount < 0) {
        cout << "Warning: invalid course count in courses.txt\n";
        return;
    }
    if (savedCourseCount > MaxCourses) {
        savedCourseCount = MaxCourses;
        cout << "Warning: courses.txt has more courses than the program can load\n";
    }

    CourseCount = 0;
    for (int i = 0; i < savedCourseCount; i++) {
        if (!getline(file, courses[i].Code)) break;
        if (!getline(file, courses[i].Name)) break;
        string creditsStr;
        if (!getline(file, creditsStr) || !isIntegerString(creditsStr)) break;
        courses[i].Credits = stoi(creditsStr);
        CourseCount++;
    }
    file.close();
    if (CourseCount > 0)
        cout << "Loaded " << CourseCount << " course(s) from courses.txt\n";
}

void saveUsers() {
    ofstream file("authenticator.txt");
    if (!file.is_open()) {
        cout << "Warning: could not open authenticator.txt for saving.\n";
        return;
    }
    file << UserCount << "\n";
    for (int i = 0; i < UserCount; i++) {
        file << users[i].Username << "\n";
        file << users[i].Password << "\n";
        file << users[i].StudentID << "\n";
        file << (users[i].isAdmin ? "1" : "0") << "\n";
    }
    file.close();
}

void loadUsers() {
    ifstream file("authenticator.txt");
    if (!file.is_open()) {
        users[0].Username = "admin";
        users[0].Password = "Admin@123";
        users[0].StudentID = "";
        users[0].isAdmin = true;
        UserCount = 1;
        saveUsers();
        return;
    }
    int savedUserCount;
    if (!(file >> savedUserCount)) {
        file.close();
        users[0].Username = "admin";
        users[0].Password = "Admin@123";
        users[0].StudentID = "";
        users[0].isAdmin = true;
        UserCount = 1;
        saveUsers();
        return;
    }
    file.ignore();
    if (savedUserCount < 0) {
        file.close();
        users[0].Username = "admin";
        users[0].Password = "Admin@123";
        users[0].StudentID = "";
        users[0].isAdmin = true;
        UserCount = 1;
        saveUsers();
        return;
    }
    if (savedUserCount > MaxStudents + 1) {
        savedUserCount = MaxStudents + 1;
        cout << "Warning: authenticator.txt has more users than the program can load\n";
    }

    UserCount = 0;
    for (int i = 0; i < savedUserCount; i++) {
        if (!getline(file, users[i].Username)) break;
        if (!getline(file, users[i].Password)) break;
        if (!getline(file, users[i].StudentID)) break;
        string isAdminStr;
        if (!getline(file, isAdminStr)) break;
        users[i].isAdmin = (isAdminStr == "1");
        UserCount++;
    }
    file.close();
    bool adminFound = false;
    for (int i = 0; i < UserCount; i++) {
        if (users[i].Username == "admin") {
            adminFound = true;
        }
    }
    if (!adminFound && UserCount < MaxStudents + 1) {
        users[UserCount].Username = "admin";
        users[UserCount].Password = "Admin@123";
        users[UserCount].StudentID = "";
        users[UserCount].isAdmin = true;
        UserCount++;
        saveUsers();
    }
    if (UserCount > 0)
        cout << "Loaded " << UserCount << " user(s) from authenticator.txt\n";
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

bool NegativeNumberValidation(string Number) {
    if (!Number.empty() && Number[0] == '-') {
        return false;
    }
    return true;
}

bool validatePassword(string Password) {
    bool hasUppercase = false;
    bool hasDigit = false;

    if (Password.size() <= 8) {
        return false;
    }
    for (int i = 0; i < (int)Password.size(); i++) {
        if (Password[i] >= 'A' && Password[i] <= 'Z') {
            hasUppercase = true;
        }
        if (Password[i] >= '0' && Password[i] <= '9') {
            hasDigit = true;
        }
    }
    return hasUppercase && hasDigit;
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

bool validateID(string ID) {
    if (ID.size() != 7) {
        return false;
    }
    if (!(ID[0] >= '0' && ID[0] <= '9') || !(ID[1] >= '0' && ID[1] <= '9')) {
        return false;
    }
    if (ID[2] != 'P') {
        return false;
    }
    for (int i = 3; i < (int)ID.size(); i++) {
        if (!(ID[i] >= '0' && ID[i] <= '9')) {
            return false;
        }
    }
    return true;
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
    int birthYear = (DOB[6] - '0') * 1000 + (DOB[7] - '0') * 100 + (DOB[8] - '0') * 10 + (DOB[9] - '0');

    if (month < 1 || month >12) {
        return false;
    }
    if (day < 1 || day>31) {
        return false;
    }

    int currentYear = 2026;
    int currentMonth = 5;
    int currentDay = 9;
    int age = currentYear - birthYear;
    if (month > currentMonth || (month == currentMonth && day > currentDay)) {
        age--;
    }
    if (age < 17) {
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
        if (!NegativeNumberValidation(s.NationalID)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
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
        if (!NegativeNumberValidation(s.PhoneNumber)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
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
        if (!NegativeNumberValidation(input)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (input.empty()) {
            cout << "Level must be 1, 2, 3, or 4 " << endl;
            continue;
        }
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

        if (!NegativeNumberValidation(choiceInput)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (choiceInput.empty() || choiceInput == "4") return;

        switch (choiceInput[0]) {
        case '1':
            cout << "\nEnter ID: "; // Specific prompt
            getline(cin, SearchCriteria); // Only one input call
            if (!validateID(SearchCriteria)) {
                cout << "Invalid Student ID! Please enter a valid ID like 26P0001\n";
                break;
            }
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

            if (!NegativeNumberValidation(SearchCriteria)) {
                cout << "You can't enter a negative number" << endl;
                break;
            }
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
    for (int i = 0; i < StudentCount - 1; i++) {
        for (int j = 0; j < StudentCount - i - 1; j++) {
            if (students[j].GPA < students[j + 1].GPA) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    displayStudentTable(students, StudentCount);
}

int findByID(string ID) {
    for (int i = 0; i < StudentCount; i++) {
        if (students[i].ID == ID) {
            return i;
        }
    }
    return -1;
}

int findUserByUsername(string Username) {
    for (int i = 0; i < UserCount; i++) {
        if (users[i].Username == Username) {
            return i;
        }
    }
    return -1;
}

bool validateCourseCode(string& CourseCode) {
    if (CourseCode.size() != 6) {
        return false;
    }
    for (int i = 0; i < 3; i++) {
        if (!((CourseCode[i] >= 'A' && CourseCode[i] <= 'Z') || (CourseCode[i] >= 'a' && CourseCode[i] <= 'z'))) {
            return false;
        }
        if (CourseCode[i] >= 'a' && CourseCode[i] <= 'z') {
            CourseCode[i] = CourseCode[i] - 32;
        }
    }
    for (int i = 3; i < 6; i++) {
        if (!(CourseCode[i] >= '0' && CourseCode[i] <= '9')) {
            return false;
        }
    }
    return true;
}

bool validateCourseCredits(int credits) {
    return credits >= 2 && credits <= 4;
}

int findByCourseCode(string CourseCode) {
    for (int i = 0; i < CourseCount; i++) {
        if (courses[i].Code == CourseCode) {
            return i;
        }
    }
    return -1;
}

bool uniqueCourseCode(string Code) {
    for (int i = 0; i < CourseCount; i++)
        if (courses[i].Code == Code)
            return false;
    return true;
}

int findGrade(string StudentID, string CourseCode) {
    for (int i = 0; i < GradeCount; i++) {
        if (grades[i].StudentID == StudentID && grades[i].CourseCode == CourseCode) {
            return i;
        }
    }
    return -1;
}

int countStudentCourses(string StudentID) {
    int count = 0;
    for (int i = 0; i < GradeCount; i++) {
        if (grades[i].StudentID == StudentID) {
            count++;
        }
    }
    return count;
}

int getMaxCourseLoad(double GPA) {
    if (GPA > 0.0 && GPA < 2.0) {
        return 5;
    }
    return 8;
}

int inputNumberInRange(int start, int end) {
    string input;
    int value;
    while (true) {
        cout << "Enter your choice: ";
        getline(cin, input);
        if (!NegativeNumberValidation(input)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (input.empty()) {
            cout << "Invalid choice, please enter a number" << endl;
            continue;
        }
        bool digitsOnly = true;
        for (int i = 0; i < (int)input.size(); i++) {
            if (!(input[i] >= '0' && input[i] <= '9')) {
                digitsOnly = false;
                break;
            }
        }
        if (!digitsOnly) {
            cout << "Invalid choice, please enter a number" << endl;
            continue;
        }
        value = stoi(input);
        if (value < start || value > end) {
            cout << "Invalid choice" << endl;
            continue;
        }
        return value;
    }
}

void addCourse() {
    cout << "\n=== Add Course ===" << endl;
    if (CourseCount >= MaxCourses) {
        cout << "The maximum number of courses has been reached ";
        return;
    }

    Course c;

    while (true) {
        cout << "Enter Course Code: ";
        getline(cin, c.Code);
        if (!validateCourseCode(c.Code)) {
            cout << "Course Code must be in form of LLLXXX, like CSE141" << endl;
            continue;
        }
        if (!uniqueCourseCode(c.Code)) {
            cout << "This Course Code already exists" << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter Course Name: ";
        getline(cin, c.Name);
        if (!c.Name.empty()) {
            break;
        }
        cout << "Course Name cannot be empty" << endl;
    }

    cout << "Enter Credits (2-4)" << endl;
    c.Credits = inputNumberInRange(2, 4);

    courses[CourseCount] = c;
    CourseCount++;

    saveCourses();

    cout << "\nCourse added successfully!\n";
    cout << "Course Code: " << c.Code << endl;
    cout << "Course Name: " << c.Name << endl;
}

void viewCourses() {
    if (CourseCount == 0) {
        cout << "No courses available" << endl;
        return;
    }

    cout << "\nTotal Courses: " << CourseCount << endl;
    cout << (char)201;
    for (int i = 0; i < 50; i++) cout << (char)205;
    cout << (char)187 << endl;

    cout << (char)186 << " " << left << setw(10) << "Code"
        << " " << (char)186 << " " << setw(25) << "Name"
        << " " << (char)186 << " " << setw(8) << "Credits" << (char)186 << endl;

    cout << (char)204;
    for (int i = 0; i < 50; i++) cout << (char)205;
    cout << (char)185 << endl;

    for (int i = 0; i < CourseCount; i++) {
        string courseCode = courses[i].Code;
        string courseName = courses[i].Name;
        string courseCredits = to_string(courses[i].Credits);
        if (courseCode.size() > 10) courseCode = courseCode.substr(0, 10);
        if (courseName.size() > 25) courseName = courseName.substr(0, 25);
        if (courseCredits.size() > 8) courseCredits = courseCredits.substr(0, 8);
        cout << (char)186 << " " << left << setw(10) << courseCode
            << " " << (char)186 << " " << setw(25) << courseName
            << " " << (char)186 << " " << setw(8) << courseCredits << (char)186 << endl;
    }

    cout << (char)200;
    for (int i = 0; i < 50; i++) cout << (char)205;
    cout << (char)188 << endl;
}

void updateCourse() {
    if (CourseCount == 0) {
        cout << "\nNo courses available" << endl;
        return;
    }

    string Code, input;
    int indexcrs = -1;
    int choice;

    cout << "\n=== Update Course ===" << endl;
    while (true) {
        cout << "Enter Course Code: ";
        getline(cin, Code);

        if (!validateCourseCode(Code)) {
            cout << "Course Code must be in form of LLLXXX, like CSE141" << endl;
            continue;
        }

        indexcrs = findByCourseCode(Code);
        if (indexcrs == -1) {
            cout << "Course Not Found" << endl;
            return;
        }

        break;
    }

    while (true) {
        cout << "\n1. Course Name\n2. Credits\n0. Back" << endl;
        cout << "Enter field you want to update: ";
        getline(cin, input);

        if (!NegativeNumberValidation(input)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (input.size() != 1 || input[0] < '0' || input[0] > '2') {
            cout << "Please choose a number from 0 to 2" << endl;
            continue;
        }

        choice = input[0] - '0';
        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1:
            while (true) {
                cout << "Enter Course Name: ";
                getline(cin, courses[indexcrs].Name);
                if (!courses[indexcrs].Name.empty()) {
                    cout << "Course name updated successfully" << endl;
                    break;
                }
                cout << "Course Name cannot be empty" << endl;
            }
            break;

        case 2:
            cout << "Enter Credits (2-4)" << endl;
            courses[indexcrs].Credits = inputNumberInRange(2, 4);
            cout << "Credits updated successfully" << endl;
            break;
        }

        saveCourses();
    }
}

void deleteCourse() {
    if (CourseCount == 0) {
        cout << "\nNo courses available" << endl;
        return;
    }

    string Code, input;
    int indexcrs;

    cout << "\n=== Delete Course ===" << endl;
    while (true) {
        cout << "Enter Course Code: ";
        getline(cin, Code);

        if (!validateCourseCode(Code)) {
            cout << "Course Code must be in form of LLLXXX, like CSE141" << endl;
            continue;
        }

        indexcrs = findByCourseCode(Code);
        if (indexcrs == -1) {
            cout << "Course Not Found" << endl;
            return;
        }
        break;
    }

    for (int i = 0; i < GradeCount; i++) {
        if (grades[i].CourseCode == Code) {
            cout << "Cannot delete: this course has grades recorded" << endl;
            return;
        }
    }

    cout << "Confirm deleting course: " << courses[indexcrs].Name << endl;
    cout << "1. Yes\n2. No" << endl;
    cout << "Enter your choice: ";
    getline(cin, input);

    if (!NegativeNumberValidation(input)) {
        cout << "You can't enter a negative number" << endl;
        return;
    }
    if (input == "1") {
        for (int i = indexcrs; i < CourseCount - 1; i++) {
            courses[i] = courses[i + 1];
        }
        CourseCount--;
        saveCourses();
        cout << "Successfully deleted" << endl;
    }
}

double getPoints(double total) {
    if (total > 93) return 4.0;
    if (total > 89) return 3.7;
    if (total > 84) return 3.3;
    if (total > 80) return 3.0;
    if (total > 76) return 2.7;
    if (total > 73) return 2.3;
    if (total > 70) return 2.0;
    if (total > 67) return 1.7;
    if (total > 64) return 1.3;
    if (total > 60) return 1.0;
    return 0.0;
}

void enterGrades() {
    if (StudentCount == 0) {
        cout << "\nNo students registered yet." << endl;
        return;
    }
    if (CourseCount == 0) {
        cout << "\nNo courses available yet." << endl;
        return;
    }
    if (GradeCount >= MaxGrades) {
        cout << "The maximum number of grades has been reached" << endl;
        return;
    }

    string studentID, courseCode;
    int indexstd, indexcrs, indexgrd;
    int midterm, finalExam;

    cout << "\n=== Enter Grades ===" << endl;
    while (true) {
        cout << "Enter Student ID: ";
        getline(cin, studentID);
        if (!validateID(studentID)) {
            cout << "Invalid Student ID! Please enter a valid ID like 26P0001" << endl;
            continue;
        }
        indexstd = findByID(studentID);
        if (indexstd == -1) {
            cout << "Student Not Found" << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter Course Code: ";
        getline(cin, courseCode);
        if (!validateCourseCode(courseCode)) {
            cout << "Course Code must be in form of LLLXXX, like CSE141" << endl;
            continue;
        }
        indexcrs = findByCourseCode(courseCode);
        if (indexcrs == -1) {
            cout << "Course Not Found" << endl;
            continue;
        }
        break;
    }

    indexgrd = findGrade(studentID, courseCode);
    if (indexgrd == -1 && countStudentCourses(studentID) >= getMaxCourseLoad(students[indexstd].GPA)) {
        cout << "Student cannot enroll in more than " << getMaxCourseLoad(students[indexstd].GPA) << " courses" << endl;
        return;
    }

    cout << "Enter Midterm Exam Grade (0-40)" << endl;
    midterm = inputNumberInRange(0, 40);
    cout << "Enter Final Exam Grade (0-60)" << endl;
    finalExam = inputNumberInRange(0, 60);

    if (indexgrd == -1) {
        grades[GradeCount].StudentID = studentID;
        grades[GradeCount].CourseCode = courseCode;
        grades[GradeCount].Midterm = midterm;
        grades[GradeCount].Final = finalExam;
        grades[GradeCount].Total = midterm + finalExam;
        GradeCount++;
    }
    else {
        grades[indexgrd].Midterm = midterm;
        grades[indexgrd].Final = finalExam;
        grades[indexgrd].Total = midterm + finalExam;
    }

    saveGrades();
    cout << "Grades successfully added" << endl;
}

void updateGrade() {
    if (GradeCount == 0) {
        cout << "\nNo available grades" << endl;
        return;
    }

    string studentID, courseCode;
    int indexstd, indexcrs, indexgrd;

    cout << "\n=== Update Grade ===" << endl;
    cout << "Enter Student ID: ";
    getline(cin, studentID);
    if (!validateID(studentID)) {
        cout << "Invalid Student ID! Please enter a valid ID like 26P0001" << endl;
        return;
    }
    indexstd = findByID(studentID);
    if (indexstd == -1) {
        cout << "Student Not Found" << endl;
        return;
    }

    cout << "Enter Course Code: ";
    getline(cin, courseCode);
    if (!validateCourseCode(courseCode)) {
        cout << "Course Code must be in form of LLLXXX, like CSE141" << endl;
        return;
    }
    indexcrs = findByCourseCode(courseCode);
    if (indexcrs == -1) {
        cout << "Course Not Found" << endl;
        return;
    }

    indexgrd = findGrade(studentID, courseCode);
    if (indexgrd == -1) {
        cout << "This student is not enrolled in this course" << endl;
        return;
    }

    cout << "Enter Midterm Exam Grade (0-40)" << endl;
    grades[indexgrd].Midterm = inputNumberInRange(0, 40);
    cout << "Enter Final Exam Grade (0-60)" << endl;
    grades[indexgrd].Final = inputNumberInRange(0, 60);
    grades[indexgrd].Total = grades[indexgrd].Midterm + grades[indexgrd].Final;

    saveGrades();
    cout << "Grade updated successfully" << endl;
}

void viewGrades() {
    if (GradeCount == 0) {
        cout << "\nNo available grades" << endl;
        return;
    }

    cout << "\n=== View Grades ===" << endl;
    for (int i = 0; i < GradeCount; i++) {
        int studentIndex = findByID(grades[i].StudentID);
        int courseIndex = findByCourseCode(grades[i].CourseCode);

        cout << "Student: " << (studentIndex == -1 ? grades[i].StudentID : students[studentIndex].Name) << endl;
        cout << "Course: " << (courseIndex == -1 ? grades[i].CourseCode : courses[courseIndex].Name) << endl;
        cout << "Midterm Exam Grade: " << grades[i].Midterm << " | Final Exam Grade: " << grades[i].Final << endl;
        cout << "Total Grade: " << grades[i].Total << endl << endl;
    }
}

void calculateGPA() {
    string studentID;
    int indexstd;
    double totalHours = 0.0;
    double gpa = 0.0;

    cout << "\n=== Calculate GPA ===" << endl;
    while (true) {
        cout << "Enter Student ID: ";
        getline(cin, studentID);
        if (!validateID(studentID)) {
            cout << "Invalid Student ID! Please enter a valid ID like 26P0001" << endl;
            continue;
        }
        indexstd = findByID(studentID);
        if (indexstd == -1) {
            cout << "Student Not Found" << endl;
            continue;
        }
        break;
    }

    for (int i = 0; i < GradeCount; i++) {
        if (grades[i].StudentID == studentID) {
            int courseIndex = findByCourseCode(grades[i].CourseCode);
            if (courseIndex != -1) {
                totalHours += courses[courseIndex].Credits;
                gpa += getPoints(grades[i].Total) * courses[courseIndex].Credits;
            }
        }
    }

    if (totalHours == 0) {
        cout << "No graded courses found for this student" << endl;
        return;
    }

    gpa = gpa / totalHours;
    students[indexstd].GPA = gpa;
    saveStudents();

    cout << "Student: " << students[indexstd].Name << endl;
    cout << "GPA: " << fixed << setprecision(2) << gpa << endl;
}

void generateTranscript() {
    string studentID;
    int indexstd;
    int courseCount = 0;
    double totalHours = 0.0;
    double gpa = 0.0;
     

    cout << "\n=== Generate Transcript ===" << endl;
    if (!loggedInStudentID.empty()) {
        studentID = loggedInStudentID;
        indexstd = findByID(studentID);
        if (indexstd == -1) {
            cout << "Student Not Found" << endl;
            return;
        }
    }
    else {
        while (true) {
            cout << "Enter Student ID: ";
            getline(cin, studentID);
            if (!validateID(studentID)) {
                cout << "Invalid Student ID! Please enter a valid ID like 26P0001" << endl;
                continue;
            }
            indexstd = findByID(studentID);
            if (indexstd == -1) {
                cout << "Student Not Found" << endl;
                continue;
            }
            break;
        }
    }
    for (int i = 0; i < GradeCount; i++) {
        if (grades[i].StudentID == studentID) {
            int courseIndex = findByCourseCode(grades[i].CourseCode);
            if (courseIndex != -1) {
                totalHours += courses[courseIndex].Credits;
                gpa += getPoints(grades[i].Total) * courses[courseIndex].Credits;
            }
        }
    }

    if (totalHours == 0) {
        cout << "No graded courses found for this student" << endl;
        return;
    }

    gpa = gpa / totalHours;
    students[indexstd].GPA = gpa;
    saveStudents(); // aashan maygesh GPA zero, ruins the load status w max courses
    for (int i = 0; i < GradeCount; i++) {
        if (grades[i].StudentID == studentID) {
            courseCount++;
        }
    }

    cout << "\nTranscript for " << students[indexstd].Name << " (" << students[indexstd].ID << ")" << endl;
    if (students[indexstd].GPA != 0.0 && students[indexstd].GPA < 2.0) {
        cout << "Load Status: Half load" << endl;
    }
    else {
        cout << "Load Status: Full load" << endl;
    }
    cout << "Courses Enrolled: " << courseCount << "/" << getMaxCourseLoad(students[indexstd].GPA) << endl;

    const int transcriptTableWidth = 94;
    cout << (char)201;
    for (int i = 0; i < transcriptTableWidth; i++) cout << (char)205;
    cout << (char)187 << endl;

    cout << (char)186 << " " << left << setw(10) << "Code"
        << " " << (char)186 << " " << setw(25) << "Course"
        << " " << (char)186 << " " << setw(8) << "Midterm"
        << " " << (char)186 << " " << setw(8) << "Final"
        << " " << (char)186 << " " << setw(8) << "Total"
        << " " << (char)186 << " " << setw(8) << "Points"
        << " " << (char)186 << " " << setw(7) << "Credits" << " " << (char)186 << endl;

    cout << (char)204;
    for (int i = 0; i < transcriptTableWidth; i++) cout << (char)205;
    cout << (char)185 << endl;

    if (courseCount == 0) {
        cout << (char)186 << " " << left << setw(transcriptTableWidth - 1) << "No grades recorded for this student" << (char)186 << endl;
    }
    else {
        for (int i = 0; i < GradeCount; i++) {
            if (grades[i].StudentID == studentID) {
                int courseIndex = findByCourseCode(grades[i].CourseCode);
                string courseName = courseIndex == -1 ? "Unknown Course" : courses[courseIndex].Name;
                int credits = courseIndex == -1 ? 0 : courses[courseIndex].Credits;
                if (courseName.size() > 25) courseName = courseName.substr(0, 25);

                cout << (char)186 << " " << left << setw(10) << grades[i].CourseCode
                    << " " << (char)186 << " " << setw(25) << courseName
                    << " " << (char)186 << " " << setw(8) << fixed << setprecision(1) << grades[i].Midterm
                    << " " << (char)186 << " " << setw(8) << grades[i].Final
                    << " " << (char)186 << " " << setw(8) << grades[i].Total
                    << " " << (char)186 << " " << setw(8) << setprecision(2) << getPoints(grades[i].Total)
                    << " " << (char)186 << " " << setw(7) << credits << " " << (char)186 << endl;
            }
        }
    }

    cout << (char)200;
    for (int i = 0; i < transcriptTableWidth; i++) cout << (char)205;
    cout << (char)188 << endl;
    cout << "GPA: " << fixed << setprecision(2) << students[indexstd].GPA << endl;
}

void updateStudent() {
    if (StudentCount == 0) {
        cout << "\nNo students registered yet." << endl;
        return;
    }

    string id, input;
    int index = -1;
    int choice;

    cout << "\n=== Update Student ===" << endl;
    if (!loggedInStudentID.empty()) { // check first law fy student logged in, if so dont prompt to input ID
        id = loggedInStudentID;
        index = findByID(id);
        if (index == -1) {
            cout << "Student Not Found" << endl;
            return;
        }
        printformat(students[index]);
    }
    else { // if admin logged in, no global student logged in ID, prompt to manual entry
        while (true) {
            cout << "Enter Student ID: ";
            getline(cin, id);

            if (!validateID(id)) {
                cout << "Invalid Student ID! Please enter a valid ID like 26P0001" << endl;
                continue;
            }

            index = findByID(id);
            if (index == -1) {
                cout << "ID not found" << endl;
                return;
            }

            printformat(students[index]);
            break;
        }
    }

    while (true) {
        cout << "\n1. Name\n2. Phone Number\n3. Birth Date\n4. Gender\n5. Level\n6. Program\n0. Back" << endl;
        cout << "Enter field you want to update: ";
        getline(cin, input);

        if (!NegativeNumberValidation(input)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (input.size() != 1 || input[0] < '0' || input[0] > '6') {
            cout << "Please choose a number from 0 to 6" << endl;
            continue;
        }

        choice = input[0] - '0';
        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1:
            while (true) {
                cout << "Enter Student Name: ";
                getline(cin, students[index].Name);
                if (NameValidation(students[index].Name)) {
                    cout << "Name updated successfully" << endl;
                    break;
                }
                cout << "Name must be exactly 2 words (first and last name)" << endl;
            }
            break;

        case 2:
            while (true) {
                cout << "Enter Phone Number: ";
                getline(cin, students[index].PhoneNumber);
                if (!NegativeNumberValidation(students[index].PhoneNumber)) {
                    cout << "You can't enter a negative number" << endl;
                    continue;
                }
                if (PhoneNOValidation(students[index].PhoneNumber)) {
                    cout << "Phone number updated successfully" << endl;
                    break;
                }
                cout << "The phone number must be 11 digits starting with 01" << endl;
            }
            break;

        case 3:
            while (true) {
                cout << "Enter Date of Birth (DD/MM/YYYY): ";
                getline(cin, students[index].DOB);
                if (DOBValidation(students[index].DOB)) {
                    cout << "Birth date updated successfully" << endl;
                    break;
                }
                cout << "Invalid date or Age (the student must be 17 or older)" << endl;
            }
            break;

        case 4:
            while (true) {
                cout << "Enter the Gender (M/F): ";
                getline(cin, input);
                if (input.size() == 1 && GenderValidation(input[0])) {
                    students[index].Gender = input[0];
                    cout << "Gender updated successfully" << endl;
                    break;
                }
                cout << "Gender must be M or F" << endl;
            }
            break;

        case 5:
            while (true) {
                cout << "Enter your Academic Level (1-4): ";
                getline(cin, input);
                if (!NegativeNumberValidation(input)) {
                    cout << "You can't enter a negative number" << endl;
                    continue;
                }
                if (input.size() == 1 && input[0] >= '1' && input[0] <= '4') {
                    students[index].Level = input[0] - '0';
                    cout << "Level updated successfully" << endl;
                    break;
                }
                cout << "Level must be 1, 2, 3, or 4" << endl;
            }
            break;

        case 6:
            while (true) {
                cout << "Enter Your Program (CSE/CCE/MCT): ";
                getline(cin, students[index].Program);
                if (ProgramValidation(students[index].Program)) {
                    cout << "Program updated successfully" << endl;
                    break;
                }
                cout << "Program must be CSE, CCE, or MCT" << endl;
            }
            break;
        }

        saveStudents();
    }
}

void deleteStudent() {
    if (StudentCount == 0) {
        cout << "\nNo students registered yet." << endl;
        return;
    }

    string id, input;
    int index;

    cout << "\n=== Delete Student ===" << endl;
    while (true) {
        cout << "Enter Student ID: ";
        getline(cin, id);

        if (!validateID(id)) {
            cout << "Invalid Student ID! Please enter a valid ID like 26P0001" << endl;
            continue;
        }

        index = findByID(id);
        if (index == -1) {
            cout << "ID not found" << endl;
            return;
        }
        break;
    }

    cout << "Confirm deleting student: " << students[index].Name << endl;
    cout << "1. Yes\n2. No" << endl;
    cout << "Enter your choice: ";
    getline(cin, input);

    if (!NegativeNumberValidation(input)) {
        cout << "You can't enter a negative number" << endl;
        return;
    }
    if (input == "1") {
        for (int i = index; i < StudentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        StudentCount--;
        saveStudents();
        cout << "Successfully deleted" << endl;
    }
}


void listAllStudents() {
    int choice;
    string choiceinput;
    cout << "\n=== List all students ===" << endl;
    cout << "Sort by:\n1. Student ID\n2. Name (A - Z)\n3. GPA (Highest First)\n4. Back" << endl;
    cout << "\nEnter your choice: ";
    getline(cin, choiceinput);
    if (!NegativeNumberValidation(choiceinput)) {
        cout << "You can't enter a negative number" << endl;
        return;
    }
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
        if (!NegativeNumberValidation(choiceInput)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (choiceInput.empty()) {
            cout << "Please choose a number from 1 to 6";
            continue;
        }
        choice = choiceInput[0] - '0';
        switch (choice) {
        case 1:
            AddStudent();
            break;
        case 2:
            searchStudent(); break;
        case 3:
            updateStudent(); break;
        case 4:
            deleteStudent(); break;
        case 5:
            listAllStudents(); break;
        case 6: return;

        default:
            cout << "Please choose a number from 1 to 6";
            break;
        }
    }

}

void courseManagement() {
    int choice;
    string choiceInput;
    while (true) {
        cout << "\n=== Course Management ===";
        cout << "\n1. Add Course\n2. View Courses\n3. Update Course\n4. Delete Course\n5. Back to Main Menu\n\n";
        cout << "Enter your choice: ";
        getline(cin, choiceInput);
        if (!NegativeNumberValidation(choiceInput)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (choiceInput.empty()) {
            cout << "Please choose a number from 1 to 5";
            continue;
        }
        choice = choiceInput[0] - '0';
        switch (choice) {
        case 1:
            addCourse();
            break;
        case 2:
            viewCourses();
            break;
        case 3:
            updateCourse();
            break;
        case 4:
            deleteCourse();
            break;
        case 5:
            return;
        default:
            cout << "Please choose a number from 1 to 5";
            break;
        }
    }
}

void gradesManagement() {
    int choice;
    string choiceInput;
    while (true) {
        cout << "\n=== Grades Management ===";
        cout << "\n1. Enter Grades\n2. Update Grade\n3. View Grades\n4. Calculate GPA\n5. Generate Transcript\n6. Back to Main Menu\n\n";
        cout << "Enter your choice: ";
        getline(cin, choiceInput);
        if (!NegativeNumberValidation(choiceInput)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (choiceInput.empty()) {
            cout << "Please choose a number from 1 to 6";
            continue;
        }

        choice = choiceInput[0] - '0';
        switch (choice) {
        case 1:
            enterGrades();
            break;
        case 2:
            updateGrade();
            break;
        case 3:
            viewGrades();
            break;
        case 4:
            calculateGPA();
            break;
        case 5:
            generateTranscript();
            break;
        case 6:
            return;
        default:
            cout << "Please choose a number from 1 to 6";
            break;
        }
    }
}

void enrollCourse(string studentID) {
    string courseCode;
    int indexstd, indexcrs, indexgrd;
    int maxCourseLoad, currentCourseCount;

    cout << "\n=== Enroll in Course ===" << endl;
    if (CourseCount == 0) {
        cout << "No courses available" << endl;
        return;
    }
    if (GradeCount >= MaxGrades) {
        cout << "The maximum number of grades has been reached" << endl;
        return;
    }
    indexstd = findByID(studentID);
    if (indexstd == -1) {
        cout << "Student Not Found" << endl;
        return;
    }

    maxCourseLoad = getMaxCourseLoad(students[indexstd].GPA);
    currentCourseCount = countStudentCourses(studentID);
    if (currentCourseCount >= maxCourseLoad) {
        cout << "You have reached your maximum course load of " << maxCourseLoad << " courses" << endl;
        return;
    }

    viewCourses();
    while (true) {
        cout << "Enter Course Code: ";
        getline(cin, courseCode);
        if (!validateCourseCode(courseCode)) {
            cout << "Course Code must be in form of LLLXXX, like CSE141" << endl;
            continue;
        }
        indexcrs = findByCourseCode(courseCode);
        if (indexcrs == -1) {
            cout << "Course Not Found" << endl;
            continue;
        }
        break;
    }

    indexgrd = findGrade(studentID, courseCode);
    if (indexgrd != -1) {
        cout << "You are already enrolled in this course" << endl;
        return;
    }

    grades[GradeCount].StudentID = studentID;
    grades[GradeCount].CourseCode = courseCode;
    grades[GradeCount].Midterm = 0;
    grades[GradeCount].Final = 0;
    grades[GradeCount].Total = 0;
    GradeCount++;
    saveGrades();
    cout << "Successfully enrolled in " << courses[indexcrs].Name << endl;
}

void studentMenu(string studentID) {
    int choice;
    string choiceInput;
    int indexstd;

    indexstd = findByID(studentID);
    if (indexstd == -1) {
        cout << "Student Not Found" << endl;
        return;
    }

    loggedInStudentID = studentID;
    cout << "\n=== Welcome, " << students[indexstd].Name << " ===" << endl;
    while (true) {
        cout << "\n1. View My Transcript\n2. Enroll in a Course\n3. View All Courses\n4. Update My Info\n5. Logout\n\n";
        cout << "Enter your choice: ";
        getline(cin, choiceInput);
        if (!NegativeNumberValidation(choiceInput)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (choiceInput.empty()) {
            cout << "Please choose a number from 1 to 5";
            continue;
        }
        choice = choiceInput[0] - '0';
        switch (choice) {
        case 1:
            generateTranscript();
            break;
        case 2:
            enrollCourse(studentID);
            break;
        case 3:
            viewCourses();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            loggedInStudentID = ""; // reset current logged in student on logout
            return;
        default:
            cout << "Please choose a number from 1 to 5";
            break;
        }
    }
}

void adminMenu() {
    int choice;
    string choiceInput;
    while (true) {
        cout << "\n=== Admin Menu ===";
        cout << "\n1. Student Management\n2. Course Management\n3. Grades Management\n4. Logout\n\n";
        cout << "Enter your choice: ";
        getline(cin, choiceInput);
        if (!NegativeNumberValidation(choiceInput)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (choiceInput.empty()) {
            cout << "Please choose a number from 1 to 4";
            continue;
        }
        choice = choiceInput[0] - '0';
        switch (choice) {
        case 1:
            studentManagement();
            break;
        case 2:
            courseManagement();
            break;
        case 3:
            gradesManagement();
            break;
        case 4:
            return;
        default:
            cout << "Please choose a number from 1 to 4";
            break;
        }
    }
}

void loginScreen() {
    int choice;
    string choiceInput;
    string username, password;
    int index;

    while (true) {
        cout << "\n1. Login\n2. Register as Student\n3. Exit\n\n";
        cout << "Enter your choice: ";
        getline(cin, choiceInput);
        if (!NegativeNumberValidation(choiceInput)) {
            cout << "You can't enter a negative number" << endl;
            continue;
        }
        if (choiceInput.empty()) {
            cout << "Please choose a number from 1 to 3";
            continue;
        }
        choice = choiceInput[0] - '0';
        switch (choice) {
        case 1:
            cout << "Enter Username: ";
            getline(cin, username);
            cout << "Enter Password: ";
            getline(cin, password);
            index = findUserByUsername(username); // boolean search if user exists
            if (index == -1) {
                cout << "Username not found" << endl;
                continue;
            }
            if (users[index].Password != password) {
                cout << "Incorrect password" << endl;
                continue;
            }
            if (users[index].isAdmin) {
                cout << "Welcome, Admin!" << endl;
                adminMenu();
            }
            else {
                cout << "Welcome, " << users[index].Username << "!" << endl;
                studentMenu(users[index].StudentID); // sends to student menu, saves ID globally to be used instead of manual entry
            }
            break;
        case 2:
            cout << "\n=== Student Registration ===" << endl;
            if (UserCount >= MaxStudents + 1) {
                cout << "The maximum number of users has been reached" << endl;
                break;
            }
            AddStudent();
            username = students[StudentCount - 1].ID + "@eng.asu.edu.eg";
            cout << "Your username is: " << username << endl;
            while (true) {
                cout << "Set your password: ";
                getline(cin, password);
                if (validatePassword(password)) {
                    break;
                }
                cout << "Password must be more than 8 characters, contain at least one uppercase letter and one number" << endl;
            }
            users[UserCount].Username = username;
            users[UserCount].Password = password;
            users[UserCount].StudentID = students[StudentCount - 1].ID;
            users[UserCount].isAdmin = false;
            UserCount++;
            saveUsers();
            cout << "Registration successful! Please login to continue." << endl;
            break;
        case 3:
            cout << "Goodbye!" << endl;
            return;
        default:
            cout << "Please choose a number from 1 to 3";
            break;
        }
    }
}


int main() {

    loadStudents(); // <-- auto-load saved students on startup
    loadGrades();
    loadCourses();
    loadUsers();

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


    loginScreen();
    return 0;
}

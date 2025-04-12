#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Phone {
    int id;
    string model;
    double price;
};

struct Teacher {
    int id;
    string name;
    vector<string> subjects;
    vector<int> phoneIds;
};

vector<Teacher> teachers;
vector<Phone> phones;
vector<pair<int, int>> foreignKeys;
void loadDataFromFile(const string& teacherFile, const string& phoneFile, const string& foreignKeysFile) {
    ifstream teacherStream(teacherFile);
    ifstream phoneStream(phoneFile);
    ifstream foreignKeysStream(foreignKeysFile);

    string line;
    while (getline(phoneStream, line)) {
        stringstream ss(line);
        int id;
        string model;
        double price;
        ss >> id >> model >> price;
        phones.push_back({ id, model, price });
    }

    while (getline(teacherStream, line)) {
        stringstream ss(line);
        int id;
        string name;
        int subjectCount;
        ss >> id >> name >> subjectCount;

        Teacher teacher;
        teacher.id = id;
        teacher.name = name;

        for (int i = 0; i < subjectCount; ++i) {
            string subject;
            ss >> subject;
            teacher.subjects.push_back(subject);
        }

        teachers.push_back(teacher);
    }

    while (getline(foreignKeysStream, line)) {
        stringstream ss(line);
        int teacherId, phoneId;
        ss >> teacherId >> phoneId;

        for (auto& teacher : teachers) {
            if (teacher.id == teacherId) {
                teacher.phoneIds.push_back(phoneId);
                break;
            }
        }
    }

    cout << "Data loaded from files successfully!" << endl;
}

void loadForeignKeysFromFile(const string& foreignKeysFile) {
    ifstream foreignKeysStream(foreignKeysFile);
    string line;
    
    while (getline(foreignKeysStream, line)) {
        stringstream ss(line);
        int teacherId, phoneId;
        ss >> teacherId >> phoneId;
        cout << "Teacher ID: " << teacherId << " | Phone ID: " << phoneId << endl;

        foreignKeys.push_back(make_pair(teacherId, phoneId));

        for (auto& teacher : teachers) {
            if (teacher.id == teacherId) {
                teacher.phoneIds.push_back(phoneId);
                break;
            }
        }
    }
    cout << "Foreign keys loaded successfully!" << endl;
}

void linkTeacherToPhones(int teacherId, const vector<int>& phoneIds) {
    for (int phoneId : phoneIds) {
        foreignKeys.push_back(make_pair(teacherId, phoneId));
    }
    cout << "Teacher linked to phones successfully!" << endl;
}

void printAllPhones() {
    for (const auto& phone : phones) {
        cout << "Phone ID: " << phone.id << " | Model: " << phone.model 
             << " | Price: " << phone.price << "$" << endl;
    }
}

void printAllTeachers() {
    for (const auto& teacher : teachers) {
        cout << "Teacher ID: " << teacher.id << " | Name: " << teacher.name << endl;
    }
}

void editPhoneField(int phoneId, const string& field, const string& value) {
    for (auto& phone : phones) {
        if (phone.id == phoneId) {
            if (field == "model") phone.model = value;
            else if (field == "price") phone.price = stod(value);
            cout << "Phone field updated successfully!" << endl;
            return;
        }
    }
    cout << "Phone not found!" << endl;
}

void editTeacherField(int teacherId, const string& field, const string& value) {
    for (auto& teacher : teachers) {
        if (teacher.id == teacherId) {
            if (field == "name") teacher.name = value;
            else if (field == "subjects") {
                teacher.subjects.clear();
                stringstream ss(value);
                string subject;
                while (ss >> subject) {
                    teacher.subjects.push_back(subject);
                }
            }
            cout << "Teacher field updated successfully!" << endl;

            cout << "Link this teacher to phones? (y/n): ";
            char choice;
            cin >> choice;
            cin.ignore(INT32_MAX, '\n');
            if (choice == 'y') {
                printAllPhones();
                cout << "Enter phone IDs to link (space-separated): ";
                string phoneIdsInput;
                getline(cin, phoneIdsInput);
                stringstream ss(phoneIdsInput);
                vector<int> phoneIds;
                int phoneId;
                while (ss >> phoneId) {
                    phoneIds.push_back(phoneId);
                }
                linkTeacherToPhones(teacherId, phoneIds);
            }
            return;
        }
    }
    cout << "Teacher not found!" << endl;
}

void clearPhoneFields(int phoneId, const vector<string>& fields) {
    for (auto& phone : phones) {
        if (phone.id == phoneId) {
            for (const auto& field : fields) {
                if (field == "model") phone.model = "EMPTY";
                else if (field == "price") phone.price = 0;
            }
            cout << "Phone fields cleared successfully!" << endl;
            return;
        }
    }
    cout << "Phone not found!" << endl;
}

void clearTeacherFields(int teacherId, const vector<string>& fields) {
    for (auto& teacher : teachers) {
        if (teacher.id == teacherId) {
            for (const auto& field : fields) {
                if (field == "name") teacher.name = "EMPTY";
                else if (field == "subjects") teacher.subjects.clear();
            }
            cout << "Teacher fields cleared successfully!" << endl;
            return;
        }
    }
    cout << "Teacher not found!" << endl;
}

void searchTeacherByName(const string& name) {
    bool found = false;
    for (const auto& teacher : teachers) {
        if (teacher.name == name) {
            cout << "Found Teacher: ID: " << teacher.id << " | Name: " << teacher.name 
                 << " | Subjects: ";
            for (const auto& subject : teacher.subjects) {
                cout << subject << " ";
            }
            cout << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Teacher with the given name not found." << endl;
    }
}

void printInfo() {
    for (const auto& teacher : teachers) {
        cout << "Teacher ID: " << teacher.id << " | Name: " << teacher.name 
             << " | Subjects: ";
        for (const auto& subject : teacher.subjects) {
            cout << subject << " ";
        }
        cout << "| Phones: ";
        for (int phoneId : teacher.phoneIds) {
            for (const auto& phone : phones) {
                if (phone.id == phoneId) {
                    cout << phone.model << " (Price: " << phone.price << "$) ";
                    break;
                }
            }
        }
        cout << endl;
    }
}


void saveDataToFile(const string& teacherFile, const string& phoneFile, const string& foreignKeysFile) {
    ofstream teacherStream(teacherFile);
    ofstream phoneStream(phoneFile);
    ofstream foreignKeysStream(foreignKeysFile);

    if (!teacherStream.is_open() || !phoneStream.is_open() || !foreignKeysStream.is_open()) {
        cout << "Error opening files for writing!" << endl;
        return;
    }

    for (const auto& teacher : teachers) {
        teacherStream << teacher.id << " " << teacher.name << " " << teacher.subjects.size();
        for (const auto& subject : teacher.subjects) {
            teacherStream << " " << subject;
        }
        teacherStream << endl;
    }

    for (const auto& phone : phones) {
        phoneStream << phone.id << " " << phone.model << " " << phone.price << endl;
    }

    for (const auto& fk : foreignKeys) {
        foreignKeysStream << fk.first << " " << fk.second << endl;
    }

    cout << "Data saved successfully!" << endl;
}

void addTeacher(int id, const string& name, const vector<string>& subjects) {
    Teacher newTeacher;
    newTeacher.id = id;
    newTeacher.name = name;
    newTeacher.subjects = subjects;
    teachers.push_back(newTeacher);
    
    printAllPhones();
    cout << "Enter phone IDs to link (space-separated): ";
    string phoneIdsInput;
    getline(cin, phoneIdsInput);
    stringstream ss(phoneIdsInput);
    vector<int> phoneIds;
    int phoneId;
    while (ss >> phoneId) {
        phoneIds.push_back(phoneId);
    }
    linkTeacherToPhones(id, phoneIds);
    
    cout << "Teacher added successfully!" << endl;
}

void addPhone(int id, const string& model, double price) {
    Phone newPhone;
    newPhone.id = id;
    newPhone.model = model;
    newPhone.price = price;
    phones.push_back(newPhone);
    cout << "Phone added successfully!" << endl;
}

void manageTeacher() {
    cout << "Available Teachers:\n";
    printAllTeachers();
    cout << "Enter teacher ID to manage: ";
    int teacherId;
    cin >> teacherId;

    cout << "Choose operation:\n"
         << "1. Change Name\n"
         << "2. Edit Subjects\n"
         << "3. Add Phone\n"
         << "Choose option: ";
    int operation;
    cin >> operation;

    switch (operation) {
        case 1: {
            cout << "Enter new name: ";
            string newName;
            cin.ignore(INT32_MAX, '\n');
            getline(cin, newName);
            editTeacherField(teacherId, "name", newName);
            break;
        }
        case 2: {
            cout << "Enter new subjects (space-separated): ";
            string newSubjects;
            cin.ignore(INT32_MAX, '\n');
            getline(cin, newSubjects);
            editTeacherField(teacherId, "subjects", newSubjects);
            break;
        }
        case 3: {
            printAllPhones();
            cout << "Enter phone IDs to link (space-separated): ";
            string phoneIdsInput;
            cin.ignore(INT32_MAX, '\n');
            getline(cin, phoneIdsInput);
            stringstream ss(phoneIdsInput);
            vector<int> phoneIds;
            int phoneId;
            while (ss >> phoneId) {
                phoneIds.push_back(phoneId);
            }
            linkTeacherToPhones(teacherId, phoneIds);
            break;
        }
        default:
            cout << "Invalid operation!" << endl;
    }
}


int main() {
    int choice;

    loadDataFromFile("teachers.txt", "phones.txt", "foreigingkeys.txt");
    loadForeignKeysFromFile("foreigingkeys.txt");

    while (true) {
        cout << "\nUniversity System\n"
            << "1. Print Info\n"
            << "2. Search Teacher by Name\n"
            << "3. Edit Phone Field\n"
            << "4. Edit Teacher Field\n"
            << "5. Clear Phone Fields\n"
            << "6. Clear Teacher Fields\n"
            << "7. Add Teacher\n"
            << "8. Add Phone\n"
            << "9. Save Data\n"
            << "10. Manage Teacher\n"
            << "0. Exit\n"
            << "Choose option: ";
        cin >> choice;

        double price;
        string name;
        int id;
        string field, value;
        vector<string> fields;

        switch (choice) {
            case 1:
                printInfo();
                break;
            case 2: {
                cout << "Available Teachers:\n";
                printAllTeachers();
                cout << "Enter teacher name: ";
                cin.ignore(INT32_MAX, '\n');
                getline(cin, name);
                searchTeacherByName(name);
                break;
            }
            case 3: {
                printAllPhones();
                cout << "Enter phone ID: ";
                cin >> id;
                cout << "Enter field to edit (model/price): ";
                cin >> field;
                cout << "Enter new value: ";
                cin.ignore(INT32_MAX, '\n');
                getline(cin, value);
                editPhoneField(id, field, value);
                cout << "Modified Phones:\n";
                printAllPhones();
                break;
            }
            case 4: {
                manageTeacher();
                break;
            }
            case 5: {
                cout << "Available Phones:\n";
                printAllPhones();
                cout << "Enter phone ID: ";
                cin >> id;
                cout << "Enter fields to clear (space-separated): ";
                cin.ignore(INT32_MAX, '\n');
                getline(cin, value);
                stringstream ss(value);
                string field;
                while (ss >> field) {
                    fields.push_back(field);
                }
                clearPhoneFields(id, fields);
                cout << "Modified Phones:\n";
                printAllPhones();
                break;

            }
            case 6: {
                cout << "Available Teachers:\n";
                printAllTeachers();
                cout << "Enter teacher ID: ";
                cin >> id;
                cout << "Enter fields to clear (space-separated): ";
                cin.ignore(INT32_MAX, '\n');
                getline(cin, value);
                stringstream ss(value);
                string field;
                while (ss >> field) {
                    fields.push_back(field);
                }
                clearTeacherFields(id, fields);
                cout << "Modified Teachers:\n";
                printAllTeachers();
                break;
            }
            case 7: {
                int id;
                string name;
                cout << "Available Teachers:\n";
                printAllTeachers();
                cout << "Enter teacher ID: ";
                cin >> id;
                cout << "Enter teacher name: ";
                cin.ignore(INT32_MAX, '\n');
                getline(cin, name);
                cout << "Enter subjects (space-separated): ";
                string subjectsInput;
                getline(cin, subjectsInput);
                stringstream ss(subjectsInput);
                string subject;
                vector<string> subjects;
                while (ss >> subject) {
                    subjects.push_back(subject);
                }
                addTeacher(id, name, subjects);
                break;
            }
            case 8: {
                int id;
                string model;
                double price;
                cout << "Available Phones:\n";
                printAllPhones();
                cout << "Enter phone ID: ";
                cin >> id;
                cout << "Enter phone model: ";
                cin.ignore(INT32_MAX, '\n');
                getline(cin, model);
                cout << "Enter phone price: ";
                cin >> price;
                addPhone(id, model, price);
                cout << "Modified Phones:\n";
                printAllPhones();
                break;
            }
            case 9: {
                saveDataToFile("teachers.txt", "phones.txt", "foreigingkeys.txt");
                break;
            }
            case 10: {
                manageTeacher();
                break;
            }
            case 0:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
} 
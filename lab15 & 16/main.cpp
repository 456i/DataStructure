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

void loadDataFromFile(const string& teacherFile, const string& phoneFile, const string& foreigingkeysFile) {
    ifstream teacherStream(teacherFile);
    ifstream phoneStream(phoneFile);
    ifstream foreigingkeysStream(foreigingkeysFile);

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

    while (getline(foreigingkeysStream, line)) {
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

void findPhoneByPriceLinear(double price) {
    cout << "Searching phone with price: " << price << endl;
    for (auto& p : phones) {
        if (p.price == price) {
            cout << "Found: Model: " << p.model << " | Price: " << p.price << "$" << endl;
            return;
        }
    }
    cout << "Phone with the given price not found." << endl;
}

void findPhoneByPriceBinary(double price) {
    vector<Phone> sortedPhones = phones;
    sort(sortedPhones.begin(), sortedPhones.end(), [](const Phone& a, const Phone& b) {
        return a.price < b.price;
        });

    cout << "Searching phone with price: " << price << " (Binary Search)" << endl;

    int low = 0, high = sortedPhones.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (sortedPhones[mid].price == price) {
            cout << "Found: Model: " << sortedPhones[mid].model << " | Price: " << sortedPhones[mid].price << "$" << endl;
            return;
        }
        if (sortedPhones[mid].price < price) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    cout << "Phone with the given price not found." << endl;
}

void findPhoneByPriceInterpolation(double price) {
    vector<Phone> sortedPhones = phones;
    sort(sortedPhones.begin(), sortedPhones.end(), [](const Phone& a, const Phone& b) {
        return a.price < b.price;
        });

    cout << "Searching phone with price: " << price << " (Interpolation Search)" << endl;

    int low = 0, high = sortedPhones.size() - 1;
    while (low <= high && sortedPhones[low].price <= price && sortedPhones[high].price >= price) {
        int pos = low + ((price - sortedPhones[low].price) * (high - low)) / (sortedPhones[high].price - sortedPhones[low].price);

        if (pos < low || pos > high) {
            break;
        }

        if (sortedPhones[pos].price == price) {
            cout << "Found: Model: " << sortedPhones[pos].model << " | Price: " << sortedPhones[pos].price << "$" << endl;
            return;
        }

        if (sortedPhones[pos].price < price) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }

    cout << "Phone with the given price not found." << endl;
}


void printInfo() {
    for (const auto& teacher : teachers) {
        cout << "Teacher ID: " << teacher.id << " | Name: " << teacher.name << " | Subjects: ";
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

void printAllPhones() {
    for (const auto& phone : phones) {
        cout << "Phone ID: " << phone.id << " | Model: " << phone.model << " | Price: " << phone.price << "$" << endl;
    }
}

void findTeacherByName(const string& name) {
    bool found = false;
    for (const auto& teacher : teachers) {
        if (teacher.name == name) {
            cout << "Found Teacher: ID: " << teacher.id << " | Name: " << teacher.name << " | Subjects: ";
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

int main() {
    int choice;

    loadDataFromFile("teachers.txt", "phones.txt", "foreigingkeys.txt");

    while (true) {
        cout << "\nUniversity System\n"
            << "1. Search Phone by Price (Linear Search)\n"
            << "2. Search Phone by Price (Binary Search)\n"
            << "3. Search Phone by Price (Interpolation Search)\n"
            << "4. Print printInfo\n"
            << "5. Search Teacher by Name\n"
            << "9. Exit\n"
            << "Choose option: ";
        cin >> choice;
        cin.ignore();

        double price;
        string name;
        switch (choice) {
        case 1: {
            cout << "Enter price: ";
            cin >> price;
            findPhoneByPriceLinear(price);
            break;
        }
        case 2: {
            cout << "Enter price: ";
            cin >> price;
            findPhoneByPriceBinary(price);
            break;
        }
        case 3: {
            cout << "Enter price: ";
            cin >> price;
            findPhoneByPriceInterpolation(price);
            break;
        }
        case 4:
            printInfo();
            break;
        case 5:
            cout << "Enter teacher name: ";
            getline(cin, name);
            findTeacherByName(name);
            break;
        case 9:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}
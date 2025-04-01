#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Person {
    int surname_index;
    int first_name_index;
    string surname;
    string first_name;
};

vector<Person> people;

void sort_people() {
    sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
        return a.surname == b.surname ? a.first_name < b.first_name : a.surname < b.surname;
        });
    cout << "People sorted successfully.\n";
}

void display_people() {
    if (people.empty()) {
        cout << "No data available.\n";
        return;
    }
    cout << "Index Last Name | Index First Name | Last Name | First Name\n";
    cout << "-----------------------------------------------------------\n";
    for (const auto& person : people) {
        cout << person.surname_index << "               |" << person.surname << "               |"
            << person.first_name_index << "               |" << person.first_name << endl;
    }
}

void load_from_file() {
    ifstream file("people.txt");
    if (!file) {
        cout << "Error opening file for reading.\n";
        return;
    }
    people.clear();
    Person p;
    while (file >> p.surname_index >> p.surname >> p.first_name_index >> p.first_name) {
        people.push_back(p);
    }
    file.close();
    cout << "Data loaded from file.\n";
}

void save_to_file() {
    ofstream file("people.txt");
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (const auto& person : people) {
        file << person.surname_index << " " << person.surname << " "
            << person.first_name_index << " " << person.first_name << endl;
    }
    file.close();
    cout << "Data saved to file.\n";
}

void menu() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Display people\n";
        cout << "2. Sort people\n";
        cout << "3. Load from file\n";
        cout << "4. Save to file\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: display_people(); break;
        case 2: sort_people(); break;
        case 3: load_from_file(); break;
        case 4: save_to_file(); break;
        case 5: cout << "Exiting program.\n"; break;
        default: cout << "Invalid choice, try again.\n";
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
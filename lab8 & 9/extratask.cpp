#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

struct Person {
    int id;
    string name;
    int age;
    int index;
};

bool compareByName( Person& a, Person& b) {
    return a.name < b.name;
}

void loadData(string filename, vector<Person>& people) {
    ifstream inputFile(filename);

    Person person;
    while (inputFile >> person.id >> person.name >> person.age) {
        people.push_back(person);
    }

    inputFile.close();
}

void saveData(string filename, vector<Person>& people) {
    ofstream outputFile(filename);

    for (int i = 0; i < people.size(); ++i) {
        const Person& person = people[i];
        outputFile << person.id << " " << person.name << " " << person.age << " " << i << endl;
    }

    outputFile.close();
}

void searchByIndex(const vector<Person>& people, int index) {
    if (index < 0 || index >= people.size()) {
        cout << "Invalid index!" << endl;
        return;
    }

    const Person& person = people[index];
    cout << "Found: ID: " << person.id << ", Name: " << person.name << ", Age: " << person.age << ", Index: " << person.index << endl;
}

int main() {
    vector<Person> people;

    loadData("input_people.txt", people);

    sort(people.begin(), people.end(), compareByName);

    for (int i = 0; i < people.size(); ++i) {
        people[i].index = i;
    }

    saveData("sorted_people.txt", people);

    int index;
    cout << "Enter index to search: ";
    cin >> index;

    searchByIndex(people, index);

    return 0;
}

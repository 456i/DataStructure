#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <algorithm>
using namespace std;

// Teacher management system
struct Teacher {
    int id;
    string name;
    string subject;
    string phone;
    string city;
};

// Additional data structures
struct Student {
    string firstName;
    string lastName;
    int age;
    double gpa;
};

struct Phone {
    string model;
    string manufacturer;
    double price;
};

struct Product {
    string name;
    double price;
    string manufacturer;
    string description;
};

class University {
private:
    // Teacher data
    vector<Teacher> teachers;
    unordered_map<int, Teacher*> teacherIndex;
    unordered_map<string, Teacher*> phoneIndex;
    unordered_multimap<string, Teacher*> cityIndex;
    int nextId = 1;

    // Additional data
    vector<Student> students;
    vector<Phone> phones;
    vector<Product> products;

public:
    // Teacher operations
    void addTeacher(const string& name, const string& subject, const string& phone, const string& city) {
        teachers.push_back({ nextId, name, subject, phone, city });
        teacherIndex[nextId] = &teachers.back();
        phoneIndex[phone] = &teachers.back();
        cityIndex.insert({ city, &teachers.back() });
        cout << "Teacher added with ID: " << nextId++ << endl;
    }

    void findTeacher(int id) {
        auto it = teacherIndex.find(id);
        if (it != teacherIndex.end()) {
            Teacher* t = it->second;
            cout << "Found: " << t->name << " | " << t->subject
                << " | " << t->phone << " | " << t->city << endl;
        }
        else {
            cout << "Teacher not found!" << endl;
        }
    }

    // File loading
    void loadStudents(const string& filename) {
        ifstream file(filename);
        Student s;
        while (file >> s.firstName >> s.lastName >> s.age >> s.gpa) {
            students.push_back(s);
        }
    }

    void loadPhones(const string& filename) {
        ifstream file(filename);
        Phone p;
        while (file >> p.model >> p.manufacturer >> p.price) {
            phones.push_back(p);
        }
        sort(phones.begin(), phones.end(),
            [](const Phone& a, const Phone& b) { return a.price < b.price; });
    }

    void loadProducts(const string& filename) {
        ifstream file(filename);
        Product p;
        while (getline(file, p.name, ',') && file >> p.price &&
            getline(file >> ws, p.manufacturer, ',') &&
            getline(file >> ws, p.description)) {
            products.push_back(p);
        }
        sort(products.begin(), products.end(),
            [](const Product& a, const Product& b) { return a.price < b.price; });
    }

    // Search implementations
    void linearSearchStudent(const string& target) {
        for (const auto& s : students) {
            if (s.firstName == target || s.lastName == target) {
                cout << s.firstName << " " << s.lastName
                    << " | Age: " << s.age << " | GPA: " << s.gpa << endl;
                return;
            }
        }
        cout << "Student not found!" << endl;
    }

    void binarySearchPhone(double maxPrice) {
        int left = 0, right = phones.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (phones[mid].price <= maxPrice) {
                cout << "Found: " << phones[mid].model
                    << " | " << phones[mid].manufacturer
                    << " | $" << phones[mid].price << endl;
                return;
            }
            else {
                right = mid - 1;
            }
        }
        cout << "Phone not found under $" << maxPrice << endl;
    }

    void interpolationSearchProduct(double targetPrice) {
        int low = 0, high = products.size() - 1;

        while (low <= high && targetPrice >= products[low].price
            && targetPrice <= products[high].price) {

            int pos = low + ((targetPrice - products[low].price) * (high - low))
                / (products[high].price - products[low].price);

            if (products[pos].price == targetPrice) {
                cout << "Found: " << products[pos].name
                    << " | $" << products[pos].price << endl;
                return;
            }
            if (products[pos].price < targetPrice)
                low = pos + 1;
            else
                high = pos - 1;
        }
        cout << "Product not found at $" << targetPrice << endl;
    }
};

int main() {
    University uni;
    int choice;
    string filename;

    // Load sample data
    uni.loadStudents("students.txt");
    uni.loadPhones("phones.txt");
    uni.loadProducts("products.txt");

    while (true) {
        cout << "\nUniversity System\n1. Add Teacher\n2. Find Teacher\n3. Student Search\n"
            << "4. Phone Search\n5. Product Search\n6. Exit\nChoose option: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, subject, phone, city;
            cout << "Enter name: "; cin >> name;
            cout << "Enter subject: "; cin >> subject;
            cout << "Enter phone: "; cin >> phone;
            cout << "Enter city: "; cin >> city;
            uni.addTeacher(name, subject, phone, city);
            break;
        }
        case 2: {
            int id;
            cout << "Enter teacher ID: "; cin >> id;
            uni.findTeacher(id);
            break;
        }
        case 3: {
            string name;
            cout << "Enter student name: "; cin >> name;
            uni.linearSearchStudent(name);
            break;
        }
        case 4: {
            double price;
            cout << "Enter max price: "; cin >> price;
            uni.binarySearchPhone(price);
            break;
        }
        case 5: {
            double price;
            cout << "Enter exact price: "; cin >> price;
            uni.interpolationSearchProduct(price);
            break;
        }
        case 6:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}
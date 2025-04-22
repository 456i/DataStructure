//main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include "sort_algorithms.h"

using namespace std;
using namespace std::chrono;

// Data structures
struct Teacher {
    int id;
    string name;
    string subject;
    int experience;
};

struct Phone {
    int id;
    string number;
    string model;
    int year;
};

struct TeacherPhone {
    int teacher_id;
    int phone_id;
};

// Functions for loading data
vector<Teacher> load_teachers(const string& filename) {
    vector<Teacher> teachers;
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        Teacher teacher;
        ss >> teacher.id >> teacher.name >> teacher.subject >> teacher.experience;
        teachers.push_back(teacher);
    }
    
    return teachers;
}

vector<Phone> load_phones(const string& filename) {
    vector<Phone> phones;
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        Phone phone;
        ss >> phone.id >> phone.number >> phone.model >> phone.year;
        phones.push_back(phone);
    }
    
    return phones;
}

vector<TeacherPhone> load_relations(const string& filename) {
    vector<TeacherPhone> relations;
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        TeacherPhone relation;
        ss >> relation.teacher_id >> relation.phone_id;
        relations.push_back(relation);
    }
    
    return relations;
}

// Comparison functions for structures
int compare_teacher_name(const void* a, const void* b) {
    return ((Teacher*)a)->name.compare(((Teacher*)b)->name);
}

int compare_teacher_experience(const void* a, const void* b) {
    return ((Teacher*)a)->experience - ((Teacher*)b)->experience;
}

int compare_phone_number(const void* a, const void* b) {
    return ((Phone*)a)->number.compare(((Phone*)b)->number);
}

int compare_phone_year(const void* a, const void* b) {
    return ((Phone*)a)->year - ((Phone*)b)->year;
}

// Function for printing sort results
void print_sort_results(const SortResult& result) {
    cout << result.name << ": " << result.time << " seconds\n";
}

// Function for printing teachers
void print_teachers(const vector<Teacher>& teachers) {
    cout << "\nTeachers list:\n";
    cout << "ID\t\tName\t\tSubject\t\tExperience\n";
    for (const auto& teacher : teachers) {
        cout << teacher.id << "\t\t" << teacher.name << "\t\t" << teacher.subject << "\t\t" 
             << teacher.experience << "\n";
    }
}

// Function for printing phones
void print_phones(const vector<Phone>& phones) {
    cout << "\nPhones list:\n";
    cout << "ID\t\tNumber\t\tModel\t\tYear\n";
    for (const auto& phone : phones) {
        cout << phone.id << "\t\t" << phone.number << "\t\t" << phone.model << "\t\t" 
             << phone.year << "\n";
    }
}

// Function for displaying teacher information
void display_teacher_info(const vector<Teacher>& teachers, const vector<Phone>& phones, const vector<TeacherPhone>& relations) {
    cout << "\n=== TEACHER INFORMATION ===\n";
    cout << "Total number of teachers: " << teachers.size() << "\n\n";
    
    if (teachers.empty()) {
        cout << "No teacher data available.\n";
        return;
    }
    
    // Display all teachers
    cout << "All teachers:\n";
    for (size_t i = 0; i < teachers.size(); ++i) {
        cout << i + 1 << ". " << teachers[i].name << " - " << teachers[i].subject 
             << ", " << teachers[i].experience << " years\n";
        
        // Find phones for this teacher
        cout << "   Phones: ";
        bool has_phones = false;
        for (const auto& relation : relations) {
            if (relation.teacher_id == teachers[i].id) {
                for (const auto& phone : phones) {
                    if (phone.id == relation.phone_id) {
                        cout << phone.number << " (" << phone.model << ", " << phone.year << ") ";
                        has_phones = true;
                        break;
                    }
                }
            }
        }
        if (!has_phones) {
            cout << "No phones assigned";
        }
        cout << "\n";
    }
}

// Function for displaying phone information
void display_phone_info(const vector<Phone>& phones, const vector<Teacher>& teachers, const vector<TeacherPhone>& relations) {
    cout << "\n=== PHONE INFORMATION ===\n";
    cout << "Total number of phone records: " << phones.size() << "\n\n";
    
    if (phones.empty()) {
        cout << "No phone data available.\n";
        return;
    }
    
    // Display all phones
    cout << "All phone records:\n";
    for (size_t i = 0; i < phones.size(); ++i) {
        cout << i + 1 << ". " << phones[i].number << " (" << phones[i].model << ", " 
             << phones[i].year << ")\n";
        
        // Find teachers for this phone
        cout << "   Assigned to: ";
        bool has_teachers = false;
        for (const auto& relation : relations) {
            if (relation.phone_id == phones[i].id) {
                for (const auto& teacher : teachers) {
                    if (teacher.id == relation.teacher_id) {
                        cout << teacher.name << " ";
                        has_teachers = true;
                        break;
                    }
                }
            }
        }
        if (!has_teachers) {
            cout << "No teachers assigned";
        }
        cout << "\n";
    }
}

// Function for sorting teachers
void sort_teachers(vector<Teacher>& teachers) {
    int choice;
    cout << "\nSelect sorting criteria for teachers:\n";
    cout << "1. By name\n";
    cout << "2. By experience\n";
    cout << "Your choice: ";
    cin >> choice;
    
    vector<void*> teacher_ptrs;
    for (auto& teacher : teachers) {
        teacher_ptrs.push_back(&teacher);
    }
    
    SortResult result;
    
    switch (choice) {
        case 1: {
            cout << "\nSelect sorting algorithm:\n";
            cout << "1. Bubble Sort\n";
            cout << "2. Quick Sort\n";
            cout << "3. Selection Sort\n";
            cout << "4. Insertion Sort\n";
            cout << "5. Merge Sort\n";
            cout << "Your choice: ";
            int algo_choice;
            cin >> algo_choice;
            
            switch (algo_choice) {
                case 1:
                    result = bubble_sort(teacher_ptrs, compare_teacher_name);
                    break;
                case 2:
                    result = quick_sort(teacher_ptrs, compare_teacher_name);
                    break;
                case 3:
                    result = selection_sort(teacher_ptrs, compare_teacher_name);
                    break;
                case 4:
                    result = insertion_sort(teacher_ptrs, compare_teacher_name);
                    break;
                case 5:
                    result = merge_sort(teacher_ptrs, compare_teacher_name);
                    break;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            print_sort_results(result);
            print_teachers(teachers);
            break;
        }
        case 2: {
            cout << "\nSelect sorting algorithm:\n";
            cout << "1. Bubble Sort\n";
            cout << "2. Quick Sort\n";
            cout << "3. Selection Sort\n";
            cout << "4. Insertion Sort\n";
            cout << "5. Merge Sort\n";
            cout << "Your choice: ";
            int algo_choice;
            cin >> algo_choice;
            
            switch (algo_choice) {
                case 1:
                    result = bubble_sort(teacher_ptrs, compare_teacher_experience);
                    break;
                case 2:
                    result = quick_sort(teacher_ptrs, compare_teacher_experience);
                    break;
                case 3:
                    result = selection_sort(teacher_ptrs, compare_teacher_experience);
                    break;
                case 4:
                    result = insertion_sort(teacher_ptrs, compare_teacher_experience);
                    break;
                case 5:
                    result = merge_sort(teacher_ptrs, compare_teacher_experience);
                    break;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            print_sort_results(result);
            print_teachers(teachers);
            break;
        }
        default:
            cout << "Invalid choice!\n";
            return;
    }
}

// Function for sorting phones
void sort_phones(vector<Phone>& phones) {
    int choice;
    cout << "\nSelect sorting criteria for phones:\n";
    cout << "1. By number\n";
    cout << "2. By year\n";
    cout << "Your choice: ";
    cin >> choice;
    
    vector<void*> phone_ptrs;
    for (auto& phone : phones) {
        phone_ptrs.push_back(&phone);
    }
    
    SortResult result;
    
    switch (choice) {
        case 1: {
            cout << "\nSelect sorting algorithm:\n";
            cout << "1. Bubble Sort\n";
            cout << "2. Quick Sort\n";
            cout << "3. Selection Sort\n";
            cout << "4. Insertion Sort\n";
            cout << "5. Merge Sort\n";
            cout << "Your choice: ";
            int algo_choice;
            cin >> algo_choice;
            
            switch (algo_choice) {
                case 1:
                    result = bubble_sort(phone_ptrs, compare_phone_number);
                    break;
                case 2:
                    result = quick_sort(phone_ptrs, compare_phone_number);
                    break;
                case 3:
                    result = selection_sort(phone_ptrs, compare_phone_number);
                    break;
                case 4:
                    result = insertion_sort(phone_ptrs, compare_phone_number);
                    break;
                case 5:
                    result = merge_sort(phone_ptrs, compare_phone_number);
                    break;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            print_sort_results(result);
            print_phones(phones);
            break;
        }
        case 2: {
            cout << "\nSelect sorting algorithm:\n";
            cout << "1. Bubble Sort\n";
            cout << "2. Quick Sort\n";
            cout << "3. Selection Sort\n";
            cout << "4. Insertion Sort\n";
            cout << "5. Merge Sort\n";
            cout << "Your choice: ";
            int algo_choice;
            cin >> algo_choice;
            
            switch (algo_choice) {
                case 1:
                    result = bubble_sort(phone_ptrs, compare_phone_year);
                    break;
                case 2:
                    result = quick_sort(phone_ptrs, compare_phone_year);
                    break;
                case 3:
                    result = selection_sort(phone_ptrs, compare_phone_year);
                    break;
                case 4:
                    result = insertion_sort(phone_ptrs, compare_phone_year);
                    break;
                case 5:
                    result = merge_sort(phone_ptrs, compare_phone_year);
                    break;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            print_sort_results(result);
            print_phones(phones);
            break;
        }
        default:
            cout << "Invalid choice!\n";
            return;
    }
}

int main() {
    // Load data
    auto teachers = load_teachers("teachers.txt");
    auto phones = load_phones("phones.txt");
    auto relations = load_relations("foreigingkeys.txt");
    
    cout << "Data loaded successfully\n";
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Sort teachers\n";
        cout << "2. Sort phones\n";
        cout << "3. Display teacher information\n";
        cout << "4. Display phone information\n";
        cout << "5. Exit\n";
        cout << "Your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                sort_teachers(teachers);
                break;
            case 2:
                sort_phones(phones);
                break;
            case 3:
                display_teacher_info(teachers, phones, relations);
                break;
            case 4:
                display_phone_info(phones, teachers, relations);
                break;
            case 5:
                cout << "Program terminated.\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    
    return 0;
}

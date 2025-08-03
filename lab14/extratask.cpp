#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Teacher {
    int id;
    int experience;
    string name;
    vector<string> subjects;
};

struct Phone {
    int id;
    int price;
    string number;
    string model;
};

struct TeacherPhoneKey {
    int local_id;
    int teacher_id;
    int phone_id;
};

vector<Teacher> load_teachers(const string& filename) {
    vector<Teacher> teachers;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Teacher teacher;
        string subject;
        ss >> teacher.id >> teacher.name >> teacher.experience;
        while (ss >> subject) teacher.subjects.push_back(subject);
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
        ss >> phone.id >> phone.number >> phone.model >> phone.price;
        phones.push_back(phone);
    }

    return phones;
}

vector<TeacherPhoneKey> load_relations(const string& filename) {
    vector<TeacherPhoneKey> relations;
    ifstream file(filename);
    string line;
    int local_id = 1;

    while (getline(file, line)) {
        stringstream ss(line);
        TeacherPhoneKey relation;
        ss >> relation.teacher_id >> relation.phone_id;
        relation.local_id = local_id++;
        relations.push_back(relation);
    }

    return relations;
}

void display_teachers(const vector<Teacher>& teachers) {
    cout << "\nСписок преподавателей:\n";
    cout << "ID\tИмя\tСтаж\tПредметы\n";

    for (auto teacher : teachers) {
        cout << teacher.id << "\t" << teacher.name << "\t" << teacher.experience << "\t";
        for (string subject : teacher.subjects) {
            cout << subject << " ";
        }
        cout << endl;
    }
}

void display_phones(const vector<Phone>& phones) {
    cout << "\nСписок телефонов:\n";
    cout << "ID\tНомер\tМодель\tЦена\n";

    for (auto phone : phones) {
        cout << phone.id << "\t" << phone.number << "\t" << phone.model << "\t"
            << phone.price << " руб." << endl;
    }
}

void display_relations(const vector<Teacher>& teachers, const vector<Phone>& phones,
    const vector<TeacherPhoneKey>& relations) {
    cout << "\nСвязи преподавателей и телефонов:\n";
    cout << "ID связи\tПреподаватель\tТелефон\tМодель\tЦена\n";

    for (auto relation : relations) {
        string teacher_name = "Неизвестно";
        for (auto teacher : teachers) {
            if (teacher.id == relation.teacher_id) {
                teacher_name = teacher.name;
                break;
            }
        }

        string phone_number = "Неизвестно";
        string phone_model = "Неизвестно";
        string phone_price = "Неизвестно";
        for (auto phone : phones) {
            if (phone.id == relation.phone_id) {
                phone_number = phone.number;
                phone_model = phone.model;
                phone_price = to_string(phone.price);
                break;
            }
        }

        cout << relation.local_id << "\t\t" << teacher_name << "\t\t" << phone_number
            << "\t" << phone_model << "\t" << phone_price << " руб." << endl;
    }
}

vector<Teacher> filter_teachers_by_experience(const vector<Teacher>& teachers, int min_exp) {
    vector<Teacher> result;

    for (auto teacher : teachers) {
        if (teacher.experience >= min_exp) {
            result.push_back(teacher);
        }
    }

    return result;
}

vector<Teacher> filter_teachers_by_subject(const vector<Teacher>& teachers, const string& subject) {
    vector<Teacher> result;

    for (auto teacher : teachers) {
        for (auto subj : teacher.subjects) {
            if (subj == subject) {
                result.push_back(teacher);
                break;
            }
        }
    }

    return result;
}

vector<Teacher> find_teachers_with_phone_price(const vector<Teacher>& teachers,
    const vector<Phone>& phones,
    const vector<TeacherPhoneKey>& relations,
    int min_price) {
    vector<Teacher> result;
    vector<int> teacher_ids;

    for (auto phone : phones) {
        if (phone.price >= min_price) {
            for (auto relation : relations) {
                if (relation.phone_id == phone.id) {
                    teacher_ids.push_back(relation.teacher_id);
                }
            }
        }
    }

    for (int id : teacher_ids) {
        for (auto teacher : teachers) {
            if (teacher.id == id) {
                result.push_back(teacher);
                break;
            }
        }
    }

    return result;
}

int main() {
    auto teachers = load_teachers("teachers.txt");
    auto phones = load_phones("phones.txt");
    auto relations = load_relations("foreigingkeys.txt");

    cout << "Данные успешно загружены\n";

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Вывести всех преподавателей\n";
        cout << "2. Вывести все телефоны\n";
        cout << "3. Вывести связи преподавателей и телефонов\n";
        cout << "4. Фильтр преподавателей по стажу\n";
        cout << "5. Фильтр преподавателей по предмету\n";
        cout << "6. Найти преподавателей с телефонами определенной цены\n";
        cout << "7. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            display_teachers(teachers);
            break;

        case 2:
            display_phones(phones);
            break;

        case 3:
            display_relations(teachers, phones, relations);
            break;

        case 4: {
            int min_exp;
            cout << "Введите минимальный стаж: ";
            cin >> min_exp;

            auto filtered = filter_teachers_by_experience(teachers, min_exp);
            cout << "\nНайдено преподавателей: " << filtered.size() << "\n";
            display_teachers(filtered);
            break;
        }

        case 5: {
            string subject;
            cout << "Введите предмет: ";
            cin >> subject;

            auto filtered = filter_teachers_by_subject(teachers, subject);
            cout << "\nНайдено преподавателей: " << filtered.size() << "\n";
            display_teachers(filtered);
            break;
        }

        case 6: {
            int min_price;
            cout << "Введите минимальную цену телефона: ";
            cin >> min_price;

            auto filtered = find_teachers_with_phone_price(teachers, phones, relations, min_price);
            cout << "\nНайдено преподавателей: " << filtered.size() << "\n";
            display_teachers(filtered);
            break;
        }

        case 7:
            break;

        default:
            cout << "Неверный выбор!\n";
        }
    } while (choice != 7);

    return 0;
}

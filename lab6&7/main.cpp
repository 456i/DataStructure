#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Teacher {
    int id;
    string name;
    string subject;
    string phone;
    string city;
};

class University {
private:
    vector<Teacher> teachers;
    unordered_map<int, Teacher*> teacherIndex;
    unordered_map<string, Teacher*> phoneIndex;
    unordered_multimap<string, Teacher*> cityIndex;
    int nextId = 1;

public:
    void addTeacher(const string& name, const string& subject, const string& phone, const string& city) {
        teachers.push_back({ nextId, name, subject, phone, city });
        teacherIndex[nextId] = &teachers.back();
        phoneIndex[phone] = &teachers.back();
        cityIndex.insert({ city, &teachers.back() });
        cout << "Преподаватель добавлен с ID: " << nextId << endl;
        nextId++;
    }

    void findTeacher(int id) {
        if (teacherIndex.find(id) != teacherIndex.end()) {
            Teacher* t = teacherIndex[id];
            cout << "Найден преподаватель: " << t->name << ", предмет: " << t->subject << ", телефон: " << t->phone << ", город: " << t->city << endl;
        } else {
            cout << "Преподаватель с таким ID не найден." << endl;
        }
    }

    void findTeacherByPhone(const string& phone) {
        if (phoneIndex.find(phone) != phoneIndex.end()) {
            Teacher* t = phoneIndex[phone];
            cout << "Найден преподаватель: " << t->name << ", предмет: " << t->subject << ", телефон: " << t->phone << ", город: " << t->city << endl;
        } else {
            cout << "Преподаватель с таким номером телефона не найден." << endl;
        }
    }

    void findTeachersByCity(const string& city) {
        auto range = cityIndex.equal_range(city);
        bool found = false;
        for (auto it = range.first; it != range.second; ++it) {
            Teacher* t = it->second;
            cout << "Найден преподаватель: " << t->name << ", предмет: " << t->subject << ", телефон: " << t->phone << ", город: " << t->city << endl;
            found = true;
        }
        if (!found) {
            cout << "Преподаватели в данном городе не найдены." << endl;
        }
    }

    void removeTeacher(int id) {
        if (teacherIndex.find(id) != teacherIndex.end()) {
            Teacher* t = teacherIndex[id];
            phoneIndex.erase(t->phone);
            auto range = cityIndex.equal_range(t->city);
            for (auto it = range.first; it != range.second; ) {
                if (it->second == t) {
                    it = cityIndex.erase(it);
                } else {
                    ++it;
                }
            }
            teacherIndex.erase(id);
            teachers.erase(remove_if(teachers.begin(), teachers.end(), [id](const Teacher& t) {
                return t.id == id;
            }), teachers.end());
            cout << "Преподаватель удален." << endl;
        } else {
            cout << "Преподаватель с таким ID не найден." << endl;
        }
    }

    void listTeachers() {
        for (const auto& t : teachers) {
            cout << "ID: " << t.id << ", Имя: " << t.name << ", Предмет: " << t.subject << ", Телефон: " << t.phone << ", Город: " << t.city << endl;
        }
    }
};

int main() {
    University uni;
    int choice, id;
    string name, subject, phone, city;

    while (true) {
        cout << "\n1. Добавить преподавателя\n2. Найти преподавателя по ID\n3. Найти преподавателя по телефону\n4. Найти преподавателей по городу\n5. Удалить преподавателя\n6. Список преподавателей\n7. Выйти\nВаш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите имя: ";
                cin >> name;
                cout << "Введите предмет: ";
                cin >> subject;
                cout << "Введите телефон: ";
                cin >> phone;
                cout << "Введите город: ";
                cin >> city;
                uni.addTeacher(name, subject, phone, city);
                break;
            case 2:
                cout << "Введите ID: ";
                cin >> id;
                uni.findTeacher(id);
                break;
            case 3:
                cout << "Введите телефон: ";
                cin >> phone;
                uni.findTeacherByPhone(phone);
                break;
            case 4:
                cout << "Введите город: ";
                cin >> city;
                uni.findTeachersByCity(city);
                break;
            case 5:
                cout << "Введите ID: ";
                cin >> id;
                uni.removeTeacher(id);
                break;
            case 6:
                uni.listTeachers();
                break;
            case 7:
                return 0;
            default:
                cout << "Неверный ввод! Попробуйте снова." << endl;
        }
    }
}

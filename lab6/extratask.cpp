#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

struct PersonTown {
    int id;
    string name;
    string town;
};

struct PersonCoffee {
    int id;
    vector<string> coffee_shops;
};

vector<PersonTown> people_towns;
vector<PersonCoffee> people_coffees;
int id_counter = 1;

void display_data() {
    cout << "\nСписок людей и их городов:" << endl;
    for (auto person : people_towns) {
        cout << person.id << ": " << person.name << " - " << person.town << endl;
    }
    cout << "\nЛюбимые кофейни:" << endl;
    for (auto cafe : people_coffees) {
        cout << cafe.id << ": ";
        for (const auto& shop : cafe.coffee_shops) {
            cout << shop << " ";
        }
        cout << endl;
    }
}

void sort_people() {
    sort(people_towns.begin(), people_towns.end(), [](const PersonTown& a, const PersonTown& b) {
        return a.name < b.name;
        });
    vector<int> id_order;
    for (const auto& person : people_towns) {
        id_order.push_back(person.id);
    }
    sort(people_coffees.begin(), people_coffees.end(), [&id_order](const PersonCoffee& a, const PersonCoffee& b) {
        return find(id_order.begin(), id_order.end(), a.id) < find(id_order.begin(), id_order.end(), b.id);
        });
    cout << "\nДанные отсортированы по имени." << endl;
}

void create_person() {
    string name, town, coffee_input;
    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите название города (Москва, Санкт-Петербург, Казань, Новосибирск, Екатеринбург): ";
    cin >> town;
    people_towns.push_back({ id_counter, name, town });

    cout << "Введите названия кафе через пробел: ";
    cin.ignore();
    getline(cin, coffee_input);
    stringstream ss(coffee_input);
    vector<string> coffee_shops;
    string shop;
    while (ss >> shop) {
        coffee_shops.push_back(shop);
    }
    people_coffees.push_back({ id_counter, coffee_shops });
    id_counter++;
    cout << "Человек добавлен!" << endl;
}

void menu() {
    while (true) {
        cout << "\nМеню:" << endl;
        cout << "1. Показать данные" << endl;
        cout << "2. Отсортировать по имени" << endl;
        cout << "3. Добавить человека" << endl;
        cout << "4. Выйти" << endl;
        cout << "Выберите действие: ";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            display_data();
            break;
        case 2:
            sort_people();
            break;
        case 3:
            create_person();
            break;
        case 4:
            return;
        default:
            cout << "Некорректный ввод. Попробуйте снова." << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}

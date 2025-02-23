#include <algorithm>  // Для сортировки
#include <map>
#include <list>
#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Задача 1: Использование перечислений для выбора страны
enum Country {
    USA, Canada, Mexico, Brazil, Germany, France, Japan, India, China, Russia
};

// Функция task1: Демонстрация работы с перечислением стран
void task1() {
    cout << "*** TASK1 ***" << endl;
    int choice;
    cout << "Select a country:\n1. USA\n2. Canada\n3. Mexico\n4. Brazil\n5. Germany\n6. France\n7. Japan\n8. India\n9. China\n10. Russia\n";
    cin >> choice;

    // Используем switch, чтобы в зависимости от выбора пользователя вывести страну
    switch (choice) {
    case 1: cout << "USA"; break;
    case 2: cout << "Canada"; break;
    case 3: cout << "Mexico"; break;
    case 4: cout << "Brazil"; break;
    case 5: cout << "Germany"; break;
    case 6: cout << "France"; break;
    case 7: cout << "Japan"; break;
    case 8: cout << "India"; break;
    case 9: cout << "China"; break;
    case 10: cout << "Russia"; break;
    default: cout << "Invalid choice"; break; // Если выбор не соответствует ни одному из случаев
    }
    cout << endl;
}

// Задача 2: Добавление элементов в начало и конец массива
void task2() {
    cout << "*** TASK2 ***" << endl;
    vector<int> vec = { 1, 2, 3, 4, 5 }; // Инициализируем исходный вектор
    int n = 3; // Количество добавляемых элементов
    vector<int> toAdd = { 10, 20, 30 }; // Вектор элементов для добавления

    // Добавляем элементы в начало вектора
    vec.insert(vec.begin(), toAdd.begin(), toAdd.end());

    // Добавляем элементы в конец вектора
    vec.insert(vec.end(), toAdd.begin(), toAdd.end());

    // Выводим изменённый вектор
    cout << "Updated vector: ";
    for (int num : vec) {
        cout << num << " "; // Печатаем каждый элемент вектора
    }
    cout << endl;
}

// Задача 3: Рассчёт среднего арифметического элементов вектора
void task3() {
    cout << "*** TASK3 ***" << endl;
    vector<int> vec = { 10, 20, 30, 40, 50, 60 }; // Исходный вектор
    double sum = 0; // Переменная для хранения суммы элементов

    // Суммируем все элементы вектора
    for (auto num : vec) sum += num;

    // Рассчитываем и выводим среднее значение
    cout << "Average value of vec: " << sum / vec.size() << endl << endl; // Делим сумму на количество элементов
}

// Задача 4: Поиск минимальных и максимальных элементов в deque
void task4() {
    cout << "*** TASK4 ***" << endl;
    deque<int> dq = { 10, 20, 30, 40, 50, 60 }; // Инициализируем deque
    int max_elem = INT32_MIN; // Инициализация максимального элемента
    int min_elem = INT32_MAX; // Инициализация минимального элемента

    // Итерация через deque с использованием итераторов
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        if (*it > max_elem) max_elem = *it; // Если текущий элемент больше max_elem, обновляем max_elem
        if (*it < min_elem) min_elem = *it; // Если текущий элемент меньше min_elem, обновляем min_elem
    }

    // Добавляем найденные элементы в конец и начало deque
    dq.push_back(max_elem); // Максимальный элемент в конец
    dq.push_front(min_elem); // Минимальный элемент в начало

    // Выводим элементы deque
    for (auto num : dq) cout << num << " "; // Проходим по всем элементам deque и выводим их
    cout << endl << endl;
}

// Задача 5: Работа с односвязным списком
struct Node { // Структура для узла односвязного списка
    int data; // Данные, хранящиеся в узле
    Node* next; // Указатель на следующий узел

    Node(int val) : data(val), next(nullptr) {} // Конструктор для инициализации узла значением val
};

// Функция для удаления всех узлов списка
void deleteList(Node*& head) {
    // Пока список не пуст
    while (head != nullptr) {
        Node* temp = head; // Сохраняем текущий узел
        head = head->next; // Перемещаем голову на следующий узел
        delete temp; // Удаляем текущий узел
    }
}

// Функция для добавления n узлов в начало списка
void addNodes(Node*& head, int n) {
    for (int i = 1; i <= n; ++i) {
        Node* newNode = new Node(i); // Создаём новый узел
        newNode->next = head; // Новый узел указывает на текущую голову списка
        head = newNode; // Обновляем голову списка
    }
}

// Функция для вывода списка
void printList(Node* head) {
    // Пока список не пуст
    while (head != nullptr) {
        cout << head->data << " "; // Печатаем данные текущего узла
        head = head->next; // Переходим к следующему узлу
    }
    cout << endl;
}

// Задача 5: Демонстрация работы с односвязным списком
void task5() {
    cout << "*** TASK5 ***" << endl;
    Node* head = nullptr; // Инициализируем голову списка (пустой список)

    addNodes(head, 5); // Добавляем 5 узлов в начало списка

    cout << "List after adding nodes: ";
    printList(head); // Печатаем список после добавления узлов

    deleteList(head); // Удаляем все узлы из списка
    cout << "List after deletion: ";
    printList(head); // Печатаем список после удаления узлов
}

// Задача 6: Работа с двусвязным списком (std::list)
void task6() {
    cout << "*** TASK6 ***" << endl;
    list<int> myList = { 1, 2, 3, 4, 5 }; // Инициализируем двусвязный список
    int n = 3; // Количество добавляемых элементов
    list<int> toAdd = { 10, 20, 30 }; // Список элементов для добавления

    // Добавляем элементы в начало списка
    myList.insert(myList.begin(), toAdd.begin(), toAdd.end());

    // Добавляем элементы в конец списка
    myList.insert(myList.end(), toAdd.begin(), toAdd.end());

    // Печатаем обновлённый список
    cout << "Updated list: ";
    for (int num : myList) {
        cout << num << " "; // Печатаем каждый элемент
    }
    cout << endl;
}

// Задача 7: Поиск по map
void task7() {
    cout << "*** TASK7 ***" << endl;
    map<int, string> myMap = { {1, "One"}, {2, "Two"}, {3, "Three"} }; // Инициализация map
    int searchValue;

    cout << "Enter a number to search in the map: ";
    cin >> searchValue;

    // Поиск значения по ключу в map
    auto it = myMap.find(searchValue);
    if (it != myMap.end()) { // Если элемент найден
        cout << "Found: " << it->first << " -> " << it->second << endl;
    }
    else {
        cout << "Number not found in the map." << endl; // Если элемент не найден
    }
}

void additionalTask1() {
    cout << "*** TASK1 ***" << endl;

    // Инициализируем два вектора с целыми числами
    vector<int> vec1 = { 1, 2, 3, 4, 5 };
    vector<int> vec2 = { 6, 7, 8, 9, 10 };

    // Объединяем два вектора в один с помощью insert
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());

    // Выводим элементы объединённого вектора
    cout << "Merged vector: ";
    for (int num : vec1) {
        cout << num << " ";  // Печатаем каждый элемент вектора
    }
    cout << endl;
}


enum Month {
    January, February, March, April, May, June, July, August, September, October, November, December
};

void additionalTask2() {
    cout << "*** TASK2 ***" << endl;

    // Создаём дек для хранения месяцев
    deque<Month> months = { Month::January, Month::February, Month::March, Month::April, Month::May };

    // Добавляем новые месяцы в дек
    months.push_back(Month::June);
    months.push_back(Month::July);

    // Удаляем первый и последний элемент
    months.pop_front();
    months.pop_back();

    // Выводим оставшиеся месяцы
    cout << "Updated deque of months: ";
    for (auto month : months) {
        switch (month) {  // Выводим название месяца
        case Month::January: cout << "January "; break;
        case Month::February: cout << "February "; break;
        case Month::March: cout << "March "; break;
        case Month::April: cout << "April "; break;
        case Month::May: cout << "May "; break;
        case Month::June: cout << "June "; break;
        case Month::July: cout << "July "; break;
        case Month::August: cout << "August "; break;
        case Month::September: cout << "September "; break;
        case Month::October: cout << "October "; break;
        case Month::November: cout << "November "; break;
        case Month::December: cout << "December "; break;
        }
    }
    cout << endl;
}


void additionalTask3() {
    cout << "*** TASK3 ***" << endl;

    // Инициализируем массив строк
    vector<string> strs = { "apple", "banana", "kiwi", "mango", "cherry", "peach" };

    // Сортируем строки по длине, а затем лексикографически
    sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
        if (a.size() == b.size()) {
            return a < b;  // Если длины одинаковые, сортируем лексикографически
        }
        return a.size() < b.size();  // Сортируем по длине
        });

    // Выводим отсортированный массив
    cout << "Sorted array of strings: ";
    for (const auto& str : strs) {
        cout << str << " ";  // Печатаем каждую строку
    }
    cout << endl;
}

// Главная функция, вызывающая все задачи
int main() {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    additionalTask1();
    additionalTask2();
    additionalTask3();
    return 0;
}
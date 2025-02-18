#include <iostream>
#include <vector>
#include <deque>
using namespace std;

// Задача 1: Объединить два массива в один
void task1() {
    cout << "*** TASK1 ***" << endl;
    // Инициализация двух векторов с целыми числами
    vector<int> vec1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<int> vec2 = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

    // Создание нового вектора для объединённых данных
    vector<int> mergedVec;

    // Добавляем все элементы из vec1 в mergedVec
    mergedVec.insert(mergedVec.end(), vec1.begin(), vec1.end());

    // Добавляем все элементы из vec2 в mergedVec
    mergedVec.insert(mergedVec.end(), vec2.begin(), vec2.end());

    // Выводим объединённый вектор
    cout << "Merged vector: ";
    for (int num : mergedVec) {
        cout << num << " "; // Печатаем каждый элемент вектора
    }
    cout << endl; // Переход на новую строку после вывода всех элементов
}

// Задача 3: Рассчитать среднее значение элементов вектора
void task3() {
    cout << "*** TASK3 ***" << endl;
    vector<int> vec = { 10, 20, 30, 40 , 50 , 60 };
    int sum = 0;

    // Суммируем все элементы вектора
    for (auto num : vec)
        sum += num;

    // Выводим среднее значение элементов вектора
    cout << "Average value of vec: " << sum / size(vec) << endl << endl;
}

// Задача 4: Найти минимальный и максимальный элементы в deque
void task4() {
    cout << "*** TASK4 ***" << endl;
    deque<int> dq = { 10, 20, 30, 40 , 50 , 60 };
    int max_elem = INT32_MIN; // Инициализируем максимальный элемент минимальным значением
    int min_elem = INT32_MAX; // Инициализируем минимальный элемент максимальным значением

    // Проходим по всем элементам deque
    for (int i = 1; i < dq.size(); ++i) {
        // Находим максимальный элемент
        if (dq[i] > max_elem) {
            max_elem = dq[i];
        }
        // Находим минимальный элемент
        if (dq[i] < min_elem) {
            min_elem = dq[i];
        }
    }

    // Добавляем максимальный элемент в конец deque
    dq.push_back(max_elem);
    // Добавляем минимальный элемент в начало deque
    dq.push_front(min_elem);

    int num;
    // Пока deque не пуст
    while (!dq.empty()) {
        num = dq.front(); // Получаем элемент с начала deque
        cout << num << " "; // Печатаем элемент
        dq.pop_front(); // Удаляем этот элемент
    }
    cout << endl << endl; // Переход на новую строку после вывода всех элементов
}

// Структура для узла списка (Node)
struct Node {
    int data; // Данные, хранящиеся в узле (например, целое число)
    Node* next; // Указатель на следующий узел в списке

    // Конструктор для инициализации узла
    Node(int val) : data(val), next(nullptr) {} // Инициализируем data 
    //значением val и устанавливаем next в nullptr
};

// Функция для удаления всего списка
void deleteList(Node*& head) {
    // Пока голова списка не равна nullptr (пока список не пуст)
    while (head != nullptr) {
        Node* temp = head; // Сохраняем текущий узел в temp
        head = head->next; // Перемещаем голову на следующий узел
        delete temp; // Удаляем текущий узел
    }
}

// Функция для добавления n узлов в начало списка
void addNodes(Node*& head, int n) {
    // Для каждого числа от 1 до n создаем новый узел и добавляем его в начало списка
    for (int i = 1; i <= n; ++i) {
        Node* newNode = new Node(i); // Создаем новый узел с данным значением
        newNode->next = head; // Указываем, что новый узел будет указывать на текущую голову списка
        head = newNode; // Обновляем голову списка, теперь это новый узел
    }
}

// Функция для вывода списка на экран
void printList(Node* head) {
    // Пока список не пуст
    while (head != nullptr) {
        cout << head->data << " "; // Выводим данные текущего узла
        head = head->next; // Переходим к следующему узлу
    }
    cout << endl; // Переводим строку после вывода всех данных
}

// Задача 5: Демонстрация работы с односвязным списком
void task5() {
    cout << "*** TASK5 ***" << endl;
    Node* head = nullptr; // Начальный указатель на голову списка (пустой список)

    // Добавляем 5 узлов в начало списка
    addNodes(head, 5); // Список будет: 5 -> 4 -> 3 -> 2 -> 1

    // Печатаем список
    cout << "List after adding nodes: ";
    printList(head); // Ожидаемый вывод: 5 4 3 2 1

    // Удаляем весь список
    deleteList(head);

    // Печатаем список после удаления
    cout << "List after deletion: ";
    printList(head); // Ожидаемый вывод: (пустой список)
}

int main() {
    task1(); // Вызываем задачу 1
    task3(); // Вызываем задачу 3
    task4(); // Вызываем задачу 4
    task5(); // Вызываем задачу 5
    return 0;
}

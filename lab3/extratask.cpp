#include <iostream>
#include <functional>

using namespace std;


double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
    if (b != 0) return a / b;
    cout << "Ошибка: деление на ноль!" << endl;
    return 0;
}

int main() {
    setlocale(LC_ALL, "rus");
    function<double(double, double)> operations[4] = { add, subtract, multiply, divide };

    int choice;
    double num1, num2;

    do {
        cout << "\nМеню:" << endl;
        cout << "1. Сложение" << endl;
        cout << "2. Вычитание" << endl;
        cout << "3. Умножение" << endl;
        cout << "4. Деление" << endl;
        cout << "5. Выход" << endl;
        cout << "Введите ваш выбор: ";
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            cout << "Введите два числа: ";
            cin >> num1 >> num2;
            cout << "Результат: " << operations[choice - 1](num1, num2) << endl;
        }
        else if (choice == 5) {
            cout << "Выход из программы..." << endl;
        }
        else {
            cout << "Неправильный выбор!" << endl;
        }
    } while (choice != 5);

    return 0;
}

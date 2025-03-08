#include <iostream>

using namespace std;

// Функция для отображения меню
void showMenu() {
    cout << "\n--- University Course Management ---\n"
        << "1. Add a new group\n"
        << "2. Show all groups\n"
        << "3. Add a student to a group\n"
        << "4. Remove a student from a group\n"
        << "5. Add a teacher\n"
        << "6. Show all teachers\n"
        << "7. Assign a teacher to a course\n"
        << "8. Show all courses\n"
        << "9. Exit\n"
        << "Choose an option: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Adding a new group...\n";
            // Здесь должен быть ввод данных о группе
            break;
        case 2:
            cout << "Showing all groups...\n";
            // Здесь должен быть вывод всех групп
            break;
        case 3:
            cout << "Adding a student to a group...\n";
            // Здесь добавление студента в выбранную группу
            break;
        case 4:
            cout << "Removing a student from a group...\n";
            // Здесь удаление студента из группы
            break;
        case 5:
            cout << "Adding a new teacher...\n";
            // Здесь ввод данных о преподавателе
            break;
        case 6:
            cout << "Showing all teachers...\n";
            // Здесь должен быть вывод всех преподавателей
            break;
        case 7:
            cout << "Assigning a teacher to a course...\n";
            // Здесь назначение преподавателя на курс
            break;
        case 8:
            cout << "Showing all courses...\n";
            // Здесь должен быть вывод всех курсов
            break;
        case 9:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    }

    return 0;
}
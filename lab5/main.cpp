#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <filesystem>

using namespace std;


void task1() {
    string filename = "data.txt";
    ofstream file(filename);
    if (!file) {
        cerr << "Failed to open the file!" << endl;
        return;
    }

    string data;
    cout << "Enter the data to write to the file: ";
    cin.ignore();
    getline(cin, data);

    file << data;
    file.close();
}


void task2() {
    string filename = "data.txt";
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open the file!" << endl;
        return;
    }

    string data;
    while (getline(file, data)) {
        cout << data << endl;
    }

    file.close();
}


void task3() {
    string filename = "task1.txt";
    ofstream file(filename);
    if (!file) {
        cerr << "Failed to open the file!" << endl;
        return;
    }

    file.close();
}


void task4() {
    string filename = "task1.txt";
    if (remove(filename.c_str()) != 0) {
        cerr << "Failed to delete the file!" << endl;
    }
    else {
        cout << "File successfully deleted!" << endl;
    }
}


void AdditionalTask1() {
    string dir;
    cout << "Enter the directory path: ";
    cin >> dir;

    for (const auto& entry : filesystem::directory_iterator(dir)) {
        cout << entry.path().filename() << " : " << filesystem::file_size(entry.path()) << " bytes" << endl;
    }
}


void AdditionalTask2() {
    string filename = "task1.bin";
    vector<char> search = { 'a', 'b', 'c' }; // Что ищем
    vector<char> replace = { 'x', 'y', 'z' }; // На что заменяем

    // 1. Открытие файла для чтения
    ifstream file(filename);
    if (!file) {
        cerr << "Failed to open the file!" << endl;
        return;
    }

    // 2. Чтение всего содержимого файла в вектор
    vector<char> content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // 3. Поиск и замена всех вхождений
    size_t pos = 0;
    while (true) {
        // Поиск подпоследовательности начиная с позиции pos
        auto it = search(content.begin() + pos, content.end(), search.begin(), search.end());

        // Если не нашли - выходим из цикла
        if (it == content.end()) break;

        // Вычисляем позицию найденной последовательности
        pos = it - content.begin();

        // Заменяем найденную последовательность
        copy(replace.begin(), replace.end(), content.begin() + pos);

        // Перемещаем позицию поиска вперед на длину замененной последовательности
        pos += replace.size();
    }

    // 4. Перезапись файла с измененным содержимым
    ofstream outFile(filename);
    outFile.write(content.data(), content.size());
    outFile.close();
}


void AdditionalTask3() {
    string filename = "task1.bin";

    // 1. Запись в файл
    ofstream file(filename);
    if (!file) {
        cerr << "Failed to open the file!" << endl;
        return;
    }

    int number = 42; // Данные для записи

    // Преобразуем число в последовательность байтов и записываем
    file.write(reinterpret_cast<char*>(&number), sizeof(number));
    file.close();

    // 2. Чтение из файла
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Failed to open the file!" << endl;
        return;
    }

    int readNumber;
    // Читаем байты из файла обратно в переменную
    inFile.read(reinterpret_cast<char*>(&readNumber), sizeof(readNumber));
    cout << "Data read from the binary file: " << readNumber << endl;
    inFile.close();
}


int main() {
    int task_number;
    cout << "Enter the task number (1-7): ";
    cin >> task_number;

    switch (task_number) {
    case 1:
        task1();
        break;
    case 2:
        task2();
        break;
    case 3:
        task3();
        break;
    case 4:
        task4();
        break;
    case 5:
        AdditionalTask1();
        break;
    case 6:
        AdditionalTask2();
        break;
    case 7:
        AdditionalTask3();
        break;
    default:
        cout << "Invalid task number!" << endl;
    }

    return 0;
}



#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("example.txt");
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Ошибка открытия файла" << endl;
    }

    return 0;
}

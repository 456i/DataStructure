#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void inputData(string& text) {
    cout << "Enter text: ";
    getline(cin, text);
}

void writeTextFile(string& text) {
    ofstream file("textfile.txt");
    if (file.is_open()) {
        file << text;
        file.close();
        cout << "Text file written successfully.\n";
    }
    else {
        cout << "Error opening text file!\n";
    }
}

void writeBinaryFile(string& text) {
    ofstream file("binaryfile.bin", ios::binary);
    if (file.is_open()) {
        file.write(text.c_str(), text.size());
        file.close();
        cout << "Binary file written successfully.\n";
    }
    else {
        cout << "Error opening binary file!\n";
    }
}

void readTextFile() {
    ifstream file("textfile.txt");
    if (file.is_open()) {
        string text;
        while (getline(file, text)) {
            cout << text << "\n";
        }
        file.close();
    }
    else {
        cout << "Error opening text file!\n";
    }
}

void readBinaryFile() {
    ifstream file("binaryfile.bin", ios::binary);
    if (file.is_open()) {
        string text;
        char ch;
        while (file.get(ch)) {
            text += ch;
        }
        cout << "Binary file content: " << text << "\n";
        file.close();
    }
    else {
        cout << "Error opening binary file!\n";
    }
}

int main() {
    int choice;
    string text;
    do {
        cout << "\nMenu:\n";
        cout << "1. Enter data\n";
        cout << "2. Write to text file\n";
        cout << "3. Write to binary file\n";
        cout << "4. Read from text file\n";
        cout << "5. Read from binary file\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: inputData(text); break;
        case 2: writeTextFile(text); break;
        case 3: writeBinaryFile(text); break;
        case 4: readTextFile(); break;
        case 5: readBinaryFile(); break;
        case 6: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}

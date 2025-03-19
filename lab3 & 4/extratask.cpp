#include <iostream>
#include <vector>

using namespace std;

void command1_1_1() { cout << "Executed command1_1_1" << endl; }
void command1_1_2() { cout << "Executed command1_1_2" << endl; }
void command1_2_1() { cout << "Executed command1_2_1" << endl; }
void command1_2_2() { cout << "Executed command1_2_2" << endl; }
void command2_1_1() { cout << "Executed command2_1_1" << endl; }
void command2_1_2() { cout << "Executed command2_1_2" << endl; }
void command2_2_1() { cout << "Executed command2_2_1" << endl; }
void command2_2_2() { cout << "Executed command2_2_2" << endl; }

void command1_1(vector<int>& keys) {
    cout << "Chosen command1_1" << endl;

    cout << "\n\n";
    for (int key : keys)
        cout << key << " ";
    cout << "\n\n";

    int keyLevel3;
    while (true) {
        cout << "1: command1_1_1\n2: command1_1_2\n0: Back\nEnter: ";
        cin >> keyLevel3;
        if (keyLevel3 == 0) return;

        keys[2] = keyLevel3;
        switch (keyLevel3) {
        case 1: command1_1_1(); break;
        case 2: command1_1_2(); break;
        default: cout << "Invalid command!" << endl;
        }
    }
}

void command1_2(vector<int>& keys) {
    cout << "Chosen command1_2" << endl;

    cout << "\n\n";
    for (int key : keys)
        cout << key << " ";
    cout << "\n\n";

    int keyLevel3;
    while (true) {
        cout << "1: command1_2_1\n2: command1_2_2\n0: Back\nEnter: ";
        cin >> keyLevel3;
        if (keyLevel3 == 0) return;

        keys[2] = keyLevel3;
        switch (keyLevel3) {
        case 1: command1_2_1(); break;
        case 2: command1_2_2(); break;
        default: cout << "Invalid command!" << endl;
        }
    }
}

void command2_1(vector<int>& keys) {
    cout << "Chosen command2_1" << endl;

    cout << "\n\n";
    for (int key : keys)
        cout << key << " ";
    cout << "\n\n";

    int keyLevel3;
    while (true) {
        cout << "1: command2_1_1\n2: command2_1_2\n0: Back\nEnter: ";
        cin >> keyLevel3;
        if (keyLevel3 == 0) return;

        keys[2] = keyLevel3;
        switch (keyLevel3) {
        case 1:
            command2_1_1();
            cout << "\n\n";
            for (int key : keys)
                cout << key << " ";
            cout << "\n\n";break;
        case 2:
            command2_1_2();
            cout << "\n\n";
            for (int key : keys)
                cout << key << " ";
            cout << "\n\n";break;
        default: cout << "Invalid command!" << endl;
        }
    }
}

void command2_2(vector<int>& keys) {
    cout << "Chosen command2_2" << endl;

    cout << "\n\n";
    for (int key : keys)
        cout << key << " ";
    cout << "\n\n";

    int keyLevel3;
    while (true) {
        cout << "1: command2_2_1\n2: command2_2_2\n0: Back\nEnter: ";
        cin >> keyLevel3;
        if (keyLevel3 == 0) return;

        keys[2] = keyLevel3;
        switch (keyLevel3) {
        case 1:
            command2_2_1();
            cout << "\n\n";
            for (int key : keys)
                cout << key << " ";
            cout << "\n\n";break;

        case 2:
            command2_2_2();
            cout << "\n\n";
            for (int key : keys)
                cout << key << " ";
            cout << "\n\n"; break;
        default: cout << "Invalid command!" << endl;
        }
    }
}

void command1(vector<int>& keys) {
    cout << "Chosen command1" << endl;

    cout << "\n\n";
    for (int key : keys)
        cout << key << " ";
    cout << "\n\n";

    int keyLevel2;
    while (true) {
        cout << "1: command1_1\n2: command1_2\n0: Back\nEnter: ";
        cin >> keyLevel2;
        if (keyLevel2 == 0) return;

        keys[1] = keyLevel2;
        switch (keyLevel2) {
        case 1: command1_1(keys); break;
        case 2: command1_2(keys); break;
        default: cout << "Invalid command!" << endl;
        }
    }
}

void command2(vector<int>& keys) {
    cout << "Chosen command2" << endl;

    cout << "\n\n";
    for (int key : keys)
        cout << key << " ";
    cout << "\n\n";

    int keyLevel2;
    while (true) {
        cout << "1: command2_1\n2: command2_2\n0: Back\nEnter: ";
        cin >> keyLevel2;
        if (keyLevel2 == 0) return;

        keys[1] = keyLevel2;
        switch (keyLevel2) {
        case 1: command2_1(keys); break;
        case 2: command2_2(keys); break;
        default: cout << "Invalid command!" << endl;
        }
    }
}

int main() {
    vector<int> keys = { 0, 0, 0 };

    int keyLevel1;
    while (true) {
        cout << "Main Menu:\n1: command1\n2: command2\n0: Exit\nEnter: ";
        cin >> keyLevel1;
        if (keyLevel1 == 0) break;

        keys[0] = keyLevel1;
        switch (keyLevel1) {
        case 1: command1(keys); break;
        case 2: command2(keys); break;
        default: cout << "Invalid command!" << endl;
        }
    }

    cout << "Exiting program..." << endl;
    return 0;
}
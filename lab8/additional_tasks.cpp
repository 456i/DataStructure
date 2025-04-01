#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для поиска всех вхождений подстроки
vector<int> findAllOccurrences(const string& pattern, const string& text) {
    vector<int> positions;
    size_t pos = text.find(pattern);
    while (pos != string::npos) {
        positions.push_back(pos);
        pos = text.find(pattern, pos + 1);  // Ищем следующее вхождение
    }
    return positions;
}

// Функция для поиска первого вхождения подстроки
int findFirstOccurrence(const string& pattern, const string& text) {
    return text.find(pattern);
}

// Функция для поиска самой длинной общей подстроки
string longestCommonSubstring(const string& str1, const string& str2) {
    int len1 = str1.length(), len2 = str2.length();
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
    int maxLength = 0, endIndex = 0;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i;
                }
            }
        }
    }
    return str1.substr(endIndex - maxLength, maxLength);  // Возвращаем найденную подстроку
}

void menu() {
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Find all occurrences of a substring\n";
        cout << "2. Find the first occurrence of a substring\n";
        cout << "3. Find the longest common substring\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();  // Игнорируем символ новой строки

        if (choice == 4) break;

        string str1, str2;
        cout << "Enter the first string: ";
        getline(cin, str1);  // Читаем первую строку
        cout << "Enter the second string: ";
        getline(cin, str2);  // Читаем вторую строку

        switch (choice) {
        case 1: {
            vector<int> positions = findAllOccurrences(str1, str2);
            if (positions.empty()) cout << "No occurrences found.\n";
            else {
                cout << "Occurrences found at positions: ";
                for (int pos : positions) cout << pos << " ";
                cout << endl;
            }
            break;
        }
        case 2: {
            int pos = findFirstOccurrence(str1, str2);
            if (pos == string::npos) cout << "Substring not found.\n";
            else cout << "First occurrence at position: " << pos << endl;
            break;
        }
        case 3: {
            string lcs = longestCommonSubstring(str1, str2);
            if (lcs.empty()) cout << "No common substring found.\n";
            else cout << "Longest common substring: " << lcs << endl;
            break;
        }
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}

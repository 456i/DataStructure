#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Разделение текста на предложения
vector<string> splitIntoSentences(const string& text) {
    vector<string> sentences;
    stringstream ss(text);
    string sentence;
    while (getline(ss, sentence, '.')) {
        if (!sentence.empty()) {
            sentences.push_back(sentence + '.');
        }
    }
    return sentences;
}

// Наивный поиск
bool naiveSearch(const string& text, const string& word) {
    size_t len = word.length();
    for (size_t i = 0; i <= text.length() - len; i++) {
        if (text.substr(i, len) == word) return true;
    }
    return false;
}

// Поиск с использованием string::find()
bool findSearch(const string& text, const string& word) {
    return text.find(word) != string::npos;
}

// Функция для построения префикс-функции КМП
vector<int> computeKMPTable(const string& pattern) {
    vector<int> table(pattern.length(), 0);
    int j = 0;
    for (size_t i = 1; i < pattern.length(); i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = table[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
            table[i] = j;
        }
    }
    return table;
}

// Алгоритм Кнута-Морриса-Пратта (КМП)
bool kmpSearch(const string& text, const string& pattern) {
    vector<int> table = computeKMPTable(pattern);
    int j = 0;
    for (size_t i = 0; i < text.length(); i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = table[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
            if (j == pattern.length()) return true;
        }
    }
    return false;
}

string highlightWord(const string& sentence, const string& word) {
    string result = sentence;
    size_t pos = result.find(word);
    while (pos != string::npos) {
        result.insert(pos, "|");
        result.insert(pos + word.length() + 1, "|");
        pos = result.find(word, pos + word.length() + 2);
    }
    return result;
}

void menu(const vector<string>& sentences) {
    while (true) {
        cout << "\nEnter a word to search (or 'exit' to quit): ";
        string word;
        cin >> word;
        if (word == "exit") break;

        cout << "\nChoose search algorithm:\n";
        cout << "1. Naive Search\n";
        cout << "2. string::find()\n";
        cout << "3. Knuth-Morris-Pratt (KMP)\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        cout << "\nResults:\n";
        int index = 1;
        for (const string& sentence : sentences) {
            bool found = false;
            switch (choice) {
            case 1: found = naiveSearch(sentence, word); break;
            case 2: found = findSearch(sentence, word); break;
            case 3: found = kmpSearch(sentence, word); break;
            default: cout << "Invalid choice.\n"; return;
            }
            if (found) {
                cout << index << ". " << highlightWord(sentence, word) << "\n";
            }
            index++;
        }
    }
}

int main() {
    ifstream file("input_text.txt");
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    vector<string> sentences = splitIntoSentences(text);

    menu(sentences);
    return 0;
}
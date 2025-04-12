#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

struct TextProcessor {
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
};

struct SearchAlgorithms {
    bool naiveSearch(const string& text, const string& word) {
        size_t len = word.length();
        for (size_t i = 0; i <= text.length() - len; i++) {
            if (text.substr(i, len) == word) return true;
        }
        return false;
    }

    bool findSearch(const string& text, const string& word) {
        return text.find(word) != string::npos;
    }

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


    bool boyerMooreSearch(const string& text, const string& word) {
        int m = word.length();
        int n = text.length();
        if (m > n) return false;

        bitset<256> badChar;
        int lastPos[256];
        fill(begin(lastPos), end(lastPos), -1);

        for (int i = 0; i < m; i++) {
            badChar.set((unsigned char)word[i]);
            lastPos[(unsigned char)word[i]] = i;
        }

        int shift = 0;
        while (shift <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && word[j] == text[shift + j]) {
                j--;
            }
            if (j < 0) {
                return true;
            }
            else {
                char bad = text[shift + j];
                shift += max(1, j - (badChar.test((unsigned char)bad) ? lastPos[(unsigned char)bad] : -1));
            }
        }
        return false;
    }
};


struct Menu {
    void run(const vector<string>& sentences) {
        SearchAlgorithms searcher;
        while (true) {
            cout << "\nEnter a word to search (or 'exit' to quit): ";
            string word;
            cin >> word;
            if (word == "exit") break;

            cout << "\nChoose search algorithm:\n";
            cout << "1. Naive Search\n";
            cout << "2. string::find()\n";
            cout << "3. Knuth-Morris-Pratt (KMP)\n";
            cout << "4. Boyer-Moore\n";
            cout << "Enter choice: ";
            int choice;
            cin >> choice;

            cout << "\nResults:\n";
            int index = 1;
            for (const string& sentence : sentences) {
                bool found = false;
                switch (choice) {
                case 1: found = searcher.naiveSearch(sentence, word); break;
                case 2: found = searcher.findSearch(sentence, word); break;
                case 3: found = searcher.kmpSearch(sentence, word); break;
                case 4: found = searcher.boyerMooreSearch(sentence, word); break;
                default: cout << "Invalid choice.\n"; return;
                }
                if (found) {
                    cout << index << ". " << sentence << "\n";
                }
                index++;
            }
        }
    }
};

int main() {
    ifstream file("input_text.txt");
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    TextProcessor processor;
    vector<string> sentences = processor.splitIntoSentences(text);

    Menu menu;
    menu.run(sentences);
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ifstream file("text.txt");
    if (!file.is_open()) {
        cout << "File not found!" << endl;
        return 1;
    }

    string allWords[500];
    int wordCount = 0;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string word;

        while (ss >> word) {
            if (word.length() > 0 && (word.back() == '.' || word.back() == ',')) {
                word.pop_back();
            }

            for (int k = 0; k < word.length(); k++) {
                word[k] = tolower(word[k]);
            }

            allWords[wordCount] = word;
            wordCount++;
        }
    }
    file.close();

    string longestWord = "";
    int maxRepeats = 0;

    for (int i = 0; i < wordCount; i++) {
        int currentCount = 0;

        for (int j = 0; j < wordCount; j++) {
            if (allWords[i] == allWords[j]) {
                currentCount++;
            }
        }

        if (currentCount > maxRepeats) {
            maxRepeats = currentCount;
            longestWord = allWords[i];
        }
    }

    ofstream result("output.txt");
    if (result.is_open()) {
        result << "Word: " << longestWord << endl;
        result << "Count: " << maxRepeats << endl;
        result.close();
        cout << "Done! Check output.txt" << endl;
    }
}
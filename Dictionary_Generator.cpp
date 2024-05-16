#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits> 
using namespace std;

void generateDictionaryFile() {
    std::ofstream file("dictionary.txt");
    if (file.is_open()) {
        file << "Welcome to the Dictionary Generator!" << endl;
        file.close();
        cout << "Dictionary file generated successfully.\n";
    } else {
        cout << "Unable to generate dictionary file.\n";
    }
}

void addWordMeaningPair() {
    string word, meaning;
    cout << "Enter the word: ";
    cin >> word;
    
    std::ifstream file("dictionary.txt");
    map<std::string, string> dictionary;
    
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find(":") != std::string::npos) {
                size_t pos = line.find(":");
                dictionary[line.substr(0, pos)] = line.substr(pos + 1);
            }
        }
        file.close();
    }
    
    cout << "Enter the meaning: ";
    cin.ignore();
    getline(cin, meaning);
    
    if (dictionary.find(word) != dictionary.end()) {
        dictionary[word] += " ; " + meaning;
    } else {
        dictionary[word] = meaning;
    }
    
    std::ofstream outFile("dictionary.txt");
    if (outFile.is_open()) {
        for (const auto& entry : dictionary) {
            outFile << entry.first << ":" << entry.second << endl;
        }
        outFile.close();
        cout << "Word-meaning pair added successfully.\n";
    } else {
        cout << "Unable to add word-meaning pair.\n";
    }
}

void searchWordMeaning() {
    string word;
    cout << "Enter the word to search: ";
    cin >> word;

    std::ifstream file("dictionary.txt");
    string line;
    bool found = false;

   if (file.is_open()) {
    while (getline(file, line)) {
        size_t pos = line.find(":");
        if (pos != std::string::npos && line.substr(0, pos) == word) {
            string allMeanings = line.substr(pos + 1);
            size_t startPos = 0;
            size_t endPos = allMeanings.find(" ; ");
            int meaningCount = 0;
            while (endPos != std::string::npos) {
                cout << "Meaning " << ++meaningCount << ": " << allMeanings.substr(startPos, endPos - startPos) << endl;
                startPos = endPos + 3;
                endPos = allMeanings.find(" ; ", startPos);
            }
            cout << "Meaning " << ++meaningCount << ": " << allMeanings.substr(startPos) << endl;
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Word not found in the dictionary.\n";
    }
} else {
    cout << "Dictionary file not found.\n";
}
}

void removeWordMeaningPair() {
    string word;
    cout << "Enter the word to remove: ";
    cin >> word;
    
    std::ifstream file("dictionary.txt");
    map<std::string, std::string> dictionary;
    
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find(":") != std::string::npos) {
                size_t pos = line.find(":");
                dictionary[line.substr(0, pos)] = line.substr(pos + 1);
            }
        }
        file.close();
        
        if (dictionary.erase(word) == 1) {
            std::ofstream outFile("dictionary.txt");
            if (outFile.is_open()) {
                for (const auto& entry : dictionary) {
                    outFile << entry.first << ":" << entry.second << endl;
                }
                outFile.close();
                cout << "Word-meaning pair removed successfully.\n";
            } else {
                cout << "Unable to remove word-meaning pair.\n";
            }
        } else {
            cout << "Word not found in the dictionary.\n";
        }
    } else {
        cout << "Dictionary file not found.\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n============================\n";
        cout << "  DICTIONARY GENERATOR MENU\n";
        cout << "============================\n";
        cout << "1. Generate Dictionary File\n";
        cout << "2. Add Word-Meaning Pair\n";
        cout << "3. Search Word Meaning\n";
        cout << "4. Remove Word-Meaning Pair\n";
        cout << "5. Exit\n";
        cout << "============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

   
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            cout << "\n*** Invalid input. Please enter a number. ***\n";
            continue; 
        }

        cout << "\n============================\n";

        switch (choice) {
            case 1:
                cout << "Generating Dictionary File...\n";
                generateDictionaryFile();
                break;
            case 2:
                cout << "Adding Word-Meaning Pair...\n";
                addWordMeaningPair();
                break;
            case 3:
                cout << "Searching Word Meaning...\n";
                searchWordMeaning();
                break;
            case 4:
                cout << "Removing Word-Meaning Pair...\n";
                removeWordMeaningPair();
                break;
            case 5:
                cout << "Exiting Dictionary Generator. Goodbye!\n";
                return 0;
            default:
                cout << "*** Invalid choice. Please try again. ***\n";
        }

        cout << "============================\n";

        if (choice == 5) {
            break; 
        }
    }

    return 0;
}
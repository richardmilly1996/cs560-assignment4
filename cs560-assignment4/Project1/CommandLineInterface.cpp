#include "CommandLineInterface.h"
#include "CipherManager.h"
#include <iostream>
#include <fstream>

using namespace std;

CommandLineInterface::CommandLineInterface() {
    tabs.push_back(new TextDocument());
    activeTab = 0;
}

CommandLineInterface::~CommandLineInterface() {
    for (auto tab : tabs) {
        delete tab;
    }
    tabs.clear();
}

void CommandLineInterface::printMenu() {

    cout << "Active Tab: " << activeTab + 1 << " / " << tabs.size() << "" << endl;
    cout << "1. Add Text Line\n";
    cout << "2. Add Checklist Line\n";
    cout << "3. Add Contact Line\n";
    cout << "4. Print Document\n";
    cout << "5. Save to File (Plain)\n";
    cout << "6. Load from File (Plain)\n";
    cout << "7. Encrypt and Save File\n";
    cout << "8. Load and Decrypt File\n";
    cout << "9. New Tab\n";
    cout << "10. Switch Tab\n";
    cout << "11. Close Current Tab\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

void CommandLineInterface::handleEncryptionDecryption(bool isEncrypt) {
    int cipherChoice = 0, numKey = 0;
    string strKey, inputPath, outputPath;

    cout << "Input file path: ";
    cin >> inputPath;
    cout << "Output file path: ";
    cin >> outputPath;

    cout << "Cipher (1 - Caesar, 2 - Vigenere, 3 - Atbash): ";
    cin >> cipherChoice;
    if (cipherChoice == 1) {
        cout << "Key (number): ";
        cin >> numKey;
    }
    else if (cipherChoice == 2) {
        cout << "Key (word): ";
        cin >> strKey;
    }

    ifstream inFile(inputPath);
    if (!inFile) {
        cout << "Cannot open input file.\n";
        return;
    }
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    string processedContent = CipherManager::processText(content, isEncrypt ? 1 : 2, cipherChoice, numKey, strKey);

    ofstream outFile(outputPath);
    if (outFile) {
        outFile << processedContent;
        outFile.close();
        cout << "Success! File saved to " << outputPath << endl;
    }
    else {
        cout << "Cannot create output file.\n";
    }
}

void CommandLineInterface::run() {
    int command;
    bool running = true;

    while (running) {
        printMenu();
        if (!(cin >> command)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();

        string temp1, temp2, temp3;
        bool tempBool;
        ofstream outFile;
        ifstream inFile;
        int tabChoice;

        switch (command) {
        case 1:
            cout << "Enter text: ";
            getline(cin, temp1);
            tabs[activeTab]->addLine(new TextLine(temp1));
            break;
        case 2:
            cout << "Enter task: ";
            getline(cin, temp1);
            cout << "Is it completed? (1 - Yes, 0 - No): ";
            cin >> tempBool;
            tabs[activeTab]->addLine(new ChecklistLine(temp1, tempBool));
            break;
        case 3:
            cout << "Enter Name: ";
            getline(cin, temp1);
            cout << "Enter Surname: ";
            getline(cin, temp2);
            cout << "Enter Email: ";
            getline(cin, temp3);
            tabs[activeTab]->addLine(new ContactLine(temp1, temp2, temp3));
            break;
        case 4:
            cout << "\nDocument in Tab " << activeTab + 1 << "\n";
            tabs[activeTab]->printAll();
            break;
        case 5:
            cout << "Enter filename to save: ";
            getline(cin, temp1);
            outFile.open(temp1);
            if (outFile) {
                outFile << tabs[activeTab]->serializeAll();
                outFile.close();
                cout << "Saved successfully.\n";
            }
            break;
        case 6:
            cout << "Enter filename to load: ";
            getline(cin, temp1);
            inFile.open(temp1);
            if (inFile) {
                string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
                tabs[activeTab]->deserializeAll(content);
                inFile.close();
                cout << "Loaded successfully.\n";
            }
            break;
        case 7:
            handleEncryptionDecryption(true);
            break;
        case 8:
            handleEncryptionDecryption(false);
            break;

        case 9:
            tabs.push_back(new TextDocument());
            activeTab = tabs.size() - 1; 
            cout << "New tab created, you are now in Tab " << activeTab + 1 << "\n";
            break;
        case 10:
            cout << "Enter tab number to switch to (1 - " << tabs.size() << "): ";
            cin >> tabChoice;
            if (tabChoice >= 1 && tabChoice <= tabs.size()) {
                activeTab = tabChoice - 1; 
                cout << "Switched to Tab " << activeTab + 1 << ".\n";
            }
            else {
                cout << "Invalid tab number\n";
            }
            break;
        case 11:
            if (tabs.size() == 1) {
                cout << "Cannot close the last tab\n";
            }
            else {
                delete tabs[activeTab]; 
                tabs.erase(tabs.begin() + activeTab); 
                activeTab = 0; 
                cout << "Tab closed, you are now in Tab 1\n";
            }
            break;
        case 0:
            running = false;
            break;
        default:
            cout << "Invalid command.\n";
            break;
        }
    }
}
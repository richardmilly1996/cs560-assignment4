#pragma once

#include "TextDocument.h"
#include <vector>

class CommandLineInterface {
    std::vector<TextDocument*> tabs;
    int activeTab;

    void printMenu();
    void handleEncryptionDecryption(bool isEncrypt);
public:
    CommandLineInterface();  
    ~CommandLineInterface(); 
    void run();
};


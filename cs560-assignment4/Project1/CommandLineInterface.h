#ifndef COMMANDLINEINTERFACE_H
#define COMMANDLINEINTERFACE_H

#include "TextDocument.h"

class CommandLineInterface {
    TextDocument doc;
    void printMenu();
    void handleEncryptionDecryption(bool isEncrypt);
public:
    void run();
};

#endif

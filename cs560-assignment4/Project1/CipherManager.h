#ifndef CIPHERMANAGER_H
#define CIPHERMANAGER_H

#include <string>

class CipherManager {
public:
    static std::string processText(const std::string& text, int isEncrypt, int cipherChoice, int numKey, const std::string& strKey);
};

#endif

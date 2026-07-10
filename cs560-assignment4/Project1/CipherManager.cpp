#include "CipherManager.h"
#include <windows.h>
#include <iostream>

using namespace std;

typedef void* cipher_t;

string CipherManager::processText(const string& text, int isEncrypt, int cipherChoice, int numKey, const string& strKey) {
    HMODULE lib = LoadLibraryA("Dll1.dll");
    if (!lib) {
        cout << "Error: Cannot load Dll1.dll" << endl;
        return text;
    }

    auto create_caesar = (cipher_t(*)(int))GetProcAddress(lib, "cipher_create_caesar");
    auto create_vigenere = (cipher_t(*)(const char*))GetProcAddress(lib, "cipher_create_vigenere");
    auto create_atbash = (cipher_t(*)())GetProcAddress(lib, "cipher_create_atbash");
    auto cipher_encrypt = (char* (*)(cipher_t, const char*))GetProcAddress(lib, "cipher_encrypt");
    auto cipher_decrypt = (char* (*)(cipher_t, const char*))GetProcAddress(lib, "cipher_decrypt");
    auto cipher_destroy = (void(*)(cipher_t))GetProcAddress(lib, "cipher_destroy");
    auto cipher_free = (void(*)(char*))GetProcAddress(lib, "cipher_free");

    cipher_t cipher = nullptr;
    if (cipherChoice == 1) cipher = create_caesar(numKey);
    else if (cipherChoice == 2) cipher = create_vigenere(strKey.c_str());
    else if (cipherChoice == 3) cipher = create_atbash();

    if (!cipher) {
        FreeLibrary(lib);
        return text;
    }

    char* res = nullptr;
    if (isEncrypt == 1) {
        res = cipher_encrypt(cipher, text.c_str());
    }
    else {
        res = cipher_decrypt(cipher, text.c_str());
    }

    string resultStr = text;
    if (res) {
        resultStr = res;
        cipher_free(res);
    }

    cipher_destroy(cipher);
    FreeLibrary(lib); 
    return resultStr;
}
#include "TextDocument.h"
#include <sstream>
#include <iostream>

using namespace std;

TextDocument::~TextDocument() {
    clear();
}

void TextDocument::addLine(Line* line) {
    lines.push_back(line);
}

void TextDocument::clear() {
    for (auto line : lines) {
        delete line;
    }
    lines.clear();
}

void TextDocument::printAll() const {
    if (lines.empty()) {
        cout << "Document is empty.\n";
        return;
    }
    for (auto line : lines) {
        line->print();
    }
}

string TextDocument::serializeAll() const {
    string res;
    for (auto line : lines) {
        res += line->serialize() + "\n";
    }
    return res;
}

void TextDocument::deserializeAll(const string& data) {
    clear();
    istringstream stream(data);
    string lineStr;

    while (getline(stream, lineStr)) {
        if (lineStr.empty()) continue;

        if (lineStr.substr(0, 4) == "TXT|") {
            addLine(new TextLine(lineStr.substr(4)));
        }
        else if (lineStr.substr(0, 4) == "CHK|") {
            bool checked = (lineStr[4] == '1');
            addLine(new ChecklistLine(lineStr.substr(6), checked));
        }
        else if (lineStr.substr(0, 4) == "CON|") {
            size_t pos1 = 4;
            size_t pos2 = lineStr.find('|', pos1);
            size_t pos3 = lineStr.find('|', pos2 + 1);

            if (pos2 != string::npos && pos3 != string::npos) {
                string n = lineStr.substr(pos1, pos2 - pos1);
                string s = lineStr.substr(pos2 + 1, pos3 - pos2 - 1);
                string e = lineStr.substr(pos3 + 1);
                addLine(new ContactLine(n, s, e));
            }
        }
    }
}
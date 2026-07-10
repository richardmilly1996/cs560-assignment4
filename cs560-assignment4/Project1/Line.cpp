#include "Line.h"
#include <iostream>

using namespace std;

TextLine::TextLine(const string& t) : text(t) {}

void TextLine::print() const {
    cout << "Text: " << text << endl;
}

string TextLine::serialize() const {
    return "TXT|" + text;
}

ChecklistLine::ChecklistLine(const string& i, bool c) : item(i), checked(c) {}

void ChecklistLine::print() const {
    cout << "[ " << (checked ? "x" : " ") << " ] " << item << endl;
}

string ChecklistLine::serialize() const {
    return "CHK|" + to_string(checked) + "|" + item;
}

ContactLine::ContactLine(const string& n, const string& s, const string& e)
    : name(n), surname(s), email(e) {
}

void ContactLine::print() const {
    cout << "Contact - " << name << " " << surname << ", Email: " << email << endl;
}

string ContactLine::serialize() const {
    return "CON|" + name + "|" + surname + "|" + email;
}
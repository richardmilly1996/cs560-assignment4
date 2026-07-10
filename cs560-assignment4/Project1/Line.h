#ifndef LINE_H
#define LINE_H

#include <string>

class Line {
public:
    virtual void print() const = 0;
    virtual std::string serialize() const = 0; 
    virtual ~Line() = default;
};

class TextLine : public Line {
    std::string text;
public:
    TextLine(const std::string& t);
    void print() const override;
    std::string serialize() const override;
};

class ChecklistLine : public Line {
    std::string item;
    bool checked;
public:
    ChecklistLine(const std::string& i, bool c);
    void print() const override;
    std::string serialize() const override;
};

class ContactLine : public Line {
    std::string name, surname, email;
public:
    ContactLine(const std::string& n, const std::string& s, const std::string& e);
    void print() const override;
    std::string serialize() const override;
};

#endif
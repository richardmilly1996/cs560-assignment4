#pragma once

#include <vector>
#include <string>
#include "Line.h"

class TextDocument {
    std::vector<Line*> lines;
public:
    ~TextDocument();
    void addLine(Line* line);
    void clear();
    void printAll() const;
    std::string serializeAll() const;
    void deserializeAll(const std::string& data);
};


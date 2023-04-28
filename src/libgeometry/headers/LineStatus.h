#pragma once

#include <string>
#include <iostream>

enum LineStatus {
    fine,
    nameException,
    bracketsException,
    inBracketsIncorrectException
};

LineStatus checkLine(std::string line);

void printExceptionMessage(LineStatus exception, int lineIndex);
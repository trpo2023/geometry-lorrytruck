#include "headers/LineStatus.h"

LineStatus checkLine(std::string line)
{
    size_t namepos = line.find("circle");
    if (namepos != 0)
        return nameException;
        
    size_t leftb =  line.find("(");
    size_t rightb = line.rfind(")");

    if (leftb == std::string::npos) return bracketsException;
    if (rightb == std::string::npos) return bracketsException;
    if (leftb >= rightb) return bracketsException;

    size_t leftSpace = line.find(" ");
    size_t rightSpace = line.rfind(" ");
    size_t zap = line.find(",");

    if (leftSpace == std::string::npos) return inBracketsIncorrectException;
    if (rightSpace == std::string::npos) return inBracketsIncorrectException;
    if (zap == std::string::npos) return inBracketsIncorrectException;
    
    size_t endSb = 0;

    stof(line.substr(leftb+1, leftSpace-leftb), &endSb);
    if (endSb != leftSpace-leftb-1) return inBracketsIncorrectException;

    stof(line.substr(leftSpace+1, zap-leftSpace), &endSb);
    if (endSb != zap-leftSpace-1) return inBracketsIncorrectException;

    stof(line.substr(rightSpace+1, rightb-rightSpace), &endSb);
    if (endSb != rightb-rightSpace-1) return inBracketsIncorrectException;


    return fine;
}

void printExceptionMessage(LineStatus exception, int lineIndex)
{
    std::cout << "Error at column " << lineIndex << ": ";
    switch (exception)
    {
    case nameException:
        std::cout << "expected 'circle'";
        break;

    case bracketsException:
        std::cout << "expected '(...)'";
        break;
    case inBracketsIncorrectException:
        std::cout << "expected '({float x} {float y}, {float radius})'";
        break;
    
    default:
        std::cout << "unknown error ocurred";
        break;
    }
    std::cout << std::endl;
}

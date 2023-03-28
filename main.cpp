#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <math.h>

using namespace std;

enum LineStatus {
    fine,
    nameException,
    bracketsException,
    inBracketsIncorrectException
};

struct Vector2
{
    float x;
    float y;
};

struct Circle
{
    int id;
    Vector2 position;
    float radius;
    string initLine;
};


// bool checkFloatNuber(string strNumber){
//     size_t point = strNumber.find(".");
//     size_t pointR = strNumber.rfind(".");

//     if (point == string::npos) return false;
//     if (point != pointR) return false;
//     if (point == 0 || point == strNumber.length()-1) return false;

//     return true;
// }

LineStatus checkLine(string line){
    size_t namepos = line.find("circle");
    if (namepos != 0)
        return nameException;

    size_t leftb =  line.find("(");
    size_t rightb = line.rfind(")");

    if (leftb == string::npos) return bracketsException;
    if (rightb == string::npos) return bracketsException;
    if (leftb >= rightb) return bracketsException;

    size_t leftSpace = line.find(" ");
    size_t rightSpace = line.rfind(" ");
    size_t zap = line.find(",");

    if (leftSpace == string::npos) return inBracketsIncorrectException;
    if (rightSpace == string::npos) return inBracketsIncorrectException;
    if (zap == string::npos) return inBracketsIncorrectException;

    size_t endSb = 0;

    stof(line.substr(leftb+1, leftSpace-leftb), &endSb);
    if (endSb != leftSpace-leftb-1) return inBracketsIncorrectException;

    stof(line.substr(leftSpace+1, zap-leftSpace), &endSb);
    if (endSb != zap-leftSpace-1) return inBracketsIncorrectException;

    stof(line.substr(rightSpace+1, rightb-rightSpace), &endSb);
    if (endSb != rightb-rightSpace-1) return inBracketsIncorrectException;


    return fine;
}

void printExceptionMessage(LineStatus exception, int lineIndex){
    cout << "Error at column " << lineIndex << ": ";
    switch (exception)
    {
    case nameException:
        cout << "expected 'circle'";
        break;

    case bracketsException:
        cout << "expected '(...)'";
        break;
    case inBracketsIncorrectException:
        cout << "expected '({float x} {float y}, {float radius})'";
        break;

    default:
        cout << "unknown error ocurred";
        break;
    }
    cout << endl;
}

Vector2 getPosition(string line){
    size_t leftb =  line.find("(");
    size_t leftSpace = line.find(" ");
    size_t zap = line.find(",");

    Vector2 position;
    position.x = stof(line.substr(leftb+1, leftSpace-leftb-1));
    position.y = stof(line.substr(leftSpace+1, leftSpace-zap-1));
    return position;
}

float getRadius(string line){
    size_t rightb = line.rfind(")");
    size_t rightSpace = line.rfind(" ");

    float r = stof(line.substr(rightSpace+1, rightb-rightSpace-1));
    return r;
}

void printFigureData(Circle c){
    cout << c.id << ". ";
    cout << c.initLine << endl;
    cout << "\tperimetr: " << 3.14*c.radius*2 << endl;
    cout << "\tarea: " << 3.14*c.radius*c.radius << endl;
}

void printIntersects(Circle f, list<Circle> figures) {
    bool haveIntersects = false;
    for(Circle ff : figures){
        if(ff.id == f.id) continue;
        float radiusesSum = f.radius + ff.radius;
        float distantion = sqrt(
            pow(abs(f.position.x-ff.position.x),2) +
            pow(abs(f.position.y-ff.position.y),2)
        );

        if (radiusesSum >= distantion) {
            cout << "\t  " << ff.id << ". circle" << endl;
            haveIntersects = true;
        }
    }
    if (!haveIntersects)
        cout << "\t  no intersect" << endl;
    cout << endl;
}

void printCirclesData(list<Circle> figures){
    for(Circle f : figures){
        printFigureData(f);
        cout << "\tintersects:" << endl;
        printIntersects(f, figures);
    }

}

int main()
{
    list<Circle> figures;

    ifstream file("input.wkt");
    string line;

    int currentFigureId = 0;
    bool incorrectInput = false;
    while (getline(file, line))
    {

LineStatus errorCode = checkLine(line);
        if (errorCode != fine){
            printExceptionMessage(errorCode, currentFigureId);
            incorrectInput = true;
            break;

        } else {
            Circle figure;
            figure.id = currentFigureId;
            figure.position = getPosition(line);
            figure.radius = getRadius(line);
            figure.initLine = line;

            figures.push_back(figure);
            currentFigureId++;
        }
    }

    if (!incorrectInput)
        printCirclesData(figures);
}

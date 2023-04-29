#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <math.h>

#include <Circle.h>
#include <LineStatus.h>
#include <Vector2.h>

using namespace std;

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
            figure.position = getCirclePosition(line);
            figure.radius = getCircleRadius(line);
            figure.initLine = line;

            figures.push_back(figure);
            currentFigureId++;
        }
    }
    if (!incorrectInput)
        printCirclesData(figures);
}

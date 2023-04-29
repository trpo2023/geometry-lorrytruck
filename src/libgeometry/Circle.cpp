#include "headers/Circle.h"

Vector2 getCirclePosition(std::string line)
{
    size_t leftb =  line.find("(");
    size_t leftSpace = line.find(" ");
    size_t zap = line.find(",");

    Vector2 position;
    position.x = stof(line.substr(leftb+1, leftSpace-leftb-1));
    position.y = stof(line.substr(leftSpace+1, leftSpace-zap-1));
    return position;
}

float getCircleRadius(std::string line){
    size_t rightb = line.rfind(")");
    size_t rightSpace = line.rfind(" ");

    float r = stof(line.substr(rightSpace+1, rightb-rightSpace-1));
    return r;
}

void printCircleData(Circle c){
    std::cout << c.id << ". ";
    std::cout << c.initLine << std::endl;
    std::cout << "\tperimetr: " << 3.14*c.radius*2 << std::endl;
    std::cout << "\tarea: " << 3.14*c.radius*c.radius << std::endl;
}

void printCirclesIntersects(Circle f, std::list<Circle> figures) {
    bool haveIntersects = false;
    for(Circle ff : figures){
        if(ff.id == f.id) continue;
        float radiusesSum = f.radius + ff.radius;
        float distantion = sqrt(
            pow(abs(f.position.x-ff.position.x),2) +
            pow(abs(f.position.y-ff.position.y),2)
        );

        if (radiusesSum >= distantion) {
            std::cout << "\t  " << ff.id << ". circle" << std::endl;
            haveIntersects = true;
        }
    }
    if (!haveIntersects)
        std::cout << "\t  no intersect" << std::endl;
    std::cout << std::endl;
}

void printCirclesData(std::list<Circle> figures){
    for(Circle f : figures){
        printCircleData(f);
        std::cout << "\tintersects:" << std::endl;
        printCirclesIntersects(f, figures);
    }
        
}
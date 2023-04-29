#pragma once

#include <string>
#include <iostream>
#include <list>
#include <cmath>

#include "Vector2.h"

struct Circle
{
    int id;
    Vector2 position;
    float radius;
    std::string initLine;
};

// todo test
Vector2 getCirclePosition(std::string line);

// todo test
float getCircleRadius(std::string line);

void printCircleData(Circle c);

void printCirclesIntersects(Circle f, std::list<Circle> figures);

void printCirclesData(std::list<Circle> figures);
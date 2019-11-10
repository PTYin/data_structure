//
// Created by Peter on 2019/11/5.
//

#ifndef DATA_STRUCTURE_CORE_H
#define DATA_STRUCTURE_CORE_H

#include <GL/glut.h>
#include <vector>
#include <ctime>
#include <cmath>
#include "../../other/quick_sort.hpp"

//--------------------------------------------------------------
// Toolkit
struct Point
{
    int x, y;

    Point(int x_, int y_) : x(x_), y(y_)
    {}

    bool operator==(const Point &o)
    {
        return x == o.x && y == o.y;
    }
};

static bool valid(Point p1, Point p2, Point p3)
{
    return (p2.x-p1.x)*(p3.y-p2.y)-(p3.x-p2.x)*(p2.y-p1.y) <= 0;
}

static void swap(Point &e1, Point &e2)
{
    Point temp = e1;
    e1 = e2;
    e2 = temp;
}

//--------------------------------------------------------------

//--------------------------------------------------------------
// Step
void init();

void randomGenerate(int);

void GrahamsScan();
//--------------------------------------------------------------

//--------------------------------------------------------------
// Draw
void drawPoints();
//--------------------------------------------------------------

//--------------------------------------------------------------
// GL Action
void renderScene();

void mouse(int button, int state, int mx, int my);

void keyboard(unsigned char key, int x, int y);

int process(int argc, char** argv);
//--------------------------------------------------------------

#endif //DATA_STRUCTURE_CORE_H

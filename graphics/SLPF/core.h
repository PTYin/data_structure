//
// Created by Peter on 2019/10/11.
//

#ifndef SLPF_CORE_H
#define SLPF_CORE_H

#include "toolkit.hpp"
#include <vector>
#include <map>
#include <GL/glut.h>
#include <tree/AVLTree.hpp>
#include <tree/Treap.hpp>


//--------------------------------------------------------------
// Step
void initEdgeTable();

void scanLineFill();
//--------------------------------------------------------------

//--------------------------------------------------------------
// Draw
void drawPoints();

void drawEdges();

void fill(double left_f, double right_f, int y);
//--------------------------------------------------------------

//--------------------------------------------------------------
// GL Action
void renderScene();

void mouse(int button, int state, int mx, int my);

void keyboard(unsigned char key, int x, int y);

void process(int argc, char **argv);
//--------------------------------------------------------------

#endif //SLPF_CORE_H

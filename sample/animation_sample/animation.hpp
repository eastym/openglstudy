#pragma once

#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

#include <cstdint>

// #include "../fps/fps.hpp"

// 立方体
struct Solid
{
private:
    std::vector<std::vector<GLfloat>> vertex;
    std::vector<std::vector<GLfloat>> normal;
    std::vector<std::vector<GLfloat>> linesEdge;
    std::vector<std::vector<GLfloat>> quadEdge;
    std::vector<std::vector<GLfloat>> quadColor;

    std::vector<GLdouble> rotate;

    std::vector<GLfloat> pos = {0.5, 0.5, 0.5};

public:
    Solid();
    void setVertex(std::vector<std::vector<GLfloat>> _vertex);
    void setVertex(std::vector<GLfloat> center, GLfloat width, GLfloat height, GLfloat depth);
    std::vector<std::vector<GLfloat>> getVertex();
    std::vector<std::vector<GLfloat>> getNormal();
    std::vector<std::vector<GLfloat>> getLinesEdge();
    std::vector<std::vector<GLfloat>> getQuadEdge();
    std::vector<std::vector<GLfloat>> getQuadColor();

    void doRotate(double x, double y, double z);
};

// first
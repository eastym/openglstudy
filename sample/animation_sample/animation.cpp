#include "animation.hpp"

Solid::Solid()
{
    rotate = {0, 0, 0};
    linesEdge = {
        {0, 1},
        {1, 2},
        {2, 3},
        {0, 3},
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7},
        {4, 5},
        {5, 6},
        {6, 7},
        {4, 7}};

    quadEdge = {
        {0, 1, 2, 3},
        {0, 4, 5, 1},
        {1, 5, 6, 2},
        {2, 6, 7, 3},
        {3, 7, 4, 0},
        {4, 7, 6, 5}};

    quadColor = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 1}};
}

// x:width y:height z:depth
void Solid::setVertex(std::vector<GLfloat> center, GLfloat width, GLfloat height, GLfloat depth)
{
    Solid::vertex = {{center.at(0) - width / 2, center.at(1) - height / 2, center.at(2) - depth / 2},  // 0
                     {center.at(0) + width / 2, center.at(1) - height / 2, center.at(2) - depth / 2},  // 1
                     {center.at(0) + width / 2, center.at(1) - height / 2, center.at(2) + depth / 2},  // 2
                     {center.at(0) - width / 2, center.at(1) - height / 2, center.at(2) + depth / 2},  // 3
                     {center.at(0) - width / 2, center.at(1) + height / 2, center.at(2) - depth / 2},  // 4
                     {center.at(0) + width / 2, center.at(1) + height / 2, center.at(2) - depth / 2},  // 5
                     {center.at(0) + width / 2, center.at(1) + height / 2, center.at(2) + depth / 2},  // 6
                     {center.at(0) - width / 2, center.at(1) + height / 2, center.at(2) + depth / 2}}; // 7
}

std::vector<std::vector<GLfloat>> Solid::getVertex()
{
    return Solid::vertex;
}

std::vector<std::vector<GLfloat>> Solid::getNormal()
{
    for (int i = 0; i < quadEdge.size(); i++)
    {
        normal.push_back({ (vertex.at(quadEdge.at(i).at(0)).at(0) +  vertex.at(quadEdge.at(i).at(1)).at(0) +  vertex.at(quadEdge.at(i).at(2)).at(0) +  vertex.at(quadEdge.at(i).at(3)).at(0))/4 - 0.5,
        (vertex.at(quadEdge.at(i).at(0)).at(1) +  vertex.at(quadEdge.at(i).at(1)).at(1) +  vertex.at(quadEdge.at(i).at(2)).at(1) +  vertex.at(quadEdge.at(i).at(3)).at(1))/4 - 0.5,
        (vertex.at(quadEdge.at(i).at(0)).at(2) +  vertex.at(quadEdge.at(i).at(1)).at(2) +  vertex.at(quadEdge.at(i).at(2)).at(2) +  vertex.at(quadEdge.at(i).at(3)).at(2))/4 - 0.5 });
    }

    for(auto &f:normal){
        for(auto &e:f) e =/ std::accumulate(f.begin(),f.end(),0);
    } 
    return normal;
}

std::vector<std::vector<GLfloat>> Solid::getLinesEdge()
{
    return Solid::linesEdge;
}

std::vector<std::vector<GLfloat>> Solid::getQuadEdge()
{
    return Solid::quadEdge;
}

std::vector<std::vector<GLfloat>> Solid::getQuadColor()
{
    return Solid::quadColor;
}

void Solid::setVertex(std::vector<std::vector<GLfloat>> _vertex)
{
    Solid::vertex = _vertex;
}

void Solid::doRotate(double x, double y, double z)
{
    if (x != 0)
    {
        for (int i = 0; i < 0;)
        {
        }
    }
    this->rotate[0] += x;
    this->rotate[1] += y;
    this->rotate[2] += z;
}

#include "quad.h"

Quad::Quad(GLfloat size) 
{
    GLfloat side = size / 2.0f;

    std::vector<GLfloat> points = 
    {
       -side, -side, side, side, -side, side, side,  side, side,  -side,  side, side
    };

    std::vector<GLfloat> normals = 
    {
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    std::vector<GLfloat> texCoords = 
    {
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    std::vector<GLuint> indices =
    {
        0,1,2,0,2,3
    };

    InitBuffers(&indices, &points, &normals, &texCoords);
}
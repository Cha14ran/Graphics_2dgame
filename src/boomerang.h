#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H
class Boomerang{    
public:
    Boomerang(){};
    Boomerang(float x,float y,color_t color);
    glm::vec3 position;
    float rotation;
    int start;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void direction(float x,float y);
private:
    VAO *object;
};
#endif
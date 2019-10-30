#include "main.h"
#ifndef SEMICIRCLE_H
#define SEMICIRCLE_H

class SemiCircle{
public:
    SemiCircle(){};
    SemiCircle(float x,float y,float rotation,color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    int entered; 
    float degree;
    void draw(glm::mat4 VP);
    void set_position(float x,float y);
private:
    VAO *object;
};

#endif 
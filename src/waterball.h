#include "main.h"
#ifndef WATERBALL_H
#define WARERBALL_H

class WaterBall{
public:
    WaterBall(){};
    WaterBall(float x,float y,float radius,color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x,float y);
private:
    VAO *object;
};

#endif 
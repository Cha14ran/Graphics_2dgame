#include "main.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H


class Rectangle {
public:
    Rectangle() {}
    Rectangle(float x, float y, float width, float height, color_t color,float rotation=0.0f);
    glm::vec3 position;
       float rotation;
           float height,width,speed;
           float timeoffalling;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    // void tick();
private:
    VAO *object;
};

#endif // RECTANGLE_H

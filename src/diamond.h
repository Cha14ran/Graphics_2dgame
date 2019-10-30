#include "main.h"

#ifndef DIAMOND_H
#define DIAMOND_H


class Diamond {
public:
    Diamond(){};
    Diamond(float x, float y,color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float rotation;
    int visible;
private:
    VAO *object;
};

#endif // BALL_H

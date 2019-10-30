#include "main.h"
#ifndef COIN_H
#define COIN_H

class Coins{
public:
    Coins(){};
    Coins(float x,float y,color_t color);
    glm::vec3 position;
    float radius;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x,float y);
    // void tick();
private:
    VAO *object;

};


#endif //COIN_H

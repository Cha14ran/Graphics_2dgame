// #include "main.h"
#include "coins.h"
#include "ground.h"
#ifndef ENEMY_H
#define ENEMY_H

class Enemy1{
public:
    Enemy1(){};
    Enemy1(glm::vec3 position_c1,glm::vec3 position_c2,int visible);
    glm::vec3 position_c1;
    glm::vec3 position_c2;
    Rectangle g1;
    Coins c1,c2;
    float distance;
    float rotation;
    float slope;
    int  visible;
    glm::vec3 topright,bottomleft;
    float a11,b12,c13;
    float a21,b22,c23;
    float a31,b32,c33;
    float a41,b42,c43;
    void draw(glm::mat4 VP,int visible);
    int checkcollision(glm::vec3 playerpos);
};

#endif 
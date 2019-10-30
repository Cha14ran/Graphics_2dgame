#include "main.h"
#include "convert.h"
CircleObj convertcircle(Coins one){
    CircleObj temp = {one.position, one.radius};
    return temp;
}

RectangleObj convertrectangle(Rectangle one) {
    glm::vec2 position1=glm::vec2(one.position.x,one.position.y);
    glm::vec2 position2=glm::vec2(one.width,one.height);
    RectangleObj temp={position1,position2};
    return temp;
}
#include "main.h"
#include "enemy.h"
#include "coins.h"
#include "ground.h"
#include<cmath>

Enemy1::Enemy1(glm::vec3 position_c1,glm::vec3 position_c2,int visible){
    this->c1=Coins(position_c1.x,position_c1.y,COLOR_GREY);
    this->c2=Coins(position_c2.x,position_c2.y,COLOR_GREY);
    this->position_c1=position_c1;
    this->position_c2=position_c2;
    this->visible=visible;
    float x=(position_c2.x-position_c1.x)*(position_c2.x-position_c1.x);
    float y=(position_c2.y-position_c1.y)*(position_c2.y-position_c1.y);
    distance=sqrtf(x+y);
    float rotation=(float)atan((double)(position_c2.y-position_c1.y)/(position_c2.x-position_c1.x));
    float slope=(position_c2.y-position_c1.y)/(position_c2.x-position_c1.x);
    this->slope=slope;
    this->rotation=(180/3.14159)*rotation;
    this->g1=Rectangle((position_c1.x+position_c2.x)/2,(position_c1.y+position_c2.y)/2,distance,0.2,COLOR_RED,this->rotation); 
    glm::vec3 topleft=glm::vec3(static_cast<float>(this->position_c1.x+0.1f * cos(this->rotation-M_PI/2.0f)),static_cast<float>(this->position_c1.y+0.1f*sin(this->rotation - M_PI/2.0f)),0.0f); 
    glm::vec3 bottomright=glm::vec3(static_cast<float>(this->position_c2.x-0.1f * cos(this->rotation-M_PI/2.0f)),static_cast<float>(this->position_c2.y-0.1f*sin(this->rotation - M_PI/2.0f)),0.0f);
    if(this->slope==0){
        printf("slope is zero\n");
        this->a11=0;
        this->b12=1;
        this->c13=-topleft.y;

        this->a21=1;
        this->b22=0;
        this->c23=-topleft.x;

        this->a31=0;
        this->b32=1;
        this->c33=-bottomright.y;

        this->a41=1;
        this->b42=0;
        this->c43=-bottomright.x;
    }
    else if(isinf(this->slope)){
        this->a11=1;
        this->b12=0;
        this->c13=-topleft.x;

        this->a21=0;
        this->b22=1;
        this->c23=-topleft.y;

        this->a31=1;
        this->b32=0;
        this->c33=-bottomright.x;

        this->a41=0;
        this->b42=1;
        this->c43=-bottomright.y;
    }
    else{
        this->a11=this->slope;
        this->b12=-1;
        this->c13=topleft.y-(this->slope)*topleft.x;

        this->a21=-1.0f/this->slope;
        this->b22=-1;
        this->c23=topleft.y-(-1.0f/this->slope)*topleft.x;

        this->a31=this->slope;
        this->b32=-1;
        this->c33=bottomright.y-(this->slope)*bottomright.x;

        this->a41=-1.0f/this->slope;
        this->b42=-1;
        this->c43=bottomright.y-(-1.0f/this->slope)*bottomright.x;
        //     printf("position_c1.x is %f\n",position_c1.x);
        //     printf("positon_c1.y is %f\n",position_c1.y);
        //     printf("topleftx is %f\n",topleft.x);
        //     printf("toplefty is %f\n",topleft.y);
        // printf("a11,b12,c13 is%f,%f,%f\n",a11,b12,c13);
        // printf("a21,b22,c23 is%f,%f,%f\n",a21,b22,c23);
        // printf("a31,b32,c33 is%f,%f,%f\n",a31,b32,c33);
        // printf("a41,b42,c43 is%f,%f,%f\n",a41,b42,c43);
    }
}

void Enemy1::draw(glm::mat4 VP,int visible){
    this->c1.draw(VP);
    this->c2.draw(VP);
    if(visible==1){
        this->g1.draw(VP);
    }
}

int Enemy1::checkcollision(glm::vec3 playerpos){
    float check1;
    float check2;
    float check3;    
    float check4;
    check1=this->a11*playerpos.x+this->b12*playerpos.y+this->c13;
    check2=this->a21*playerpos.x+this->b22*playerpos.y+this->c23;
    check3=this->a31*playerpos.x+this->b32*playerpos.y+this->c33;
    check4=this->a41*playerpos.x+this->b42*playerpos.y+this->c43;
    // printf("klawhef\n");
    if(check1*check3<0&&check2*check4<0){
        return 1;
    }
    else{
        return 0;
    }
}
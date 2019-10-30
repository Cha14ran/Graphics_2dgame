#include "main.h"
#include "waterball.h"
WaterBall::WaterBall(float x, float y,float radius,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->radius=radius;
    // printf("akjgsdf:%f\n",radius);
    float n=360;
    float r=this->radius;
    float theta=2*3.14159/360;
    GLfloat vertex_buffer_data[360*9];
    for(int i=0;i<n;i++){
        float  anglebefore =theta*i;
        float angle =anglebefore+theta;
        float x=r*cos(angle);
        float y=r*sin(angle);
        float z=0.0f;

        float x1=r*cos(anglebefore);
        float y1=r*sin(anglebefore);
        float z1=0.0f;

        float x2=0.0f;
        float y2=0.0f;
        float z2=0.0f;
        vertex_buffer_data[9*i]=x2;
        vertex_buffer_data[9*i+1]=y2;
        vertex_buffer_data[9*i+2]=z2;
        
        vertex_buffer_data[9*i+3]=x1;
        vertex_buffer_data[9*i+4]=y1;
        vertex_buffer_data[9*i+5]=z1;

        vertex_buffer_data[9*i+6]=x;
        vertex_buffer_data[9*i+7]=y;
        vertex_buffer_data[9*i+8]=z;
    }
    this->object =create3DObject(GL_TRIANGLES,360*3,vertex_buffer_data,color,GL_FILL);
 
}


void WaterBall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object); 
    // draw3DObject(this->player);
}

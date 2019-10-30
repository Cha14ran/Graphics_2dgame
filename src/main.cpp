#include "main.h"
#include "timer.h"
// #include "ball.h"
#include "ground.h"
#include "coins.h"
#include "enemy.h"
#include "convert.h"
#include "boomerang.h"
#include "diamond.h"
#include "semicircle.h"
#include "waterball.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Rectangle Player,ground;
// Coins c[5][5];
vector<Coins> cn;
vector<Enemy1> e1,e2,e3;
vector<WaterBall> waterballon;
Boomerang Boom;
Diamond daya;
SemiCircle magnet;
WaterBall smallcircle;
int score,Health;
char title[1000];
int temp=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float x;
// int gameplay=1;


Timer t60(1.0 / 60);
// float speed=0.01;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ground.draw(VP);
    for(int k=0;k<cn.size();k++){
        cn[k].draw(VP);
    }
    for(int m=0;m<e1.size();m++){
            e1[m].draw(VP,e1[m].visible);
    }
    for(int l=0;l<e2.size();l++){
        e2[l].draw(VP,e2[l].visible);
    }
    // printf("screen_center_x is %f\n",screen_center_x);
    if(e3[0].position_c1.x-screen_center_x<2.0){
        for(int k=0;k<e3.size();k++){   
            e3[k].draw(VP,1);
        }
    }
    Boom.draw(VP);
    if(daya.visible==1){
        daya.draw(VP);
    }
    magnet.draw(VP);
    for(int l=0;l<waterballon.size();l++){
        waterballon[l].draw(VP);
    }
    // smallcircle1.draw(VP);
    smallcircle.draw(VP);
    Player.draw(VP);
    // magnet.draw(VP);
}

void tick_input(GLFWwindow *window) {
  int up = glfwGetKey(window, GLFW_KEY_UP);
  int left  = glfwGetKey(window, GLFW_KEY_LEFT);
  int right = glfwGetKey(window, GLFW_KEY_RIGHT);
  int down = glfwGetKey(window, GLFW_KEY_DOWN);
//   int space =glfwGetKey(window,S)
  if(left){
      Player.position.x-=0.05f;
      screen_center_x-=0.05f;
      reset_screen();
  }
  else if(right){
      Player.position.x+=0.05f;
      screen_center_x+=0.05f;
      reset_screen();
  }
  else if(up){
      Player.position.y+=0.05f;
      Player.timeoffalling=0.00f;
  }

}

void tick_firebeam(){
    float ypos1=(e3[1].c1.position.y+e3[1].c2.position.y)/2.0;
    float ypos2=(e3[0].c1.position.y+e3[0].c2.position.y)/2.0;
    if(ypos2<4.0&&temp==0){
        e3[0].c1.position.y+=0.05;
        e3[0].c2.position.y+=0.05;
        e3[0].g1.position.y+=0.05;
        e3[1].c2.position.y+=0.05;
        e3[1].c1.position.y+=0.05;
        e3[1].g1.position.y+=0.05;
        ypos2=(e3[0].c1.position.y+e3[0].c2.position.y)/2.0;
        if(ypos2>4.0){
            // printf("hkjaslfj\n");    
            temp=1;
        }
    }
    if(ypos2>-1.0&&temp==1){
        // printf("hkjaslfj\n");
        e3[0].c1.position.y-=0.05;
        e3[0].c2.position.y-=0.05;
        e3[0].g1.position.y-=0.05;
        e3[1].c2.position.y-=0.05;
        e3[1].c1.position.y-=0.05;
        e3[1].g1.position.y-=0.05;
        ypos1=(e3[1].c1.position.y+e3[1].c2.position.y)/2.0;
        if(ypos1<-2.0){
            temp=0;
        }
    }
}
void tick_waterballon(){
    vector<WaterBall>::iterator water;
    for(water=waterballon.begin();water!=waterballon.end();water++){
        water->position.x+=0.1;
    } 
}
void tick_balloncollision(){
    vector<WaterBall>::iterator watercol;
    for(watercol=waterballon.begin();watercol!=waterballon.end();watercol++){
        for(int m=0;m<e1.size();m++){
            if(e1[m].checkcollision(watercol->position)){
                e1[m].visible=0;
                // waterballon.erase(watercol);
            }
        }
        for(int l=0;l<e2.size();l++){
            if(e2[l].checkcollision(watercol->position)){
                // printf("e2 is collided\n");
                e2[l].visible=0;
                // waterballon.erase(watercol);
            }
        }
    }   
    return ;
}
void tick_elements() {
    for(int l=0;l<cn.size();l++){
        cn[l].rotation+=5;
    }
    // printf("score is %d\n",score);
    if(Player.position.y>3.8){
        Player.position.y=3.8;
    }
    daya.rotation+=5;
    float x=(Player.position.x-daya.position.x)*(Player.position.x-daya.position.x);
    float y=(Player.position.x-daya.position.y)*(Player.position.y-daya.position.y);
    float distance=sqrtf(x+y);
    // if(distance<0.05){
    //     daya.visible=0;
    // }
    if(Player.position.x>=magnet.position.x-0.75&&Player.position.y>=magnet.position.y-0.25){
        magnet.entered=1;
    }
    if(magnet.entered==1){
        Player.position.x=magnet.position.x + 0.1-1.0f*cos(-magnet.degree*M_PI/180.0f);
        Player.position.y=magnet.position.y+0.1-1.0f*sin(-magnet.degree*M_PI/180.0f);
        screen_center_x = magnet.position.x - 1.0f * cos(-magnet.degree* M_PI / 180.0f);
        magnet.degree++;
        if(magnet.degree>=180){
            magnet.entered=0;
        }
    }
    if(Player.position.x > daya.position.x - 0.6 && Player.position.x < daya.position.x + 0.6){
        if(Player.position.y > daya.position.y - 0.6 && Player.position.y < daya.position.y + 0.6){
            if(daya.visible == 1){
                daya.visible = 0;
                Health += 100;
                sprintf(title, "JetPackJoyride::Score is %d     Health : %d", score, Health);
            }
        }
    }
    

    vector<Coins>::iterator dedec;
        RectangleObj  R1=convertrectangle(Player);
        CircleObj  c1;
        for(dedec=cn.begin();dedec!=cn.end();dedec++){
            c1=convertcircle(*dedec);
            if(CheckCollision(c1,R1) ){
                cn.erase(dedec);
                score+=10;    
                sprintf(title,"JetPack JoyRide::Score is %d,Health is %d\n",score,Health);
            }
        }
    // tick_firebeam();
    tick_waterballon();
    tick_balloncollision();
    bounding_box_t a,b;
    a.x=Boom.position.x;
    a.y=Boom.position.y;
    b.x=Player.position.x;
    b.y=Player.position.y;
    a.width=0.4;
    a.height=0.2;
    b.width=Player.width;
    b.height=Player.height;
    if(detect_collision(a,b)){
        exit(1);
    }
    if(screen_center_x>8.0&&Boom.start==0){
        Boom.start=1;
    }
    if(Boom.start==1){
        if(Boom.position.x>10.0&&Boom.position.y>-1.5){
            Boom.position.x-=0.05;
        }
        else if(Boom.position.x<10.0&&Boom.position.y>-1.7){
            Boom.position.y-=0.05;
        }
        else if(Boom.position.y<-1.7){
            Boom.position.x+=0.05;
        }
    }

    for(int m=0;m<e1.size();m++){
        if(e1[m].checkcollision(Player.position)&&e1[m].visible){
            // printf("e1 is collided\n");
            exit(1);
        }
    }
    for(int m=0;m<e2.size();m++){
        if((e2[m].checkcollision(Player.position))&&(e2[m].visible)){
            // printf("e2 is collided\n");
            exit(1);
        }
    }
    tick_firebeam();
    for(int l=0;l<e3.size();l++){
        bounding_box_t a,b;
        a.x=e3[l].g1.position.x;
        a.y=e3[l].g1.position.y;
        b.x=Player.position.x;
        b.y=Player.position.y;
        a.width=5.0;
        a.height=0.2;
        b.width=Player.width;
        b.height=Player.height;
        if(detect_collision(a,b)){
            printf("e3 collided\n");
            exit(1);
        }
    }
    if(Player.position.y>ground.position.y+ground.height/2+0.125){
        Player.timeoffalling+=1.0/120.0;
        float x=(1.0/2.0*2.0*Player.timeoffalling*Player.timeoffalling);
        if((Player.position.y-x)*1<ground.position.y+ground.height/2+0.125){
            Player.timeoffalling=0.0;
            Player.position.y=ground.position.y+ground.height/2+0.125;
        }
        else{
            Player.position.y-=x;
        }
    }
    camera_rotation_angle += 1;
    glfwSetWindowTitle(window,title);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    std::cout<<width<<"\n";
    ground      = Rectangle(0,-4,1000,4,COLOR_BLUE,0.0f);
    
    // cout<<"yis "<<ground.position.y<<" h is"<<ground.height<<"\n";
    float playerposition=ground.position.y+ground.height/2+0.25/2;
    Player      = Rectangle(0,playerposition,0.25,0.25,COLOR_GREEN,0.0f);
    Boom        =Boomerang(15.5,3.5,COLOR_DARKRED);
    daya        =Diamond(15.0,0.5,COLOR_NAVAJO_WHITE);
    magnet      =SemiCircle(15.0,2.0,0.0f,COLOR_CRIMSON);
    smallcircle =WaterBall(15.0,2.0,0.5,COLOR_BACKGROUND);
    // magnet=SemiCircle(30.0,2.0,90.0f,COLOR_BLACK);
    float c1pos;
    for(float p=0.0;p<100.0;p+=5.0){
        if(p<10.0||p>40.0){
            c1pos=ground.position.y+ground.height-0.25/2;
            for(int l=0;l<5;l++){
                c1pos+=0.25;
                x=2.0+p;
                for(int m=0;m<5;m++){
                    x+=0.25;
                    if((l+m)%2==0){
                    // c[l][m]=Coins(x,c1pos,COLOR_BROWN);
                        cn.push_back(Coins(x,c1pos,COLOR_YELLOW));
                    }
                    else{
                        cn.push_back(Coins(x,c1pos,COLOR_BROWN));
                    }
                }
            }
        }
    }
    
    //  e1.push_back(Enemy1(glm::vec3(2.0f,3.0f,0.0f),glm::vec3(3.0f,3.0f,0.0f),1));
    //      e1.push_back(Enemy1(glm::vec3(4.0f,-1.0f,0.0f),glm::vec3(7.0f,-1.0f,0.0f),1));

    //    e1.push_back(Enemy1(glm::vec3(50.0f,2.0f,0.0f),glm::vec3(50.0f,2.0f,0.0f),1));
    //  e2.push_back(Enemy1(glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(1.0f,3.0f,0.0f),1));
    //  e2.push_back(Enemy1(glm::vec3(12.0f,-1.0f,0.0f),glm::vec3(12.0f,3.0f,0.0f),1));

    //  for(float p=0.0;p<100.0;p+=4.0){
    //      if(p<28&&p<35){
    //         //  e2.push_back(Enemy1(glm::vec3(0.5f+p,-0.5f,0.0f),glm::vec3(0.5f+p,1.5f,0.0f)));
    //         e1.push_back(Enemy1(glm::vec3(5.0f+p,-1.0f,0.0f),glm::vec3(5.0f+p,-1.0f,0.0f)));
    //      }
    //  }
    for(float p=0.0;p<100.0;p+=5.0){
        if(p<20.0&&p!=15.0){
            e1.push_back(Enemy1(glm::vec3(2.0f+p,3.0f,0.0f),glm::vec3(3.0f+p,3.0f,0.0f),1));
            e2.push_back(Enemy1(glm::vec3(-2.0f+p,-0.5f,0.0f),glm::vec3(1.0f+p,3.0f,0.0f),1));
            e2.push_back(Enemy1(glm::vec3(0.5f+p,0.5f,0.0f),glm::vec3(-1.5f+p,1.5f,0.0f),1));
        }
        else if(p>50.0){
            e1.push_back(Enemy1(glm::vec3(2.0f+p,3.0f,0.0f),glm::vec3(3.0f+p,3.0f,0.0f),1));
            e2.push_back(Enemy1(glm::vec3(-2.0f+p,-0.5f,0.0f),glm::vec3(1.0f+p,3.0f,0.0f),1));
            e2.push_back(Enemy1(glm::vec3(1.5f+p,0.5f,0.0f),glm::vec3(-1.5f+p,1.5f,0.0f),1));
        }
    }
    e3.push_back(Enemy1(glm::vec3(20.0f,2.0f,0.0f),glm::vec3(25.0f,2.0f,0.0f),1));
    e3.push_back(Enemy1(glm::vec3(20.0f,1.0f,0.0f),glm::vec3(25.0f,1.0f,0.0f),1));
    e3.push_back(Enemy1(glm::vec3(30.0f,0.0f,0.0f),glm::vec3(35.0f,0.0f,0.0f),1));
    for(float t=38;t<39.0;t+=0.05){
        int k=39-t;
       e3.push_back(Enemy1(glm::vec3(30.0f,0.0f+k,0.0f),glm::vec3(35.0f,0.0f+k,0.0f),1)); 
    }
    Player.speed=0.0;
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    // cout<<c[1][1].position.x<<"\n";
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1;
    int height = 1;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    sprintf(title,"JetPack JoyRide:Score is %d,Health is %d\n",score,Health);
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 7 / screen_zoom;
    float right  = screen_center_x +  7/ screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

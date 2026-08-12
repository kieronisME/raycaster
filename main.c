#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>  
#include <math.h>

/* window dimensions */
#define WIDTH  1024
#define HEIGHT 512

/* maths */
#define PI 3.1415926535


/* Player */
float player_x;
float player_y;
float player_delta_x;
float player_delta_y;
float player_angle;


/*  Map */
int map_x    = 8; 
int map_y    = 8; 
int map_size = 64;  
int map_x_offset;
int map_y_offset;
int map[] =
{
    1,1,1,1,1,1,1,1,
    1,0,0,0,1,0,0,1,
    1,0,0,0,1,0,0,1,
    1,0,0,0,1,0,0,0,
    1,0,0,0,0,0,0,0,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};


void Map(){
    for (int y = 0; y < map_y; y++){
        for(int x = 0; x < map_x; x++){
            //draw map 
            if(map[y * map_x + x] == 1){
                glColor3f(1,1,1);

            }else{ 
                glColor3f(0,0,0); 

            }

            map_x_offset = x * map_size;
            map_y_offset = y * map_size;

            glBegin(GL_QUADS);
                glVertex2i(map_x_offset            + 1, map_y_offset            + 1); // top left
                glVertex2i(map_x_offset            + 1, map_y_offset + map_size - 1); // bottom left
                glVertex2i(map_x_offset + map_size - 1, map_y_offset + map_size - 1); // bottom right
                glVertex2i(map_x_offset + map_size - 1, map_y_offset            + 1); // top right
            glEnd();

        }
    }
}

void movement (unsigned char key, int x, int y){
    if (key == 'w'){
        player_x += player_delta_x;
        player_y += player_delta_y;
        printf("yes\n");
    }

    if (key == 's'){
        player_x += player_delta_x;
        player_y += player_delta_y;
        printf("yes\n");
    }

    if (key == 'd'){
        player_angle += 0.14;
        if(player_angle > 2 * PI){ 
            player_angle -= 2 * PI;
        }

        player_delta_x = cos(player_angle) * 20;
        player_delta_y = sin(player_angle) * 20;
        printf("yes\n");
    }
    if (key == 'a'){
        player_angle += 0.14;
        if(player_angle < 0){ 
            player_angle += 2 * PI;
        }

        player_delta_x = cos(player_angle) * 20;
        player_delta_y = sin(player_angle) * 20;
        printf("yes\n");
    }


    glutPostRedisplay(); // refresh window 


}

void player(){
    
    glColor3f(1,1,0);

    //player
    glPointSize(8);
    glBegin(GL_POINTS);
        glVertex2i(player_x, player_y);
    glEnd(); 

    //player angle direction
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2i(player_x, player_y);                                           // starting position
        glVertex2i(player_x + player_delta_x * 5, player_y + player_delta_y * 5); // end position
    glEnd();

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Map();
    player();
    glutSwapBuffers();
    
}

void init(){
    glClearColor(0.5, 0.5, 0.5, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);

    //player starting position
    player_x = 300;
    player_y = 300;

    //player look angle 
    player_delta_x = cos(player_angle) * 5;
    player_delta_y = sin(player_angle) * 5;

}



int main (int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("wizard casting rays");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(movement);
    glutMainLoop();
    return 0;
}
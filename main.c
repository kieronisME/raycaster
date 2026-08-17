//todo
//make map bigger 


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

typedef struct{
    int  ray;
    int  map_x;
    int  map_y;
    int  map_pos;
    int  depth_of_feild;

    float ray_angle;
    float ray_x_offset;
    float ray_y_offset;
    float ray_x;
    float ray_y;
    float dist;


}Ray; Ray R;

void castingRays()
{
    R.ray             = 0;
    R.map_x           = 0;
    R.map_y           = 0;
    R.map_pos         = 0;
    R.depth_of_feild  = 0;
    R.ray_angle       = player_angle;
    R.ray_x_offset    = 0;
    R.ray_y_offset    = 0;
    R.ray_x           = 0;
    R.ray_y           = 0;
    R.dist            = 0;

    for(int x = 0; x < 1; x++ )
    {
        R.depth_of_feild = 0;
        float tanI = -1 / tan(R.ray_angle);

        /*               hit horizontal line check              */
        // looking up
        if ( R.ray_angle > PI)
        {
            R.ray_y = (((int)player_y << 6) >> 6) - 0.0001;  // 0.0001 for flaoting point precision 
            R.ray_x = (player_y - R.ray_y) * tanI + player_x; // y = m x + c
            R.ray_y_offset = -64;
            R.ray_x_offset = -R.ray_y_offset * tanI;
        }
        // looking down
        if ( R.ray_angle < PI)
        {
            R.ray_y = (((int)player_y << 6) >> 6) + 64;  // 0.0001 for flaoting point precision 
            R.ray_x = (player_y - R.ray_y) * tanI + player_x; // y = m x + c
            R.ray_y_offset = 64;
            R.ray_x_offset = -R.ray_y_offset * tanI; //why y
        }

        // looking right 
        if( R.ray_angle == 0 || R.ray_angle == PI)
        {
            R.ray_x = player_x;
            R.ray_y = player_y;
            R.depth_of_feild = 8;
        }

        while( R.depth_of_feild < 8)
        {
            R.map_x = (int)R.ray_x >> 6; // in box cords
            R.map_y = (int)R.ray_y >> 6; // in box cords
            R.map_pos = R.map_y * map_x + R.map_x; // ROW * num of collums + index to find current map position  

            if(R.map_pos < map_x * map_y && map[R.map_pos] == 1)
            {
                R.depth_of_feild = 8; 
            }
            else
            {
                R.ray_x += R.ray_x_offset;
                R.ray_y += R.ray_y_offset;
                R.depth_of_feild += 1;
            }
        }


        glColor3f(1,0.5,1);
        glBegin(GL_LINES);
            glVertex2i(player_x, player_y);
            glVertex2i(R.ray_x, R.ray_y);
        glEnd();










        /*               hit vertical line check              */
        // looking left
        // looking right







    }

}

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

void movement (unsigned char key, int x, int y)
{
    if (key == 'w')
    {
        player_x += player_delta_x;
        player_y += player_delta_y;
        // printf("w\n");
    }

    if (key == 's')
    {
        player_x -= player_delta_x;
        player_y -= player_delta_y;
        // printf("s\n");
    }

    if (key == 'd')
    {
        player_angle += 0.14;
        if(player_angle > 2 * PI)
        { 
            player_angle -= 2 * PI;
        }
        player_delta_x = cos(player_angle) * 5;
        player_delta_y = sin(player_angle) * 5;

        // printf("d\n");
    }
// 6.28318530718
// 9.42477796077
    if (key == 'a')
    {
        player_angle -= 0.14;
        if(player_angle < 0)
        { 
            player_angle += 2 * PI;
        }

        player_delta_x = cos(player_angle) * 5;
        player_delta_y = sin(player_angle) * 5;
        // printf("a\n");
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
    castingRays();
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
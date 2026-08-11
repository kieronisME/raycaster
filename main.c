#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>  
#include <math.h>

//window dimentions 
#define WIDTH  1024
#define HEIGHT 512


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
    
}

void init(){

    glClearColor(0.5, 0.5, 0.5, 0);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
}



int main (int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("wizard casting rays");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
#include <iostream>
#include <time.h>
#include "../include/display.h"
#include "../include/inputHandling.h"

using namespace std;

int main(int argc, char **argv)
{
    initializeCube(3);

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Rubik's Cube");

    // Register callbacks
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(normalKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);

    // Enable depth testing to correctly display the 3D cube
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
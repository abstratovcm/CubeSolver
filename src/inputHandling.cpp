#include "../include/inputHandling.h"

void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
        moveSide(0, 1);
    else if (key == GLUT_KEY_LEFT)
        moveSide(1, 1);
    else if (key == GLUT_KEY_UP)
        moveSide(2, 1);
    else if (key == GLUT_KEY_DOWN)
        moveSide(3, 1);
    glutPostRedisplay();
}

void normalKeys(unsigned char key, int x, int y)
{
    if (key == '1')
    {
        Reset();
    }
    else if (key == 'F')
    {
        moveSide(FRONT, 1);
    }
    else if (key == 'f')
    {
        moveSide(FRONT, -1);
    }
    else if (key == 'B')
    {
        moveSide(BACK, 1);
    }
    else if (key == 'b')
    {
        moveSide(BACK, -1);
    }
    else if (key == 'L')
    {
        moveSide(LEFT, 1);
    }
    else if (key == 'l')
    {
        moveSide(LEFT, -1);
    }
    else if (key == 'R')
    {
        moveSide(RIGHT, 1);
    }
    else if (key == 'r')
    {
        moveSide(RIGHT, -1);
    }
    else if (key == 'U')
    {
        moveSide(TOP, 1);
    }
    else if (key == 'u')
    {
        moveSide(TOP, -1);
    }
    else if (key == 'D')
    {
        moveSide(BOTTOM, 1);
    }
    else if (key == 'd')
    {
        moveSide(BOTTOM, -1);
    }

    glutPostRedisplay();
}
#include "../include/inputHandling.h"

void specialKeys(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_UP:
        cameraPitch -= 4.0f;
        break;
    case GLUT_KEY_DOWN:
        cameraPitch += 4.0f;
        break;
    case GLUT_KEY_LEFT:
        cameraYaw -= 4.0f;
        break;
    case GLUT_KEY_RIGHT:
        cameraYaw += 4.0f;
        break;
    }
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

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseDown = true;
        }
        else
        {
            mouseDown = false;
        }
    }
}

void motion(int x, int y)
{

    if (mouseDown)
    {
        cameraYaw += (lastMouseX - x) * 0.5f;
        cameraPitch += (lastMouseY - y) * 0.5f;
    }
    lastMouseX = x;
    lastMouseY = y;
    text = std::to_string(x) + " " + std::to_string(y);
    glutPostRedisplay();
}

void passiveMotion(int x, int y) {
    lastMouseX = x;
    lastMouseY = y;
    text = std::to_string(x) + " " + std::to_string(y);
    glutPostRedisplay();
}
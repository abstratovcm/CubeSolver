#include "../include/drawing.h"

extern std::vector<Cube> cubes;

void personalizedGlutCube(GLdouble width)
{
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-width / 2, width / 2, width / 2);
    glVertex3f(width / 2, width / 2, width / 2);
    glVertex3f(width / 2, width / 2, -width / 2);
    glVertex3f(-width / 2, width / 2, -width / 2);

    glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(width / 2, -width / 2, width / 2);
    glVertex3f(width / 2, width / 2, width / 2);
    glVertex3f(-width / 2, width / 2, width / 2);
    glVertex3f(-width / 2, -width / 2, width / 2);

    glColor3f(0.0f, 0.0f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(width / 2, width / 2, -width / 2);
    glVertex3f(width / 2, width / 2, width / 2);
    glVertex3f(width / 2, -width / 2, width / 2);
    glVertex3f(width / 2, -width / 2, -width / 2);

    glColor3f(1.0f, 1.0f, 0.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-width / 2, -width / 2, width / 2);
    glVertex3f(-width / 2, width / 2, width / 2);
    glVertex3f(-width / 2, width / 2, -width / 2);
    glVertex3f(-width / 2, -width / 2, -width / 2);

    glColor3f(1.0f, 0.0f, 1.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(width / 2, -width / 2, width / 2);
    glVertex3f(-width / 2, -width / 2, width / 2);
    glVertex3f(-width / 2, -width / 2, -width / 2);
    glVertex3f(width / 2, -width / 2, -width / 2);

    glColor3f(0.0f, 1.0f, 1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(width / 2, width / 2, -width / 2);
    glVertex3f(width / 2, -width / 2, -width / 2);
    glVertex3f(-width / 2, -width / 2, -width / 2);
    glVertex3f(-width / 2, width / 2, -width / 2);

    glEnd();
}

void drawCube(const Cube &cube)
{
    glPushMatrix();
    glTranslatef(cube.position.x, cube.position.y, cube.position.z);
    glm::mat4 rotationMatrix = glm::toMat4(cube.rotation);
    glMultMatrixf(glm::value_ptr(rotationMatrix));
    personalizedGlutCube(cubeSize * 3. / 4.);
    glPopMatrix();
}

void drawCubes()
{
    for (int i = 0; i < cubes.size(); i++)
    {
        drawCube(cubes[i]);
    }
}

void drawText()
{

    // Push the current matrix onto the stack to save it
    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(60, w / h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cameraX, cameraY, cameraZ, // Camera position
              0.0f, 0.0f, 0.0f,          // Look at position
              0.0f, 1.0f, 0.0f);         // Up direction

    glPushMatrix();

    // Set the color of the text
    glColor3f(1.0, 1.0, 1.0);

    // Position the text in 3D space
    glRasterPos4f(-2, 3.5, 0, 1);

    // Draw the text
    for (int i = 0; i < text.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }

    // Pop the matrix from the stack to restore it to its previous state
    glPopMatrix();
    glPopMatrix();
}

void updateCamera()
{
    // Set the camera's position
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, // Camera position
              0.0f, 0.0f, 0.0f,          // Look at position
              0.0f, 1.0f, 0.0f);         // Up direction

    // Rotate the camera based on its direction
    glRotatef(cameraYaw, 0.0f, 1.0f, 0.0f);
    glRotatef(cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraRow, 0.0f, 0.0f, 1.0f);
}
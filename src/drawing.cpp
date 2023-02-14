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
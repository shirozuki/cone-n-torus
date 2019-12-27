//#include <windows.h>								 
#include "freeglut.h"
#define STEP 1

GLfloat eyeX = 0.0;
GLfloat eyeY = 10.0;
GLfloat eyeZ = 30.0;
GLfloat centerX = 0;
GLfloat centerY = 10;
GLfloat centerZ = 0;

void display()
{
    glClearColor(0.1, 0.1, 0.1, 0.0); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 1000.0);
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat highAmbient[] = {0.75, 0.75, 0.0};
    GLfloat highDiffuse[] = {0.75, 0.75, 0.0};
    GLfloat highSpecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat highShiness[] = {128, 128, 128};

    GLfloat lowAmbient[] = {1.0, 0.0, 0.0};
    GLfloat lowDiffuse[] = {1.0, 0.0, 0.0};
    GLfloat lowSpecular[] = {0.5, 0.5, 0.5, 0.5};
    GLfloat lowShiness[] = {0, 0, 0};
    

    // Stożek
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lowAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lowSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, lowShiness);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(90, -1, 0, 0);
    glutSolidCone(8, 20, 100, 100);
    glPopMatrix();

    // Torus
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, highAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, highSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, highShiness);
    glPushMatrix();
    glTranslatef(0, 10, 0);
    glRotatef(90, -1, 0, 0);
    glutSolidTorus(4, 10, 200, 200);
    glPopMatrix();

    // Światło I
    GLfloat lightPos[] = {centerX, centerY, centerZ, 1.0};
    GLint spotDir[] = {(int)eyeX, (int)eyeY, (int)eyeZ};
    GLfloat lightColor[] = {1, 1, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
    glLightiv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF, 25.0);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 200.0);

    // Światło II
    GLfloat lightPos2[] = {0, -20, 0, 0.0};
    GLint spotDir2[] = {0, 0, 0};
    GLfloat lightColor2[] = {0.0, 0.3, 0.0};
    
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightColor2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor2);
    glLightiv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir2);

    // Światło III
    GLfloat lightPos3[] = {-20, 30, 10, 1.0};
    GLint spotDir3[] = {0, 0, 0};
    GLfloat lightColor3[] = {0.3, 0.4, 0.0};
    
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightColor3);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor3);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightColor3);
    glLightiv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir3);

    glFlush();
} 

void Redisplay(int width, int height)
{
  glViewport(0, 0, width, height);
  display();
}

void Klawiatura(unsigned char key, int x, int y)
{
    if(key == '+')
         eyeZ -= 3;

    if(key == '-')
         eyeZ += 3;

    if(key == '1')
        glEnable(GL_LIGHT0);

    if(key == '2')
        glDisable(GL_LIGHT0);

    if(key == '3')
        glEnable(GL_LIGHT1);

    if(key == '4')
        glDisable(GL_LIGHT1);

    if(key == '5')
        glEnable(GL_LIGHT2);

    if(key == '6')
        glDisable(GL_LIGHT2);

    Redisplay(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void Strzalki(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:
        centerX -= STEP;
        eyeX -= STEP;
        break;

    case GLUT_KEY_UP:
        centerY += STEP;
        eyeY += STEP;
        break;

    case GLUT_KEY_RIGHT:
        centerX += STEP;
        eyeX += STEP;
        break;

    case GLUT_KEY_DOWN:
        centerY -= STEP;
        eyeY -= STEP;
        break;
    }
    Redisplay(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Artur Dobrowolski | id: 439386");
    glClearColor(0.1, 0.1, 0.1, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glEnable(GL_NORMALIZE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthRange(0, 150);
    glutDisplayFunc(display);
    glutReshapeFunc(Redisplay);
    glutKeyboardFunc(Klawiatura);
    glutSpecialFunc(Strzalki);
    glutMainLoop();

    return 0;
}
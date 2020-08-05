#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "Rubik.h"

#define PI 3.14159

unsigned int texts[1];

int msec = 10;

double wScreen = 800;
double hScreen = 650;
double ang_vision = 100;
int dist = 75; //distance to the cube. We cant draw here

double room_size = 100;
double obsP[3] = {-150, 0, 0};

Rubik rubik_room(room_size);
Platform plat(32, -70, 0, 0);
Ball ball(10, 0, 0, 0, 1.5, 1,2, 3000);
Cube cube(room_size*sqrt(2)/2);

double angle_vert, angle_hor, radius;

RgbImage imag;

void draw_reflexions() {

    glEnable(GL_STENCIL_TEST); //Activa o uso do stencil buffer
    glColorMask(0, 0, 0, 0); //Nao escreve no color buffer
    glDisable(GL_DEPTH_TEST); //Torna inactivo o teste de profundidade
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //Coloca a 1 todos os pixels no stencil buffer que representam a superfície reflectora
    cube.drawUp();
    //DESENHAR SUPERFÍCIE REFLECTORA
    glColorMask(1, 1, 1, 1); //Activa a escrita de cor
    glEnable(GL_DEPTH_TEST); //Activa o teste de profundidade
    glStencilFunc(GL_EQUAL, 1, 1);//O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Stencil buffer read-only
    //Desenha o objecto com a reflexão onde stencil buffer é 1
    //DESENHAR OBJECTO REFLECTIDO
    glPushMatrix();
    glTranslatef(0, 3*cube.getSize()-ball.getY() - ball.getRadius(), 0);
    glScalef(1,-1,1);
    ball.draw();
    glPopMatrix();
    glDisable(GL_STENCIL_TEST); //Desactiva a utilização do stencil buffer


    ////////////
    glEnable(GL_STENCIL_TEST); //Activa o uso do stencil buffer
    glColorMask(0, 0, 0, 0); //Nao escreve no color buffer
    glDisable(GL_DEPTH_TEST); //Torna inactivo o teste de profundidade
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //Coloca a 1 todos os pixels no stencil buffer que representam a superfície reflectora
    cube.drawDown();
    //DESENHAR SUPERFÍCIE REFLECTORA
    glColorMask(1, 1, 1, 1); //Activa a escrita de cor
    glEnable(GL_DEPTH_TEST); //Activa o teste de profundidade
    glStencilFunc(GL_EQUAL, 1, 1);//O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Stencil buffer read-only
    //Desenha o objecto com a reflexão onde stencil buffer é 1
    //DESENHAR OBJECTO REFLECTIDO
    glPushMatrix();
    glTranslatef(0, -3*cube.getSize()-ball.getY()+ball.getRadius(), 0);
    glScalef(1,-1,1);
    ball.draw();
    glPopMatrix();
    glDisable(GL_STENCIL_TEST); //Desactiva a utilização do stencil buffer

    //////////////////////
    glEnable(GL_STENCIL_TEST); //Activa o uso do stencil buffer
    glColorMask(0, 0, 0, 0); //Nao escreve no color buffer
    glDisable(GL_DEPTH_TEST); //Torna inactivo o teste de profundidade
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //Coloca a 1 todos os pixels no stencil buffer que representam a superfície reflectora
    cube.drawLeft();
    //DESENHAR SUPERFÍCIE REFLECTORA
    glColorMask(1, 1, 1, 1); //Activa a escrita de cor
    glEnable(GL_DEPTH_TEST); //Activa o teste de profundidade
    glStencilFunc(GL_EQUAL, 1, 1);//O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Stencil buffer read-only
    //Desenha o objecto com a reflexão onde stencil buffer é 1
    //DESENHAR OBJECTO REFLECTIDO
    glPushMatrix();
    glTranslatef(0, 0, -3*cube.getSize()-ball.getZ()+ball.getRadius());
    glScalef(1,1,-1);
    ball.draw();
    glPopMatrix();
    glDisable(GL_STENCIL_TEST); //Desactiva a utilização do stencil buffer
    ///////////////////////////
    glEnable(GL_STENCIL_TEST); //Activa o uso do stencil buffer
    glColorMask(0, 0, 0, 0); //Nao escreve no color buffer
    glDisable(GL_DEPTH_TEST); //Torna inactivo o teste de profundidade
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //Coloca a 1 todos os pixels no stencil buffer que representam a superfície reflectora
    cube.drawRight();
    //DESENHAR SUPERFÍCIE REFLECTORA
    glColorMask(1, 1, 1, 1); //Activa a escrita de cor
    glEnable(GL_DEPTH_TEST); //Activa o teste de profundidade
    glStencilFunc(GL_EQUAL, 1, 1);//O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Stencil buffer read-only
    //Desenha o objecto com a reflexão onde stencil buffer é 1
    //DESENHAR OBJECTO REFLECTIDO
    glPushMatrix();
    glTranslatef(0, 0, 3*cube.getSize()-ball.getZ() - ball.getRadius());
    glScalef(1,1,-1);
    ball.draw();
    glPopMatrix();
    glDisable(GL_STENCIL_TEST); //Desactiva a utilização do stencil buffer
}

void drawScene() {
    // glColor3f(WHITE);
    // glBegin(GL_LINES);
	// 	glVertex3i( 0, 0, 0);
	// 	glVertex3i( 0, 0,100);
	// glEnd();
    // glColor3f(RED);
    // glBegin(GL_LINES);
	// 	glVertex3i( 0, 0, 0);
	// 	glVertex3i( 100, 0, 0);
	// glEnd();


    rubik_room.update();
    ball.update(cube, plat);

    rubik_room.draw();
    cube.draw();
    ball.draw();
    plat.draw();

    glClear(GL_DEPTH_BUFFER_BIT);
    draw_reflexions();


}

void init_texturas() {
    glGenTextures(1, &texts[0]); //Cria o identificador da textura
	glBindTexture(GL_TEXTURE_2D, texts[0]); //Criar um objeto textura e associa-lo ao identificador
    imag.LoadBmpFile("glass.bmp"); //Fazer load da imagem
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
}

void init(void)
{
	glClearColor(ALPHA_BLACK);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
    angle_vert = 0;
    angle_hor = 0;
    radius = 50;
    init_texturas();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec,Timer, 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glViewport(0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(ang_vision, (float)wScreen/hScreen, dist+0.5, 900);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsP[0], obsP[1], obsP[2], 0,0,0, 0,1,0);

    drawScene();


    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){


    switch (key) {
    case 27:
        exit(0);
        break;
    }

  glutPostRedisplay();

}

void teclasNotAscii(int key, int x, int y){

	glutPostRedisplay();
}

void mouse(int z, int y) {

    double pz = (z * room_size * 2/ wScreen) - room_size;
    double py = (room_size - (y * room_size * 2 / hScreen));

    plat.update(py, pz);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition (400, 200);
    glutCreateWindow("Best game eva");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(msec, Timer, 1);
    glutSpecialFunc(teclasNotAscii);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse);

    glutMainLoop();

    return 0;
}

#include "Rubik.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>

#define frand()     ((float)rand()/RAND_MAX)

extern unsigned int texts[1];

Rubik::Rubik(int size) {
    Size = size;
    AxisBeingRotated = 1;
}

void Rubik::draw() {

    glPushMatrix();
    glScalef(Size, Size, Size);
    float x = 1, y = 1, z = 1;
    float third = 2.0/3;

    //FRONT FACE, X = 1
    x = 1;
    int counter = 0;
    for(z = -1; z < 1; z += third) {
        for(y = -1; y < 1; y += third) {
            glPushMatrix();
            if(y > 0.1 && AxisBeingRotated == 1) {
                glRotatef(Rotation, 0, 1, 0);
            }
            if(y == -1 && AxisBeingRotated == 3) {
                glRotatef(Rotation, 0, 1, 0);
            }
            if(z > 0.1 && AxisBeingRotated == 4) {
                glRotatef(Rotation, 0, 0, 1);
            }
            if(z == -1 && AxisBeingRotated == 5) {
                glRotatef(Rotation, 0, 0, 1);
            }
            glTranslatef(1,0,0);
            if(AxisBeingRotated == 0) {
                glRotatef(Rotation, 1, 0, 0);
            }
            glBegin(GL_QUADS);
            glColor3f(Colors[0][counter][0], Colors[0][counter][1], Colors[0][counter][2]);
            counter++;
            glVertex3f(0, y+third-Edge, z+third);
            glVertex3f(0, y+third-Edge, z+Edge);
            glVertex3f(0, y+Edge, z+Edge);
            glVertex3f(0, y+Edge, z+third);
            glEnd();
            glPopMatrix();
        }
    }

    //UPPER FACE, Y = 1
    y = 1;
    counter = 0;
    for(z = -1; z < 1; z += third) {
        for(x = -1; x < 1; x += third) {
            glPushMatrix();
            if(x > 0.1 && AxisBeingRotated == 0) {
                glRotatef(Rotation, 1, 0, 0);
            }
            if(x == -1 && AxisBeingRotated == 2) {
                glRotatef(Rotation, 1, 0, 0);
            }
            if(z > 0.1 && AxisBeingRotated == 4) {
                glRotatef(Rotation, 0, 0, 1);
            }
            if(z == -1 && AxisBeingRotated == 5) {
                glRotatef(Rotation, 0, 0, 1);
            }
            glTranslatef(0,1,0);
            if(AxisBeingRotated == 1) {
                glRotatef(Rotation, 0, 1, 0);
            }
            glBegin(GL_QUADS);
            glColor3f(Colors[1][counter][0], Colors[1][counter][1], Colors[1][counter][2]);
            counter++;
            glVertex3f(x+third-Edge, 0, z+Edge);
            glVertex3f(x+third-Edge, 0, z+third-Edge);
            glVertex3f(x+Edge, 0, z+third-Edge);
            glVertex3f(x+Edge, 0, z+Edge);
            glEnd();
            glPopMatrix();
        }
    }

    //BACK FACE X = -1
    x = -1;
    counter = 0;
    for(z = -1; z < 1; z += third) {
        for(y = -1; y < 1; y += third) {
            glPushMatrix();
            if(y > 0.1 && AxisBeingRotated == 1) {
                glRotatef(Rotation, 0, 1, 0);
            }
            if(y == -1 && AxisBeingRotated == 3) {
                glRotatef(Rotation, 0, 1, 0);
            }
            if(z > 0.1 && AxisBeingRotated == 4) {
                glRotatef(Rotation, 0, 0, 1);
            }
            if(z == -1 && AxisBeingRotated == 5) {
                glRotatef(Rotation, 0, 0, 1);
            }
            glTranslatef(-1,0,0);
            if(AxisBeingRotated == 2) {
                glRotatef(Rotation, 1, 0, 0);
            }
            glBegin(GL_QUADS);
            glColor3f(Colors[2][counter][0], Colors[2][counter][1], Colors[2][counter][2]);
            counter++;
            glVertex3f(0, y+third-Edge, z+third);
            glVertex3f(0, y+third-Edge, z+Edge);
            glVertex3f(0, y+Edge, z+Edge);
            glVertex3f(0, y+Edge, z+third);
            glEnd();
            glPopMatrix();
        }
    }
    //DOWN FACE Y = -1
    y = -1;
    counter = 0;
    for(z = -1; z < 1; z += third) {
        for(x = -1; x < 1; x += third) {
            glPushMatrix();
            if(x > 0.1 && AxisBeingRotated == 0) {
                glRotatef(Rotation, 1, 0, 0);
            }
            if(x == -1 && AxisBeingRotated == 2) {
                glRotatef(Rotation, 1, 0, 0);
            }
            if(z > 0.1 && AxisBeingRotated == 4) {
                glRotatef(Rotation, 0, 0, 1);
            }
            if(z == -1 && AxisBeingRotated == 5) {
                glRotatef(Rotation, 0, 0, 1);
            }
            glTranslatef(0,-1,0);
            if(AxisBeingRotated == 3) {
                glRotatef(Rotation, 0, 1, 0);
            }
            glBegin(GL_QUADS);
            glColor3f(Colors[3][counter][0], Colors[3][counter][1], Colors[3][counter][2]);
            counter++;
            glVertex3f(x+Edge, 0, z+third);
            glVertex3f(x+Edge, 0, z+Edge);
            glVertex3f(x+third-Edge, 0, z+Edge);
            glVertex3f(x+third-Edge, 0, z+third);
            glEnd();
            glPopMatrix();
        }
    }
    //LEFT FACE Z = 1
    z = 1;
    counter = 0;
    for(y = -1; y < 1; y += third) {
        for(x = -1; x < 1; x += third) {
            glPushMatrix();
            if(x > 0.1 && AxisBeingRotated == 0) {
                glRotatef(Rotation, 1, 0, 0);
            }
            if(x == -1 && AxisBeingRotated == 2) {
                glRotatef(Rotation, 1, 0, 0);
            }
            if(y > 0.1 && AxisBeingRotated == 1) {
                glRotatef(Rotation, 0, 1, 0);
            }
            if(y == -1 && AxisBeingRotated == 3) {
                glRotatef(Rotation, 0, 1, 0);
            }
            glTranslatef(0,0,1);
            if(AxisBeingRotated == 4) {
                glRotatef(Rotation, 0, 0, 1);
            }
            glBegin(GL_QUADS);
            glColor3f(Colors[4][counter][0],Colors[4][counter][1],Colors[4][counter][2]);
            counter++;
            glVertex3f(x+Edge, y+third-Edge, 0);
            glVertex3f(x+third-Edge, y+third-Edge, 0);
            glVertex3f(x+third-Edge, y+Edge, 0);
            glVertex3f(x+Edge, y+Edge, 0);
            glEnd();
            glPopMatrix();
        }
    }
    //RIGHT FACE Z = -1
    z = -1;
    counter = 0;
    for(y = -1; y < 1; y += third) {
        for(x = -1; x < 1; x += third) {
            glPushMatrix();
            if(x > 0.1 && AxisBeingRotated == 0) {
                glRotatef(Rotation, 1, 0, 0);
            }
            if(x == -1 && AxisBeingRotated == 2) {
                glRotatef(Rotation, 1, 0, 0);
            }
            if(y > 0.1 && AxisBeingRotated == 1) {
                glRotatef(Rotation, 0, 1, 0);
            }
            if(y == -1 && AxisBeingRotated == 3) {
                glRotatef(Rotation, 0, 1, 0);
            }
            glTranslatef(0,0,-1);
            if(AxisBeingRotated == 5) {
                glRotatef(Rotation, 0, 0, 1);
            }
            glBegin(GL_QUADS);
            glColor3f(Colors[5][counter][0],Colors[5][counter][1],Colors[5][counter][2]);
            counter++;
            glVertex3f(x+Edge, y+third-Edge, 0);
            glVertex3f(x+third-Edge, y+third-Edge, 0);
            glVertex3f(x+third-Edge, y+Edge, 0);
            glVertex3f(x+Edge, y+Edge, 0);
            glEnd();
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void Rubik::update() {
    if(Rotation >= 90) {
        updateState();
        Rotation = 0;
        AxisBeingRotated = rand() % 6;
    }
    Rotation += 0.5;
}

void Rubik::updateState() {
    double temp[3][3];

    if(AxisBeingRotated == 0) {
        copyColors(Colors[0][6], Colors[0][3], Colors[0][0], temp[0], temp[1], temp[2]);
        copyColors(Colors[0][8], Colors[0][7], Colors[0][6], Colors[0][6], Colors[0][3], Colors[0][0]);
        copyColors(Colors[0][2], Colors[0][5], Colors[0][8], Colors[0][8], Colors[0][7], Colors[0][6]);
        copyColors(Colors[0][0], Colors[0][1], Colors[0][2], Colors[0][2], Colors[0][5], Colors[0][8]);
        copyColors(temp[0], temp[1], temp[2], Colors[0][0], Colors[0][1], Colors[0][2]);

        copyColors(Colors[1][8], Colors[1][5], Colors[1][2], temp[0], temp[1], temp[2]);
        copyColors(Colors[5][8], Colors[5][5], Colors[5][2], Colors[1][8], Colors[1][5], Colors[1][2]);
        copyColors(Colors[3][2], Colors[3][5], Colors[3][8], Colors[5][8], Colors[5][5], Colors[5][2]);
        copyColors(Colors[4][8], Colors[4][5], Colors[4][2], Colors[3][8], Colors[3][5], Colors[3][2]);
        copyColors(temp[0], temp[1], temp[2], Colors[4][2], Colors[4][5], Colors[4][8]);
    }
    else if(AxisBeingRotated == 1) {
        copyColors(Colors[1][0], Colors[1][3], Colors[1][6], temp[0], temp[1], temp[2]);
        copyColors(Colors[1][2], Colors[1][1], Colors[1][0], Colors[1][0], Colors[1][3], Colors[1][6]);
        copyColors(Colors[1][8], Colors[1][5], Colors[1][2], Colors[1][2], Colors[1][1], Colors[1][0]);
        copyColors(Colors[1][6], Colors[1][7], Colors[1][8], Colors[1][8], Colors[1][5], Colors[1][2]);
        copyColors(temp[0], temp[1], temp[2], Colors[1][6], Colors[1][7], Colors[1][8]);

        copyColors(Colors[2][8], Colors[2][5], Colors[2][2], temp[0], temp[1], temp[2]);
        copyColors(Colors[5][8], Colors[5][7], Colors[5][6], Colors[2][2], Colors[2][5], Colors[2][8]);
        copyColors(Colors[0][8], Colors[0][5], Colors[0][2], Colors[5][8], Colors[5][7], Colors[5][6]);
        copyColors(Colors[4][6], Colors[4][7], Colors[4][8], Colors[0][8], Colors[0][5], Colors[0][2]);
        copyColors(temp[0], temp[1], temp[2], Colors[4][8], Colors[4][7], Colors[4][6]);
    }
    else if(AxisBeingRotated == 2) {
        copyColors(Colors[2][6], Colors[2][3], Colors[2][0], temp[0], temp[1], temp[2]);
        copyColors(Colors[2][8], Colors[2][7], Colors[2][6], Colors[2][6], Colors[2][3], Colors[2][0]);
        copyColors(Colors[2][2], Colors[2][5], Colors[2][8], Colors[2][8], Colors[2][7], Colors[2][6]);
        copyColors(Colors[2][0], Colors[2][1], Colors[2][2], Colors[2][2], Colors[2][5], Colors[2][8]);
        copyColors(temp[0], temp[1], temp[2], Colors[2][0], Colors[2][1], Colors[2][2]);

        copyColors(Colors[1][6], Colors[1][3], Colors[1][0], temp[0], temp[1], temp[2]);
        copyColors(Colors[5][6], Colors[5][3], Colors[5][0], Colors[1][6], Colors[1][3], Colors[1][0]);
        copyColors(Colors[3][0], Colors[3][3], Colors[3][6], Colors[5][6], Colors[5][3], Colors[5][0]);
        copyColors(Colors[4][6], Colors[4][3], Colors[4][0], Colors[3][6], Colors[3][3], Colors[3][0]);
        copyColors(temp[0], temp[1], temp[2], Colors[4][0], Colors[4][3], Colors[4][6]);
    }
    else if(AxisBeingRotated == 3) {
        copyColors(Colors[3][0], Colors[3][3], Colors[3][6], temp[0], temp[1], temp[2]);
        copyColors(Colors[3][2], Colors[3][1], Colors[3][0], Colors[3][0], Colors[3][3], Colors[3][6]);
        copyColors(Colors[3][8], Colors[3][5], Colors[3][2], Colors[3][2], Colors[3][1], Colors[3][0]);
        copyColors(Colors[3][6], Colors[3][7], Colors[3][8], Colors[3][8], Colors[3][5], Colors[3][2]);
        copyColors(temp[0], temp[1], temp[2], Colors[3][6], Colors[3][7], Colors[3][8]);

        copyColors(Colors[4][0], Colors[4][1], Colors[4][2], temp[0], temp[1], temp[2]);
        copyColors(Colors[2][0], Colors[2][3], Colors[2][6], Colors[4][0], Colors[4][1], Colors[4][2]);
        copyColors(Colors[5][2], Colors[5][1], Colors[5][0], Colors[2][0], Colors[2][3], Colors[2][6]);
        copyColors(Colors[0][6], Colors[0][3], Colors[0][0], Colors[5][2], Colors[5][1], Colors[5][0]);
        copyColors(temp[0], temp[1], temp[2], Colors[0][6], Colors[0][3], Colors[0][0]);
    }
    else if(AxisBeingRotated == 4) {
        copyColors(Colors[4][6], Colors[4][3], Colors[4][0], temp[0], temp[1], temp[2]);
        copyColors(Colors[4][8], Colors[4][7], Colors[4][6], Colors[4][6], Colors[4][3], Colors[4][0]);
        copyColors(Colors[4][2], Colors[4][5], Colors[4][8], Colors[4][8], Colors[4][7], Colors[4][6]);
        copyColors(Colors[4][0], Colors[4][1], Colors[4][2], Colors[4][2], Colors[4][5], Colors[4][8]);
        copyColors(temp[0], temp[1], temp[2], Colors[4][0], Colors[4][1], Colors[4][2]);

        copyColors(Colors[3][6], Colors[3][7], Colors[3][8], temp[0], temp[1], temp[2]);
        copyColors(Colors[2][8], Colors[2][7], Colors[2][6], Colors[3][6], Colors[3][7], Colors[3][8]);
        copyColors(Colors[1][8], Colors[1][7], Colors[1][6], Colors[2][8], Colors[2][7], Colors[2][6]);
        copyColors(Colors[0][6], Colors[0][7], Colors[0][8], Colors[1][8], Colors[1][7], Colors[1][6]);
        copyColors(temp[0], temp[1], temp[2], Colors[0][6], Colors[0][7], Colors[0][8]);
    }
    else if(AxisBeingRotated == 5) {
        copyColors(Colors[5][6], Colors[5][3], Colors[5][0], temp[0], temp[1], temp[2]);
        copyColors(Colors[5][8], Colors[5][7], Colors[5][6], Colors[5][6], Colors[5][3], Colors[5][0]);
        copyColors(Colors[5][2], Colors[5][5], Colors[5][8], Colors[5][8], Colors[5][7], Colors[5][6]);
        copyColors(Colors[5][0], Colors[5][1], Colors[5][2], Colors[5][2], Colors[5][5], Colors[5][8]);
        copyColors(temp[0], temp[1], temp[2], Colors[5][0], Colors[5][1], Colors[5][2]);

        copyColors(Colors[1][2], Colors[1][1], Colors[1][0], temp[0], temp[1], temp[2]);
        copyColors(Colors[0][0], Colors[0][1], Colors[0][2], Colors[1][2], Colors[1][1], Colors[1][0]);
        copyColors(Colors[3][0], Colors[3][1], Colors[3][2], Colors[0][0], Colors[0][1], Colors[0][2]);
        copyColors(Colors[2][2], Colors[2][1], Colors[2][0], Colors[3][0], Colors[3][1], Colors[3][2]);
        copyColors(temp[0], temp[1], temp[2], Colors[2][2], Colors[2][1], Colors[2][0]);
    }

}

void Rubik::copyColors(double source[3], double dest[3]) {
    for(int i=0; i<3; i++) {
        dest[i] = source[i];
    }
}

void Rubik::copyColors(double source1[3], double source2[3], double source3[3], double dest1[3],  double dest2[3],  double dest3[3]) {
    double s[3][3];
    copyColors(source1, s[0]);
    copyColors(source2, s[1]);
    copyColors(source3, s[2]);

    for(int i=0; i<3; i++) {
        dest1[i] = s[0][i];
    }
    for(int i=0; i<3; i++) {
        dest2[i] = s[1][i];
    }
    for(int i=0; i<3; i++) {
        dest3[i] = s[2][i];
    }
}

Platform::Platform(int size, double x, double z, double y) {
    Size = size;
    this->Z = z;
    this->Y = y;
    this->X = x;
}

void Platform::draw() {
    glPushMatrix();
    glColor4f(PLATFORM_COLOR);
    glBegin(GL_QUADS);
    glVertex3f(X, Y-Size/2, Z-Size/2);
    glVertex3f(X, Y+Size/2, Z-Size/2);
    glVertex3f(X, Y+Size/2, Z+Size/2);
    glVertex3f(X, Y-Size/2, Z+Size/2);
    glEnd();
    glPopMatrix();
}

void Platform::update(double y, double z) {
    this->Y = y;
    this->Z = z;
}

double Platform::getX() {
    return X;
}

double Platform::getY() {
    return Y;
}

double Platform::getZ() {
    return Z;
}

double Platform::getSize() {
    return Size;
}

Ball::Ball(double radius, double x, double z, double y, double speed_x, double speed_y, double speed_z, int n_particles) {
    Radius = radius;
    X = x;
    Z = z;
    Y = y;
    SpeedX = speed_x;
    SpeedY = speed_y;
    SpeedZ = speed_z;
    NParticles = n_particles;
}

void Ball::draw(){
    if(isDying) {
        for(int i = 0; i < NParticles; i++) {
            Particles[i].draw();
        }
    }
    else {
        glPushMatrix();
            glTranslatef(X, Y, Z);
            glColor3f(BALL_COLOR);
            glutSolidSphere(Radius, 50, 50);
        glPopMatrix();
    }
}

void Ball::update(Cube c, Platform p) {
    if(isDying) {
        for(int i = 0; i < NParticles; i++) {
            Particles[i].update();
        }
        return;
    }

    X += SpeedX;
    Y += SpeedY;
    Z += SpeedZ;

    if(intersectsUp(c)) {
        SpeedY = -SpeedY;
        Y = c.getSize() - Radius-1;
    }
    if(intersectsDown(c)) {
        SpeedY = -SpeedY;
        Y = -c.getSize() + Radius+1;
    }
    if(intersectsLeft(c)) {
        SpeedZ = -SpeedZ;
        Z = -c.getSize() + Radius+1;
    }
    if(intersectsRight(c)) {
        SpeedZ = -SpeedZ;
        Z = c.getSize() - Radius-1;
    }
    if(intersectsBack(c)) {
        SpeedX = -SpeedX;
        X = c.getSize() - Radius-1;
    }
    if(intersectsPlatform(p)) {
        SpeedX = -SpeedX;
        X = p.getX() + Radius+1;
    }
    else if(intersectsFront(c)) {
        die();
    }
}


bool Ball::intersectsUp(Cube c) {
    if(Y + Radius >= c.getSize()) {
        return true;
    }
    return false;
}

bool Ball::intersectsDown(Cube c) {
    if(Y - Radius <= -c.getSize()) {
        return true;
    }
    return false;
}

bool Ball::intersectsLeft(Cube c) {
    if(Z - Radius <= -c.getSize()) {
        return true;
    }
    return false;
}

bool Ball::intersectsRight(Cube c) {
    if(Z + Radius >= c.getSize()) {
        return true;
    }
    return false;
}

bool Ball::intersectsBack(Cube c) {
    // printf("BACK: X(%f)-Radius(%f) <= c.size(%f)\n", X, Radius, -c.getSize());
    if(X + Radius >= c.getSize()) {
        return true;
    }
    return false;
}

bool Ball::intersectsFront(Cube c) {
    if(X - Radius <= -c.getSize()) {
        return true;
    }
    return false;
}

bool Ball::intersectsPlatform(Platform p) {
    if(X - Radius <= p.getX()
        && (Y + Radius/2 > p.getY() - p.getSize()/2 && Y - Radius/2 < p.getY() + p.getSize()/2)
        && (Z + Radius/2 > p.getZ() - p.getSize()/2 && Z - Radius/2 < p.getZ() + p.getSize()/2)
    ) {
        return true;
    }
    return false;
}
void Ball::die() {
    isDying = true;
    Particles = (Particle*) malloc(NParticles*sizeof(Particle));
    double x, y, z;
    for(int i = 0; i < NParticles; i++) {
        x = z = y = 1000;
        while(x*x + z*z +y*y > (Radius/2)*(Radius/2)) {
            x = frand()*Radius-Radius/2;
            y = frand()*Radius-Radius/2;
            z = frand()*Radius-Radius/2;
        }
        Particles[i] = Particle(DyingParticlesSize, DyingParticlesLife, x+X/2, y+Y/2, z+Z/2);
    }
}

double Ball::getY() {
    return Y;
}

double Ball::getZ() {
    return Z;
}

double Ball::getRadius() {
    return Radius;
}

Particle::Particle(double size, int life, double x, double y, double z) {
    Size = size*frand();
    Life = life*frand();
    SpeedX = rand() % 6 - 2;
    SpeedY = rand() % 6 - 2;
    SpeedZ = rand() % 6 - 2;
    X = x;
    Y = y;
    Z = z;
}

void Particle::draw() {
    glPushMatrix();
    glTranslatef(X, Y, Z);
    if(Life > 0) {
        glColor3f(BALL_COLOR);
        glBegin(GL_QUADS);
            glVertex3f(X, Y-Size, Z+Size);
    		glVertex3f(X, Y-Size, Z-Size);
            glVertex3f(X, Y+Size, Z-Size);
    	    glVertex3f(X, Y+Size, Z+Size);
    	glEnd();
    }
    glPopMatrix();
}

void Particle::update() {
    X += SpeedX;
    Y += SpeedY;
    Z += SpeedZ;
    Life--;
}

Cube::Cube(double size) {
    Size = size;
}

void Cube::draw() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texts[0]);
    glPushMatrix();
    glScalef(Size, Size, Size);
    glColor4f(CUBE_COLOR);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(1, -1, -1);
        glTexCoord2f(1.0f,0.0f);  glVertex3f(1, -1, 1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, -1);
    glEnd();
    // glBegin(GL_QUADS);
    //     glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, -1);
    //     glTexCoord2f(1.0,0.0);  glVertex3f(-1, -1, 1);
    //     glTexCoord2f(1.0, 1.0); glVertex3f(-1, 1, 1);
    //     glTexCoord2f(0.0, 1.0); glVertex3f(-1, 1, -1);
    // glEnd();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, -1);
        glTexCoord2f(1.0,0.0);  glVertex3f(-1, -1, 1);
        glTexCoord2f(1.0, 1.0); glVertex3f(1, -1, 1);
        glTexCoord2f(0.0, 1.0); glVertex3f(1, -1, -1);
    glEnd();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1, 1, -1);
        glTexCoord2f(1.0,0.0);  glVertex3f(-1, 1, 1);
        glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, 1);
        glTexCoord2f(0.0, 1.0); glVertex3f(1, 1, -1);
    glEnd();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, -1);
        glTexCoord2f(1.0,0.0);  glVertex3f(-1, 1, -1);
        glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, -1);
        glTexCoord2f(0.0, 1.0); glVertex3f(1, -1, -1);
    glEnd();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, 1);
        glTexCoord2f(1.0,0.0);  glVertex3f(-1, 1, 1);
        glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, 1);
        glTexCoord2f(0.0, 1.0); glVertex3f(1, -1, 1);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINES);
		glVertex3i( -1, -1, -1);
		glVertex3i( 1, -1, -1);
	glEnd();
    glBegin(GL_LINES);
		glVertex3i( -1, 1, -1);
		glVertex3i( 1, 1, -1);
	glEnd();
    glBegin(GL_LINES);
		glVertex3i( -1, -1, 1);
		glVertex3i( 1, -1, 1);
	glEnd();
    glBegin(GL_LINES);
		glVertex3i( -1, 1, 1);
		glVertex3i( 1, 1, 1);
	glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
double Cube::getSize() {
    return Size;
}

void Cube::drawBack() {
    glPushMatrix();
    glScalef(Size, Size, Size);
    glBegin(GL_QUADS);
        glVertex3f(1, -1, -1);
        glVertex3f(1, -1, 1);
        glVertex3f(1, 1, 1);
        glVertex3f(1, 1, -1);
    glEnd();
    glPopMatrix();
}

void Cube::drawLeft() {
    glPushMatrix();
    glScalef(Size, Size, Size);
    glBegin(GL_QUADS);

    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);

    glEnd();
    glPopMatrix();
}

void Cube::drawRight() {
    glPushMatrix();
    glScalef(Size, Size, Size);
    glBegin(GL_QUADS);

    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);

    glEnd();
    glPopMatrix();
}

void Cube::drawDown() {
    glColor4f(CUBE_COLOR);
    glPushMatrix();
    glScalef(Size, Size, Size);
    glBegin(GL_QUADS);

    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, -1);

    glEnd();
    glPopMatrix();
}

void Cube::drawUp() {
    glPushMatrix();
    glScalef(Size, Size, Size);
    glBegin(GL_QUADS);

    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, -1);

    glEnd();
    glPopMatrix();
}

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#define window_w 1000
#define window_h 1000

void initColor();
void display();
void resize(int w,int h);
void mouse(int button, int state, int x, int y);

std::vector<std::vector<GLint>>  pl;

bool rubberband = 0;

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window_w, window_h);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    initColor();
    glutMainLoop();
    return 0;
}

void initColor(){
    glClearColor(0.0, 1.0, 1.0, 1.0);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    for(auto& e:pl){
        glColor3d(0.0, 0.0, 0.0);
        glVertex2i(e[0],e[1]);
    }
    glEnd();
    glFlush();

    std::cout << "display"<<std::endl;

    glFlush();
}

void resize(int w,int h){
    glViewport(0, 0, w, h);
    glLoadIdentity();

    /* スクリーン上の座標系をマウスの座標系に一致させる */
    glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y){

    switch (button) {
        case GLUT_LEFT_BUTTON:
            printf("left");
            break;

        case GLUT_MIDDLE_BUTTON:
            printf("middle");
            break;
  
        case GLUT_RIGHT_BUTTON:
            printf("right");
            break;
  
        default:
            break;
    }

    switch (state) {
        case GLUT_UP:
            printf("up");
            pl.push_back({x,y});
            break;

        case GLUT_DOWN:
            printf("down");
            pl.push_back({x,y});
            break;
  
        default:
            break;
    }

    //printf(" at (%d, %d)\n", x, y);
    glBegin(GL_LINES);
    for(auto& e:pl){
        glColor3d(0.0, 0.0, 0.0);
        glVertex2i(e[0],e[1]);
    }
    glEnd();
    glFlush();
}
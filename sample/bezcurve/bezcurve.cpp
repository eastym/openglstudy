#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <memory>

#define SPLINE 1000.0

float t = 0.5;

std::vector<std::vector<GLfloat>> ctrlPoint = {
};

void bezNd(std::vector<std::vector<GLfloat>> inp)
{

    if (inp.size() == 2)
    {
        glColor4f(1.0, 1.0, 1.0, 1.0);

        glPointSize(20.0);
        glBegin(GL_POINTS);
        glVertex3f((1 - t) * inp.at(0).at(0) + t * inp.at(1).at(0), (1 - t) * inp.at(0).at(1) + t * inp.at(1).at(1), 0);
        glEnd();
        return;
    }
    else if (inp.size() < 2)
    {
        return;
    }

    std::vector<std::vector<GLfloat>> oup;

    glColor4f(1.0, 1.0, 1.0, 1.0);

    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);

    for (unsigned int i = 0; i < inp.size() - 1; i++)
    {
        glVertex3f((1 - t) * inp.at(i).at(0) + t * inp.at(i + 1).at(0), (1 - t) * inp.at(i).at(1) + t * inp.at(i + 1).at(1), 0);
        oup.push_back({(1 - t) * inp.at(i).at(0) + t * inp.at(i + 1).at(0), (1 - t) * inp.at(i).at(1) + t * inp.at(i + 1).at(1), 0});
    }
    glEnd();

    bezNd(oup);
}

void display()
{
    std::unique_ptr<GLfloat> buffer(new GLfloat[ctrlPoint.size() * 3]);
    int i = 0;
    for (auto &e : ctrlPoint)
    {
        memcpy(buffer.get() + i * 3, e.data(), sizeof(GLfloat) * 3);
        i++;
    }
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, ctrlPoint.size(), buffer.get());

    glClear(GL_COLOR_BUFFER_BIT);

    bezNd(ctrlPoint);

    glColor4f(1.0, 0.0, 0.0, 1.0);

    glLineWidth(10.0);

    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= SPLINE; i++)
    {
        glEvalCoord1f(static_cast<GLfloat>(i / SPLINE));
    }
    glEnd();

    glColor4f(1.0, 1.0, 0.0, 1.0);

    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);

    for (const auto &e : ctrlPoint)
    {
        glVertex3fv(e.data());
    }

    glEnd();

    glFlush();
}

void resize(int w, int h)
{

    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    std::string title;

    switch (key)
    {
    case '\33':
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 'a':
        if (t <= 1)
        {
            t += 1.f / SPLINE;
        }
        break;
    case 's':
        if (0 <= t)
        {
            t -= 1.f / SPLINE;
        }
        break;

    case 'r':
        ctrlPoint.clear();

    default:
        break;
    }
    glutPostRedisplay();

    title = " t  =  " + std::to_string(t) + " edge  = " + std::to_string(ctrlPoint.size());

    glutSetWindowTitle(title.c_str());
}

void mouse(int button, int state, int x, int y)
{

    std::string title;

    switch (state)
    {
    case GLUT_DOWN:
        printf("up");
        printf(" at (%d, %d)\n", x, y);

        ctrlPoint.push_back({static_cast<GLfloat>(x), static_cast<GLfloat>(y), 0});
        break;

    default:
        break;
    }

    title = " t  =  " + std::to_string(t) + " edge  = " + std::to_string(ctrlPoint.size());

    glutSetWindowTitle(title.c_str());

    glutPostRedisplay();
}

void init(void)
{
    std::unique_ptr<GLfloat> buffer(new GLfloat[ctrlPoint.size() * 3]);
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, ctrlPoint.size(), buffer.get());
    glEnable(GL_MAP1_VERTEX_3);
}

int main(int argc, char **argv)
{
    std::string title;

    title = " t  =  " + std::to_string(t) + " edge  = " + std::to_string(ctrlPoint.size());

    /* 初期化 */
    glutInit(&argc, argv);

    /* ウィンドウの生成 */
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(1500, 700);
    glutInitWindowSize(900, 900);

    glutCreateWindow(title.c_str());

    /* OpenGL 初期化ルーチンの呼出し */
    init();

    /* 描画ルーチンの設定 */
    glutDisplayFunc(display);
    glutReshapeFunc(resize);

    glutMouseFunc(mouse);

    /* 入力処理ルーチンの設定 */
    glutKeyboardFunc(keyboard);

    /* 無限ループ */
    glutMainLoop();

    return 0;
}
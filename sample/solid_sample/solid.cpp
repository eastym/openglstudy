#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include <vector>

#define window_w 1000
#define window_h 1000

void initColor();
void display();
void resize(int w, int h);

template <typename T1, typename T2>

T1 indexSearch(std::vector<T2> &x, int y)
{
    auto *tg = x.data();
    for (int i = 0; i < y; i++)
    {
        tg++;
    }
    return static_cast<T1>(tg);
}

template <typename T>
void createSolid(std::vector<std::vector<T>> &u_surface, std::vector<std::vector<T>> &d_surface)
{
    glBegin(GL_LINES);

    for (int i = 0; i < u_surface.size(); i++)
    {
        auto *u_tg = u_surface[i].data();
        glVertex3dv(u_tg);
    }

    glBegin(GL_LINES);
    for (int i = 0; i < d_surface.size(); i++)
    {
        auto *d_tg = d_surface[i].data();
        glVertex3dv(d_tg);
    }

    // for (int i = 0; i < u_surface.size(); i++) {

    //     float tmp = FLT_MAX;

    //     for (int i = 0; i < d_surface.size(); i++) {

    //     }

    // }

    glEnd();
}

std::vector<std::vector<GLdouble>> u = {{0.0, 0.0, 0.0}, /* A */
                                        {1.0, 0.0, 0.0}, /* B */
                                        {1.0, 1.0, 0.0}, /* C */
                                        {0.0, 1.0, 0.0},
                                        /* D */};

std::vector<std::vector<GLdouble>> d = {{0.0, 0.0, 1.0}, /* A */
                                        {1.0, 0.0, 1.0}, /* B */
                                        {1.0, 1.0, 1.0}, /* C */
                                        {0.0, 1.0, 1.0},
                                        /* D */};

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window_w, window_h);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    initColor();
    glutMainLoop();
    return 0;
}

void initColor()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0.0, 0.0, 0.0);

    createSolid<GLdouble>(u, d);

    glFlush();
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
    gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/*
最初の引数 fovy はカメラの画角であり、度で表します。
これが大きいほどワイドレンズ（透視が強くなり、絵が小さくなります）になり、 小さいほど望遠レンズになります。

２つ目の引数 aspect は画面のアスペクト比（縦横比）であり、 1 であればビューポートに表示される図形の X 方向と Y 方向のスケールが等しくなります。

３つ目の引数 zNear と４つ目の引数 zFar は表示を行う奥行き方向の範囲で、
zNear は手前（前方面）、zFar は後方（後方面）の位置を示します。 この間にある図形が描画されます。
*/
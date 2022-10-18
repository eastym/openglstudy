#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#define window_w 1000
#define window_h 1000

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

void initColor();
void initEnvironment();
void display();
void resize(int w, int h);
void mouse(int button, int state, int x, int y);

std::vector<std::vector<GLint>> pl;

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window_w, window_h);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    initColor();
    initEnvironment();
    glutMainLoop();
    return 0;
}

void initColor()
{
    glClearColor(0.0, 1.0, 1.0, 1.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    for (auto &e : pl)
    {
        glColor3d(0.0, 0.0, 0.0);
        glVertex2i(e[0], e[1]);
    }
    glEnd();
    glFlush();

    std::cout << "display" << std::endl;

    glFlush();
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glLoadIdentity();

    /* スクリーン上の座標系をマウスの座標系に一致させる */
    glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{

    switch (button)
    {
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

    switch (state)
    {
    case GLUT_UP:
        printf("up");
        pl.push_back({x, y});
        break;

    case GLUT_DOWN:
        printf("down");
        pl.push_back({x, y});
        break;

    default:
        break;
    }

    printf(" at (%d, %d)\n", x, y);
    glBegin(GL_LINES);
    // for(auto& e:pl){
    //     glColor3d(0.0, 0.0, 0.0);
    //     glVertex2i(e[0],e[1]);
    // }
    for (int i = 0; i < pl.size(); i++)
    {
        glColor3d(0.0, 0.0, 0.0);
        glVertex2iv(indexSearch<GLint *, GLint>(pl[i], 0));
    }
    glEnd();
    glFlush();
}

void initEnvironment()
{
    // 光源計算
    std::vector<GLfloat> position = {10.0, 10.0, 10.0, 1.0/*0.0 の時、平行光源*/}; 
    std::vector<GLfloat> diffuse = {0.8, 0.8, 0.8, 1.0};
    std::vector<GLfloat> specular = {1.0, 1.0, 1.0, 1.0};
    std::vector<GLfloat> ambient = {0.1, 0.1, 0.1, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, position.data());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.data());   // 拡散反射成分の色
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular.data()); // 鏡面反射成分の色
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.data());   // 環境光成分の色

/*
Ambient: 環境光
周囲の環境によって散乱し， その方向が特定不能になった光源からの光です． すべての方向から照らされるように見えます．環境光が面に当たると、全方向に均等に散乱します。
Diffuse: 拡散光
一方向からの光で，一回面に当たるとすべての方向に均等に散乱します．目の位置に無関係に、同様に明るく見えます。
Specular: 鏡面光
特定の方向から進行する光で，面から特定の方向を向かって反射する性質を持っています。
Emission: 放射光
オブジェクト自体から放射され，どの光源の影響も受けません．*/

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    // 物体の色情報
   // glEnable(GL_COLOR_MATERIAL);
    // Zテストを有効
    glEnable(GL_DEPTH_TEST);
    // 背面除去
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearColor(0.5, 0.5, 0.1, 0.0);
}
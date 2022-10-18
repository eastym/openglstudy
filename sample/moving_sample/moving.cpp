#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include <vector>
#include <chrono>

#include <random>
#include <cstdint>

#define window_w 1000
#define window_h 1000

void initColor();
void display();
void resize(int w, int h);
void idle();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);

struct Solid
{
public:
    std::vector<std::vector<GLdouble>> vertex;
    std::vector<std::vector<GLdouble>> edge;
    std::vector<GLdouble> rotate;
    std::vector<GLdouble> pos = {0.5, 0.5, 0.5};

    Solid()
    {
        vertex = {{pos[0] - 0.5, pos[1] - 0.5, pos[2] - 0.5}, /* A */
                  {pos[0] + 0.5, pos[1] - 0.5, pos[2] - 0.5}, /* B */
                  {pos[0] + 0.5, pos[1] + 0.5, pos[2] - 0.5}, /* C */
                  {pos[0] - 0.5, pos[1] + 0.5, pos[2] - 0.5}, /* D */
                  {pos[0] - 0.5, pos[1] - 0.5, pos[2] + 0.5}, /* E */
                  {pos[0] + 0.5, pos[1] - 0.5, pos[2] + 0.5}, /* F */
                  {pos[0] + 0.5, pos[1] + 0.5, pos[2] + 0.5}, /* G */
                  {pos[0] - 0.5, pos[1] + 0.5, pos[2] + 0.5} /* H */};

        edge = {{0, 1},
                {1, 2},
                {2, 3},
                {3, 0},
                {4, 5},
                {5, 6},
                {6, 7},
                {7, 4},
                {0, 4},
                {1, 5},
                {2, 6},
                {3, 7}};

        rotate = {0, 0, 0};
    }

    void doRotate(double x, double y, double z)
    {
        if (x != 0)
        {
            for (int i = 0; i < 0;)
            {
            }
        }
        this->rotate[0] += x;
        this->rotate[1] += y;
        this->rotate[2] += z;
    }

} solid;

std::vector<std::vector<GLint>> pl;
std::vector<GLint> point(4);

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
void createSolid(std::vector<std::vector<T>> &vertex, std::vector<std::vector<T>> &edge)
{

    GLfloat R, G, B;

    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    glLineWidth(5);

    for (int i = 0; i < edge.size(); ++i)
    {
        R = GLfloat(engine()) / GLfloat(UINT32_MAX);
        G = GLfloat(engine()) / GLfloat(UINT32_MAX);
        B = GLfloat(engine()) / GLfloat(UINT32_MAX);

        glColor3d(R, G, B);
        glBegin(GL_LINES);
        glVertex3dv(indexSearch<T *, T>(vertex[edge[i][0]], 0));
        glVertex3dv(indexSearch<T *, T>(vertex[edge[i][1]], 0));
        glEnd();
    }
}

std::chrono::system_clock::time_point start, end;

int main(int argc, char *argv[])
{
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutInit(&argc, argv); /*ログラム自身で処理すべき引数があるときは, 後で処理します.*/
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    // glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
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
    static int x = 0, y = 0;

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.5, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0);

    x += point[2] - point[0];
    y += point[3] - point[1];

    glRotated(static_cast<double>(x), 0.0, 1.0, 0.0);
    glRotated(static_cast<double>(y), 1.0, 0.0, 0.0);

    createSolid<GLdouble>(solid.vertex, solid.edge);

    glutSwapBuffers();
    // glFlush();
    if (x >= 360)
    {
        x -= 360;
    }

    if (y >= 360)
    {
        // end = std::chrono::system_clock::now();
        y -= 360;
        // std::cout << static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) << std::endl;
        // start = std::chrono::system_clock::now();
    }
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{

    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        point[0] = point[2] = x / 100;
        point[1] = point[3] = y / 100;
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(idle);
        }
        else
        {
            glutIdleFunc(0);
        }
        break;

    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutPostRedisplay();
        }
        break;

    default:
        break;
    }
}

void keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 'q':
    case 'Q':
    case '\033': /* '\033' は ESC の ASCII コード */
        exit(0);

    case 'x':
        std::cin >> solid.rotate[0];
        break;

    case 'y':
        std::cin >> solid.rotate[1];
        break;

    case 'z':
        std::cin >> solid.rotate[2];
        break;

    default:
        std::cout << key << std::endl;
        break;
    }
}

void motion(int x, int y)
{

    point[2] = x / 100;
    point[3] = y / 100;
}

/*
アニメーションを実現するには, このウィンドウの再描画イベントを連続的に発生させる必要があります. プログラム中でウィンドウの再描画イベントを発生させるには, glutPostRedisplay() 関数を用います. これをプログラムが「暇なとき」に繰り返し呼び出すことで, アニメーションが実現できます. プログラムが暇になったときに実行する関数は, glutIdleFunc() で指定します.

繰り返し描画を行うには, 描画の度に座標変換の行列を設定する必要があります.

座標変換のプロセスは,

図形の空間中での位置を決める「モデリング変換」
その空間を視点から見た空間に直す「ビューイング (視野) 変換」
その空間をコンピュータ内の空間にあるスクリーンに投影する「透視変換」
スクリーン上の図形をディスプレイ上の表示領域に切り出す「ビューポート変換」
という四つのステップで行われます. 今行おうとしている図形を回すという変換は, 「モデリング変換」に相当します.

これまではこれらを区別 せずに取り扱ってきました. すなわち, これらの投影を行う行列式を掛け合わせることで, 単一の行列式として取り扱ってきたのです.

しかし図形だけを動かす場合は, モデリング変換の行列だけを変更すればいいことになります. また, 後で述べる陰影付けは, 透視変換を行う前の座標系で計算する必要があります.

そこで OpenGL では, 「モデリング変換−ビューイング変換」の変換行列 (モデルビュー変換行列) と, 「透視変換」の変換行列を独立して取り扱う手段が提供されています. モデルビュー変換行列を設定する場合は glMatrixMode(GL_MODELVIEW), 透視変換行列を設定する場合は glMatrixMode(GL_PROJECTION) を実行します.

カメラの画角などのパラメータを変更しなければ, 透視変換行列を設定しなければならないのはウィンドウを開いたときだけなので, これは resize() で設定すればよいでしょう. あとは全てモデリング−ビューイング変換行列に対する操作なので, 直後に glMatrixMode(GL_MODELVIEW) を実行します.

カメラ (視点) の位置を動かすアニメーションを行う場合は, 描画のたびに gluLookAt() によるカメラの位置や方向の設定 (ビューイング変換行列の設定) を行う必要があります. 同様に物体が移動したり回転したりするアニメーションを行う場合も, 描画のたびに物体の位置や回転角の設定 (モデリング変換行列の設定) を 行う必要があります. したがって, これらは display() の中で設定します.*/
#include "animation.hpp"

#define window_w 1000
#define window_h 1000

void initColor();
void display();
void resize(int w, int h);
void idle();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void motion(int x, int y);

std::vector<std::vector<GLint>> pl;
std::vector<GLint> point(4);
FPS fps(60);

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
void createSolid(Solid target)
{
    for (auto i = 0u; i < target.getQuadEdge().size(); ++i)
    {
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        glColor3fv(target.getQuadColor().at(i).data());

        // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color.at(i).data());

        glNormal3fv(target.getNormal().at(i).data());
        glBegin(GL_QUADS);

        glVertex3fv(target.getVertex().at(target.getQuadEdge().at(i).at(0)).data());
        glVertex3fv(target.getVertex().at(target.getQuadEdge().at(i).at(1)).data());
        glVertex3fv(target.getVertex().at(target.getQuadEdge().at(i).at(2)).data());
        glVertex3fv(target.getVertex().at(target.getQuadEdge().at(i).at(3)).data());
        glEnd();
    }
}

void putObject(std::vector<Solid> shelf, int x, int y)
{

    for (auto &e : shelf)
        e.setVertex({0.5, 0.5, 0.5}, 1.0, 1.0, 1.0);

    glRotated(static_cast<double>(x), 0.0, 1.0, 0.0);
    glRotated(static_cast<double>(y), 1.0, 0.0, 0.0);

    createSolid<GLfloat>(shelf.at(0));

    glPushMatrix();

    for (auto i = 1; i < shelf.size(); i++)
    {
        glTranslated(1.0, 1.0, 1.0);
        glRotated(static_cast<double>(x), 0.0, 1.0, 0.0);
        glRotated(static_cast<double>(y), 1.0, 0.0, 0.0);

        createSolid<GLfloat>(shelf.at(i));

        glPushMatrix();
    }

    for (auto i = 0; i < shelf.size(); i++)
        glPopMatrix();
}

void lighton(std::vector<int> target)
{
    for (int light = 0; light <= GL_LIGHT7 - GL_LIGHT0; light++)
    {
        if (std::ranges::find_if(target, [light](int x)
                                 { return x == light; }) != target.cend())
        {
            glEnable(GL_LIGHT0 + light);
        }
        else
        {
            glDisable(GL_LIGHT0 + light);
        }
    }
}

void timer(int i)
{

    fps.GetFPS(glutPostRedisplay);
    glutTimerFunc(1, timer, 0);
}

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
    glutTimerFunc(1, timer, 0);

    glutMainLoop();
    return 0;
}

void initColor()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);

    std::vector<GLfloat> position = {0, 0, 10.0, 0.0 /*0.0 の時、平行光源*/};
    std::vector<GLfloat> diffuse = {1.0, 0, 0, 1.0};
    std::vector<GLfloat> specular = {0, 0.0, 0.0, 1.0};
    std::vector<GLfloat> ambient = {0.2, 0.0, 0.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, position.data());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.data());   // 拡散反射成分の色 　sub
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular.data()); // 鏡面反射成分の色 nothing
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.data());   // 環境光成分の色　light original color

    diffuse = {0, 1.0, 0, 1.0};
    specular = {0, 0, 0, 1.0};
    ambient = {0, 0.2, 0, 1.0};

    glLightfv(GL_LIGHT1, GL_POSITION, position.data());
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse.data());   // 拡散反射成分の色
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular.data()); // 鏡面反射成分の色
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient.data());   // 環境光成分の色

    diffuse = {0, 0, 1.0, 1.0};
    specular = {0, 0, 0, 1.0};
    ambient = {0, 0, 0.2, 1.0};

    glLightfv(GL_LIGHT2, GL_POSITION, position.data());
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse.data());   // 拡散反射成分の色
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular.data()); // 鏡面反射成分の色
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient.data());   // 環境光成分の色

    diffuse = {1.0, 1.0, 1.0, 1.0};
    specular = {0, 0, 0, 1.0};
    ambient = {0.2, 0.2, 0.2, 1.0};

    glLightfv(GL_LIGHT3, GL_POSITION, position.data());
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse.data());   // 拡散反射成分の色
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular.data()); // 鏡面反射成分の色
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient.data());   // 環境光成分の色

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

void display()
{
    static Solid solid, solidus, liquid, venom, naked, bahamut, alexander, omega, eden, pandemonium,
        anima, asura, chocobo, hades, ixion, masamune, titan;

    static int x = 0, y = 0;

    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.5, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0);

    x += point[2] - point[0];
    y += point[3] - point[1];

    glMatrixMode(GL_MODELVIEW); // ワールド座標-> カメラ座標　変換行列

    putObject({naked,solid,liquid,solidus,venom,bahamut,alexander,omega,eden,pandemonium,anima,asura,chocobo,hades,ixion,masamune,titan},x,y);

    glutSwapBuffers();
    glFlush();
    if (x >= 360)
    {
        x -= 360;
    }

    if (y >= 360)
    {
        y -= 360;
    }

    // std::cout << "RIGHT:  " << m[0] << "\t" << m[1] << "\t" << m[2] << std::endl;
    // std::cout << "UP:  " << m[4] << "\t" << m[5] << "\t" << m[6] << std::endl;
    // std::cout << "FRONT:  " << m[8] << "\t" << m[9] << "\t" << m[10] << std::endl;
    // std::cout << "POSITION:  " << -1 * (m[0] * m[3] + m[4] * m[7] + m[8] * m[11]) << "\t"
    //           << -1 * (m[1] * m[3] + m[5] * m[7] + m[9] * m[11]) << "\t"
    //           << -1 * (m[2] * m[3] + m[6] * m[7] + m[10] * m[11]) << std::endl;
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); /* マトリックスモードを投影変換にする */
    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0); /* 透視投影 */

    glMatrixMode(GL_MODELVIEW); /* マトリックスモードをモデルビューにする */
}

void mouse(int button, int state, int x, int y)
{

    switch (button)
    {
    case GLUT_LEFT_BUTTON:

        if (state == GLUT_DOWN)
        {
            point[0] = point[2] = x / 100;
            point[1] = point[3] = y / 100;
        }
        else
        {
            glutIdleFunc(0);
        }
        break;

    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
        }
        break;

    default:
        break;
    }
    // glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 'q':
    case 'Q':
    case '\033': /* '\033' は ESC の ASCII コード */
        exit(0);

    case 'r':
        glEnable(GL_LIGHTING);

        lighton({0});

        break;
    case 'g':
        glEnable(GL_LIGHTING);

        lighton({1});
        break;
    case 'b':
        glEnable(GL_LIGHTING);

        lighton({2});
        break;
    case 'o':
        glEnable(GL_LIGHTING);

        lighton({0, 1, 2});
        break;

    case 'w':
        glEnable(GL_LIGHTING);

        lighton({3});
        break;

    case 'p':
        glDisable(GL_LIGHTING);

        lighton({});
        break;
    default:
        break;
    }
    // glutPostRedisplay();
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

カメラ (視点) の位置を動かすアニメーションを行う場合は, 描画のたびに gluLookAt() によるカメラの位置や方向の設定 (ビューイング変換行列の設定) を行う必要があります. 同様に物体が移動したり回転したりするアニメーションを行う場合も, 描画のたびに物体の位置や回転角の設定 (モデリング変換行列の設定) を 行う必要があります. したがって, これらは display() の中で設定します.

ライティング処理は，モデルビュー変換行列モードで行われるので，glLightfv() による光源の位置 (GL_POSITION) の設定は，視点の位置を設定した後に行う必要があります． また，上のプログラムの glRotate3d() より後でこれを設定すると，光源もいっしょに回転します．

5.1 節で，座標変換のプロセスは，

モデリング変換
ビューイング（視野）変換
投影変換
ビューポート変換
という４つのステップで行わると書きましたが， プログラムのコーディング上は，これらの設定が次のように逆順になることに注意してください．
glLoadIdentity() でモデルビュー変換行列を初期化
gluLookAt()やglFrustum() 等でビューイング変換を設定
glTranslated() や glRotated() 等でモデリング変換を設定
glBegin()～glEnd() 等による描画*/

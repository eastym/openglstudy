#include <GL/glut.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <vector>

void display(void);
void resize(int w, int h);
void initColor();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);

int rubberband = 0; /* ラバーバンドの消去 */
int pointnum = 0;
GLint point[1000][2];

int main(int argc, char *argv[])
{

  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1000, 1000);
  glutInit(&argc, argv); /*ログラム自身で処理すべき引数があるときは, 後で処理します.*/
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[1]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  initColor();
  glutMainLoop();
  return 0;
}

void display()
{

  glClear(GL_COLOR_BUFFER_BIT);

  if (pointnum > 1)
  {
    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < pointnum; ++i)
    {
      glVertex2iv(point[i]);
    }
    glEnd();
  }
  glFlush();
}

void initColor()
{
  glClearColor(1, 1, 1, 0.5);
}

void resize(int w, int h)
{
  glViewport(0, 0, w, h);

  glLoadIdentity();

  glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{

  static int x0, y0;

  switch (button)
  {
  case GLUT_LEFT_BUTTON:
    point[pointnum][0] = x;
    point[pointnum][1] = y;
    if (state == GLUT_UP)
    {
      /* ボタンを押した位置から離した位置まで線を引く */
      glColor3d(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex2iv(point[pointnum - 1]); /* 一つ前は押した位置　 */
      glVertex2iv(point[pointnum]);     /* 今の位置は離した位置 */
      glEnd();
      glFlush();

      rubberband = 0;
    }
    else
    {
    }
    if (pointnum < 1000 - 1)
      ++pointnum;
    break;
  case GLUT_MIDDLE_BUTTON:
    /* 削除 */
    break;
  case GLUT_RIGHT_BUTTON:
    /* 削除 */
    break;
  default:
    break;
  }
}

void motion(int x, int y)
{
  static GLint savepoint[2]; /* 以前のラバーバンドの端点 */

  /* 論理演算機能 ON */
  glEnable(GL_COLOR_LOGIC_OP);
  glLogicOp(GL_INVERT);

  glBegin(GL_LINES);
  if (rubberband)
  {
    /* 以前のラバーバンドを消す */
    glVertex2iv(point[pointnum - 1]);
    glVertex2iv(savepoint);
  }
  /* 新しいラバーバンドを描く */
  glVertex2iv(point[pointnum - 1]);
  glVertex2i(x, y);
  glEnd();

  glFlush();

  /* 論理演算機能 OFF */
  glLogicOp(GL_COPY);
  glDisable(GL_COLOR_LOGIC_OP);

  /* 今描いたラバーバンドの端点を保存 */
  savepoint[0] = x;
  savepoint[1] = y;

  /* 今描いたラバーバンドは次のタイミングで消す */
  rubberband = 1;
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'q':
    /* code */
    std::cout << "q";
    break;

  case '\033':
    exit(0);
    break;

  default:
    break;
  }
}
/*
GLenum err = glewInit();
if (GLEW_OK != err)
{
  // 初期化に失敗した場合の処理
  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
}
*/
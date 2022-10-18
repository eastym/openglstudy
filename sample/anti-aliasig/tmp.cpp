#include <GL/glut.h>

#define window_w 1000
#define window_h 1000

void initColor();
void display();
void resize(int w,int h);

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
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

void initColor(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

/*
 混合処理の設定
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);  混合処理を ON

アンチエイリアス処理 
glEnable(GL_POINT_SMOOTH);
glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

アンチエイリアシングの対象設定
• glEnable(GL POINT SMOOTH)： 点
• glEnable(GL LINE SMOOTH)： 線
• glEnable(GL POLYGON SMOOTH)： 面

• 描画は速いがギザギザ（デフォルト設定）
• glHint(GL POINT SMOOTH HINT, GL FASTEST);
• glHint(GL LINE SMOOTH HINT, GL FASTEST);
• glHint(GL POLYGON SMOOTH HINT, GL FASTEST);

• 綺麗だが遅い
• glHint(GL POINT SMOOTH HINT, GL NICEST);
• glHint(GL LINE SMOOTH HINT, GL NICEST);
• glHint(GL POLYGON SMOOTH HINT, GL NICEST);
*/

    glFlush();
}

void resize(int w,int h){
    glViewport(0, 0, w, h);
    glLoadIdentity();
}
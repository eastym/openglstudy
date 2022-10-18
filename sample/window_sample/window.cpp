#include <GL/glut.h>

void init(){
    glClearColor(0,0.0125,0.8,0.5);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);  //描画用バッファの初期化
    glFlush();  //描画命令
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("window");
    glutDisplayFunc(display);

    init();

    glutMainLoop();
    return 0;
}
#include <GL/glut.h>

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);

    glutCreateWindow(argv[0]);
    glutMainLoop();
    return 0;
}
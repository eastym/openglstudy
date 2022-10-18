#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void display(){

#ifdef old
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3d(1.0, 0.0, 0.0); /* 赤 */
    glVertex2d(-0.9, -0.9);
    glColor3d(0.0, 1.0, 0.0); /* 緑 */
    glVertex2d(0.9, -0.9);
    glColor3d(0.0, 0.0, 1.0); /* 青 */
    glVertex2d(0.9, 0.9);
    glColor3d(1.0, 1.0, 0.0); /* 黄 */
    glVertex2d(-0.9, 0.9);
    glEnd();
    glFlush();
#endif

#ifdef new
    glm::vec3 vertices[2];
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
glDrawArrays(GL_LINES, 0, 2);
glDisableVertexAttribArray(0);
#endif
}

/*

vec3 vertices[2];
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
glDrawArrays(GL_LINES, 0, 2);
glDisableVertexAttribArray(0);

vec3 myVec = vec3(1.0, 2.5, 0.25);


*/

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
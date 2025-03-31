#include<GL/freeglut.h>

int main() {
	glutInit(&argc, argv); // Initialize FreeGLUT
    	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Single buffer, RGB mode
    	glutInitWindowSize(500, 500); // Set window size
    	glutCreateWindow("OpenGL Window"); // Create window with title

	glClearColor(0,0,0,1);


}

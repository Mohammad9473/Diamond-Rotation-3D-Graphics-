#include <GL/glut.h>
#include <bevgrafmath2017.h>
#include <math.h>

GLsizei winWidth = 800, winHeight = 600;
GLint keyStates[256];
float s = 5;

mat4 w2v, rotatedX, rotatedY, rotatedZ, projection;

float alpha = pi() / 4;
float beta = pi() / 5;
float gamma = 0 ;

int orthogonalMode = 1;


struct face {
	vec3 t[3];
	vec3 normal;
};


face thethraFaces[4] = {};

void setNormalVectors() {
	for (int i = 0; i < 4; i++)
		thethraFaces[i].normal = cross(thethraFaces[i].t[1] - thethraFaces[i].t[0], thethraFaces[i].t[2] - thethraFaces[i].t[0]);
}

struct face1 {
	vec3 d[3];
	vec3 normal;

};

face1 diamondFaces[8] = {};

void setNormalVectors1() {
	for (int i = 0; i < 8; i++)
		diamondFaces[i].normal = cross(diamondFaces[i].d[1] - diamondFaces[i].d[0], diamondFaces[i].d[2] - diamondFaces[i].d[0]);
		

}

void initThetra() {

	//bottom//
	thethraFaces[0].t[0] = { -1, float(2 * sin(2 * pi() / 3)), -0.5 };
	thethraFaces[0].t[1] = { 2, 0, -0.5 };
	thethraFaces[0].t[2] = { -1, float(-2 * sin(2 * pi() / 3)), -0.5 };

	//right
	thethraFaces[1].t[0] = { 2, 0, -0.5 };
	thethraFaces[1].t[1] = { -1, float(2 * sin(2 * pi() / 3)), -0.5 };
	thethraFaces[1].t[2] = { 0,0, 2 };
	
	//left
	thethraFaces[2].t[0] = { 0,0, 2 };
	thethraFaces[2].t[1] = { -1, float(-2 * sin(2 * pi() / 3)), -0.5 };
	thethraFaces[2].t[2] = { 2,0,-0.5 };

	//back//
	thethraFaces[3].t[0] = { -1, float(2 * sin(2 * pi() / 3)), -0.5 };
	thethraFaces[3].t[1] = { -1, float(-2 * sin(2 * pi() / 3)), -0.5 };
	thethraFaces[3].t[2] = { 0,0, 2 };
	
	setNormalVectors();

}



void initDiamond() {


	//Upright
	diamondFaces[0].d[0] = { 0.5, -0.5, 0 };
	diamondFaces[0].d[1] = { 0.5, 0.5, 0 };
	diamondFaces[0].d[2] = { 0,0, 2 };
	


	//Upback
	diamondFaces[1].d[0] = { 0.5, 0.5, 0.0 };
	diamondFaces[1].d[1] = { -0.5, 0.5, 0.0 };
	diamondFaces[1].d[2] = { 0.0, 0.0 , 2.0 };
	


	//Upleft
	diamondFaces[2].d[0] = { -0.5, 0.5 , 0.0 };
	diamondFaces[2].d[1] = { -0.5, -0.5, 0.0 };
	diamondFaces[2].d[2] = { 0.0, 0.0 , 2.0 };
	
	//Upfront
	diamondFaces[3].d[0] = { -0.5, -0.5, 0.0 };
	diamondFaces[3].d[1] = { 0.5,-0.5, 0.0 };
	diamondFaces[3].d[2] = { 0.0 ,0.0 , 2.0};
	
	//Downright
	diamondFaces[4].d[0] = { 0.5, -0.5, 0.0 };
	diamondFaces[4].d[1] = { 0.0, 0.0, -2.0 };
	diamondFaces[4].d[2] = { 0.5, 0.5, 0.0 };


	//Downback
	diamondFaces[5].d[0] = {0.5, 0.5, 0.0 };
	diamondFaces[5].d[1] = { 0.0 ,0.0, -2.0 }; 
	diamondFaces[5].d[2] = { -0.5, 0.5, 0.0 };
	


	//Downleft
	diamondFaces[6].d[0] = { -0.5, 0.5, 0.0 };
	diamondFaces[6].d[1] = { 0.0 ,0.0 , -2.0 };
	diamondFaces[6].d[2] = { -0.5, -0.5, 0.0 }; 
	


	//Downfront
	diamondFaces[7].d[0] = { -0.5, -0.5, 0.0 };
	diamondFaces[7].d[1] = { 0.0 ,0.0 , -2.0 };
	diamondFaces[7].d[2] = { 0.5, -0.5, 0.0 };
	

	setNormalVectors1();
	
}

void initMatrices() {

	vec2 windowSize = { 6, 6 };
	vec2 windowPosition = { -3, -3 };

	vec2 viewportSize = { 450, 450 };
	vec2 viewportPosition = { winWidth / 2 - viewportSize.x / 2, winHeight / 2 - viewportSize.y / 2 };
	w2v = windowToViewport3(windowPosition, windowSize, viewportPosition, viewportSize);
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(5.0);
	glLineWidth(1.0);

	initThetra();
	initDiamond();
	initMatrices();

}


void setColor(int i) {
	switch (i) {
	case 0:
		glColor3f(0.2, 0.1, 0.0);
		break;
	case 1:
		glColor3f(0.4, 0.8, 0.2);
		break;
	case 2:
		glColor3f(0.8, 0.0, 0.9);
		break;
	case 3:
		glColor3f(0.6, 0.2, 0.9);
		break;
	case 4:
		glColor3f(0.3, 0.0, 0.9);
		break;
	case 5:
		glColor3f(0.3, 0.0, 0.5);
		break;
	case 6:
		glColor3f(0.5, 0.2, 0.5);
		break;
	default:
		glColor3f(0, 0, 0);
	}
}


void drawThetra() {

	glColor3f(0.0, 0.0, 0.0);

	vec3 d1 = vec3(-2, 0, 0); //translation
	mat4 M = translate(d1); //translation 4*4 matrix
	mat4 rotation = rotateZ(gamma) * rotateY(beta) * rotateX(alpha); //all alpha beta gamma multiplication

	if (orthogonalMode) {
		projection = ortho();
	}
	else {
		projection = perspective(s);
	}


	for (int idx = 0; idx < 4; idx++) {

		face f = thethraFaces[idx]; 
		vec4 normalH = ihToH(f.normal); //normal vector
		vec3 rotatedNormal = hToIh(rotation * normalH);  //rotated normal vector

		bool condition = 0;
		if (orthogonalMode) {
			condition = rotatedNormal.z > 0.0; //condition for visibility ortoghonal
		}
		else {
			vec4 facePointH = ihToH(f.t[0]);  
			vec4 rotatedPoint = M * rotation * facePointH; //actual point on thetrahedron 
															//(multiplication of translation rotation and face vector at t[0])
			condition = dot((vec3(0, 0, s) - hToIh(rotatedPoint)), rotatedNormal) > 0; //condition for visibility of perspective projection 
		}

		if (condition) {
			mat4 M2 = w2v * projection * M * rotation; //multiplication for a face to being visible
			glBegin(GL_POLYGON);
			for (int i = 0; i < 3; i++) {

				setColor(idx);

				vec4 pointH = ihToH(f.t[i]);
				vec4 transformedPoint = M2 * pointH;

				if (transformedPoint.w != 0) {
					vec3 result = hToIh(transformedPoint);
					if (result.z == 0) {
						glVertex2f(result.x, result.y);
					}
				}

			}
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3f(0, 0, 0);
			for (int i = 0; i < 3; i++) {

				vec4 pointH = ihToH(f.t[i]);
				vec4 transformedPoint = M2 * pointH;

				if (transformedPoint.w != 0) {
					vec3 result = hToIh(transformedPoint);
					if (result.z == 0) {
						glVertex2f(result.x, result.y);
					}
				}

			}
			glEnd();

		}

	}

}

void drawDiamond() {

	glColor3f(0.0, 0.0, 0.0);

	vec3 d1 = vec3(2, 0, 0);
	mat4 M1 = translate(d1);

	mat4 rotation1 = rotateZ(gamma) * rotateY(beta) * rotateX(alpha);
	if (orthogonalMode) {
		projection = ortho();
	}
	else {
		projection = perspective(s);
	}

	
	for (int idx = 0; idx < 8; idx++) {
		face1 f1 = diamondFaces[idx];
		vec4 normalH1 = ihToH(f1.normal);
		vec3 rotatedNormal1 = hToIh(rotation1 * normalH1);

		bool condition = 0;
		if (orthogonalMode) {
			condition = rotatedNormal1.z > 0.0;
		}
		else {
			vec4 facePointH1 = ihToH(f1.d[0]);
			vec4 rotatedPoint1 = M1 * rotation1 * facePointH1;
			condition = dot((vec3(0, 0, s) - hToIh(rotatedPoint1)), rotatedNormal1) > 0;
		}

		if (condition) {
			mat4 M3 = w2v * projection * M1 * rotation1;

			glBegin(GL_POLYGON);
			for (int i = 0; i < 3; i++) {

				setColor(idx);

				vec4 pointH = ihToH(f1.d[i]);
				vec4 transformedPoint = M3 * pointH;

				if (transformedPoint.w != 0) {
					vec3 result = hToIh(transformedPoint);
					if (result.z == 0) {
						glVertex2f(result.x, result.y);
					}
				}

			}
			glEnd();


			glEnd();
			glBegin(GL_LINE_LOOP);
			glColor3f(0, 0, 0);
			for (int i = 0; i < 3; i++) {

				vec4 pointH = ihToH(f1.d[i]);
				vec4 transformedPoint = M3 * pointH;

				if (transformedPoint.w != 0) {
					vec3 result = hToIh(transformedPoint);
					if (result.z == 0) {
						glVertex2f(result.x, result.y);
					}
				}

			}
			glEnd();
		}
	}
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 0.0);

	drawThetra();
	drawDiamond();
	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = 1;

	if (key == '1') //orthogonal
		orthogonalMode = 1;
	else if (key == '2') //perspective
		orthogonalMode = 0;

}

void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = 0;
}

void keyOperations(int value)
{
	if (keyStates['a']) { alpha += 0.01; }
	if (keyStates['q']) { alpha -= 0.01; }

	if (keyStates['s']) { beta += 0.01; }
	if (keyStates['w']) { beta -= 0.01; }

	if (keyStates['d']) { gamma += 0.01; }
	if (keyStates['e']) { gamma -= 0.01; }


	glutPostRedisplay();

	glutTimerFunc(5, keyOperations, 0);
}





int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Pyramid");

	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(5, keyOperations, 0);

	glutMainLoop();
	return 0;
}

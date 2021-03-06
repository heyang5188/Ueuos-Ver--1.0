
#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <queue>

//GLM

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

////#include "AbstractDrawCommand.h"
//#include "DrawCommand/TriangeCommand.h"
//#include "DrawCommand/QuadCommand.h"
//#include "Math/Vector2.h"
//#include "Math/Vector3.h"
#include "./Math/UMath.h"
#include "./UeuosObject/SceneObject/BaseGeometry/Cube.h"
#include "./UeuosObject/SceneObject/BaseGeometry/Pyramid.h"
#include "./UeuosObject/SceneObject/TargetCamera.h"
#include "./UeuosObject/SceneObject/Axis.h"
#include "./UeuosObject/SceneObject/Grid.h"
#include "Rendering/GLProgramHelper.h"
#include "./UeuosObject/SceneObject/World.h"

//TEST 
void Vector2UnitTest();
void Vector3UnitTest();
void QuaternionUnitTest();
void TransformUnitTest();
void ViewMatrixUnitTest();
void printVector3AsEuler(Math::Vector3 rot);
void printVector3(Math::Vector3 vec);
//

//float view[] = {
//	1.0,0.0,0.0,-1.0,
//	0.0,1.0,0.0,0.0,
//	0.0,0.0,1.0,0.0,
//	0.0,0.0,0.0,1.0
//};


using namespace std;

//vector<AbstractDrawCommand*> renderVector;

const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec4 color;\n"
"uniform mat4 transform;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"uniform mat4 pv;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"gl_Position = pv*transform*vec4(position.x, position.y, position.z, 1.0);\n"
"vertexColor=color;"
"}\0";
const GLchar* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 color;\n"
"in  vec4 vertexColor;\n"
"void main()\n"
"{\n"
"color = vertexColor;\n"
"}\n\0";
float x = 100;
float y = 100;
float z = 100;
//Math::Matrix view = Math::Matrix::lookAt(Math::Vector3(x, y, z), Math::Vector3(0, 0, 0), Math::Vector3(0, 1, 0));

//glm::mat4 view = glm::lookAt(glm::vec3(x, y, z), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
//float x11 = view[5];
//int a = 0;
Ueuos::TargetCamera camera = Ueuos::TargetCamera();
int scalar = 2.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	switch ( key )
	{
	case GLFW_KEY_UP:
		y += 2;
	//	camera.transform.updateModleMatrix();
		printVector3(camera.transform.getForward().normalize());
		camera.setPosition(camera.getPosition()+camera.transform.getForward()*scalar);
		break;
	case GLFW_KEY_DOWN:
	//	y -= 2;
		camera.setPosition(camera.getPosition()- camera.transform.getForward()*scalar);
		break;
	case GLFW_KEY_LEFT:
		x -= 2;
		//printVector3AsEuler(camera.transform.getRight());
		camera.setPosition(camera.getPosition()- camera.transform.getRight()*scalar);
		break;
	case GLFW_KEY_RIGHT:
		x += 2;
		printVector3(camera.transform.getRight().normalize());
		camera.setPosition(camera.getPosition() + camera.transform.getRight().normalize()*scalar);
		break;
	case GLFW_KEY_Q:
		z += 4;
		break;
	case GLFW_KEY_S:
		z -= 4;
		break;
	case GLFW_KEY_R:
		camera.setPosition(Math::Vector3(100, 100, 100));
		break;
	default:
		break;
	}
	//view = Math::Matrix::lookAt(Math::Vector3(x, y, z), Math::Vector3(0, 0, 0), Math::Vector3(0, 1, 0));
}

GLuint genShader(const char* source, GLenum shaderType) {
	//create shader obj
	GLuint shader = glCreateShader(shaderType);
	//apply source
	glShaderSource(shader, 1, &source, NULL);
	//compile shader
	glCompileShader(shader);
	GLint compilePass;
	GLchar infoBuffer[512] = { 0 };
	//query if compile passed
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compilePass);
	//compile fails
	if (!compilePass) 
	{
		glGetShaderInfoLog(shader, 512, NULL, infoBuffer);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoBuffer << std::endl;
		return 0;
	}
	return shader;
}

GLuint genGLProgram() {
	GLuint program = glCreateProgram();
	GLuint vertexShader = genShader(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fragShader = genShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	if (vertexShader == 0 || fragShader == 0) {
		return 0;
	}
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	//ready to link
	glLinkProgram(program);
	//query link result
	GLint linkPass;
	glGetProgramiv(program, GL_LINK_STATUS, &linkPass);
	GLchar info[512] = { 0 };
	if (!linkPass)
	{
		glGetProgramInfoLog(program, 512, NULL, info);
		std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << info << std::endl;
		return 0;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	return program;
}


int main()
{
	//Ueuos::GLProgramHelper::getInstance();
	//return 0;
	QuaternionUnitTest();
	
	//Vector3UnitTest();
	//QuaternionUnitTest();
	//TransformUnitTest();
	//ViewMatrixUnitTest();
	//return 1;
	//Ueuos::TargetCamera camera = Ueuos::TargetCamera();
	//camera.setPosition(Math::Vector3(0, 0, 100));
	//camera.lookAt(Math::Vector3(0, 0, 0));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Uouos3D Ver.-1.0", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);  
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	


	GLuint glPro = genGLProgram();


	Ueuos::Cube cube;
	Ueuos::Axis axis;
	Ueuos::Grid grid(55,30);
	cube.setScale(Math::Vector3(30, 30, 30));
	cube.setPostion(Math::Vector3(30, 0, 30));
	axis.setScale(Math::Vector3(10000, 10000, 10000));
	Math::Matrix p1 = Math::Matrix::createPerspective(45, 800.0f / 600.0f, 0.1,10000);
	camera.setProjectionMatrix(p1);
	float rot = 0.0f;
	float y = 0.0;
	Ueuos::World world;

	while (!glfwWindowShouldClose(window))
	{
		y = y + 0.0001;

		float camX = sin(y)*100;
		float camZ = cos(y) * 100;
		camera.lookAt(camera.transform.getForward());
		
		glEnable(GL_DEPTH_TEST);
	//	glDepthFunc(GL_LESS);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
		//glCullFace(GL_BACK);
		
		glfwPollEvents();
		//glLineWidth(10);
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		//glUseProgram(glPro);		

	
		//for (vector<AbstractDrawCommand*>::iterator it = renderVector.begin(); it != renderVector.end(); ++it) {
		//GLint mvLoc = glGetUniformLocation(glPro, "pv");
		//	GLint projLoc = glGetUniformLocation(glPro, "projection");
			//GLint viewLoc = glGetUniformLocation(glPro, "view");
		//	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, (GLfloat*)&camera.getViewProjMat());
			

			//glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, (GLfloat*)&grid.getModelMatrix());
		//	grid.draw();

		//	glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, (GLfloat*)&axis.getModelMatrix());
		//	axis.draw();
		//	Math::Transform cubeFakeParentModelMatrix = Math::Transform();
		//	cubeFakeParentModelMatrix.doRotate(Math::Vector3(0, 0, 0));
		//	//cubeFakeParentModelMatrix.doScale(Math::Vector3(0.1, .1, .1));

		//	//cubeFakeParentModelMatrix.doTranslate(Math::Vector3(30,0, 30));
		//	Math::Matrix mat = cube.getModelMatrix()*cubeFakeParentModelMatrix.getModelMatrix();
			//GLint tranformLoc = glGetUniformLocation(glPro, "transform");
			//glUniformMatrix4fv(tranformLoc, 1, GL_FALSE, (GLfloat*)&mat);
		////	cube.setPostion(cube.getPosition() + cube.getTransform().getRight()*0.01);
		//	//cube.setRotation(Math::Vector3(0, y, 0));
		//	cube.draw();
			world.draw();


			//(*it)->rotate(Math::Vector3(rot,-rot, rot));
			//(*it)->doDraw();
		//}

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}


void printVector2(Math::Vector2 vec) {
	cout <<"(" << vec.x << "," << vec.y << ")" << endl;
}

void printVector3(Math::Vector3 vec) {
	cout << "(" << vec.x << ", " << vec.y<<", "<<vec.z<< ")" << endl;
}

void printVector3AsEuler(Math::Vector3 rot) {
	char buffer[128] = { 0 };
	sprintf(buffer,"X:%f \nY:%f\nZ:%f\n",RADIANS_TO_DEGREES(rot.x),RADIANS_TO_DEGREES(rot.y),RADIANS_TO_DEGREES(rot.z));
	cout << buffer << endl;
}

void Vector2UnitTest() {
	Math::Vector2 v1(1, 1);
	cout << "Vector2 v1(1,1)\n";
//	cout << "V1 Mag:";
	//cout << v1.magnitude() << endl;
	//cout << "Normalizing:";
	//cout << v1.normalize().magnitude() << endl;
	Math::Vector2 v2(1, -1);
	cout << "Vector2 v1(1,-1)\n";
	cout << "v1+v2 : ";
	printVector2(v1 + v2);
	cout << "v1-v2 : ";
	printVector2(v1 - v2);

	cout << "Mul Vector by real number: v1*3";
	printVector2(v1 * 3);
	cout << "Mul Vector by real number : 3*v1";
	printVector2(3 * v1);

	cout << "Lerp from v1 to v2 at 0.3:";
	printVector2(Math::Vector2::lerp(v1, v2, 0.3));
	cout << "Lerp from v1 to v2 at 0.5:";
	printVector2(Math::Vector2::lerp(v1, v2, 0.5));
	cout << "Lerp from v1 to v2 at 0.7:";
	printVector2(Math::Vector2::lerp(v1, v2, 0.7));

	cout << "Dot product of v1 and v2: ";
	cout<<(Math::Vector2::dot(v1, v2))<<endl;

	cout << "Angle:";
	cout << Math::Vector2::angle(v1, v2) << endl;  ;
	
	Math::Vector2 normal(0, 1);
	Math::Vector2 incoming(-1, -1);
	cout << "reflect : ";
	printVector2(Math::Vector2::reflect(incoming, normal));
}

void printMatrix(Math::Matrix mat) {
	cout << "=====================\n";
	for (int i = 0; i < 16; i++)
	{
		if (i > 0 && i % 4 == 0)
		{
			cout << endl;
		}
		printf("%.1f  ", mat[i]);
	}
	cout << "\n=====================\n";
}

void Vector3UnitTest() {
	cout << "=====================================\n";
	using  Math::Vector3;
	//Vector3 forward = Vector3::forward;
	//cout << "V1";
	//printVector3(forward);
	//Vector3 right = Vector3::right;
	//cout << "V2";
	//printVector3(right);

	//Vector3 up = Vector3::cross(forward, right);
	//cout << "Cross Product:";
	//printVector3(up);

	//float upDownDelta = Vector3::angle(Vector3::up, Vector3::down);
	//cout << "Angle :" << upDownDelta << endl;

	//Vector3 RtoU = Vector3::cross(Vector3::right, Vector3::up);
	//cout << "RtoU";
	//printVector3(RtoU);

	//Vector3 UtoR = Vector3::cross(Vector3::up, Vector3::right);
	//cout << "UtoR";
	//printVector3(UtoR);

	//Vector3 FtoR = Vector3::cross(Vector3::forward, Vector3::right);
	//cout << "FtoR";
	//printVector3(FtoR);

	//float sAF2R = Vector3::signedAngle(Vector3::forward, Vector3::right);
	//cout << (sAF2R) << endl;;

	//float sAF2L = Vector3::signedAngle(Vector3::forward, Vector3::left);
	//cout << (sAF2L) << endl;;

	//float sAR2L = Vector3::signedAngle(Vector3::right, Vector3::left);
	//cout << (sAR2L) << endl;;

	//float sAL2R = Vector3::signedAngle(Vector3(-1,0,0), Vector3::right);
	//cout << (sAL2R) << endl;;
}

void QuaternionUnitTest() {
	using Math::Vector3;
	using Math::Quaternion;
	using Math::Matrix;

	//Quaternion quat(0, 0, 0.577, 0.817);
	//Vector3 euler = Quaternion::euler(quat);

	Quaternion eulerQuat(Vector3(40, -65, 23));
	Vector3 euler1 = Quaternion::euler(eulerQuat);
	//Matrix mat = eulerQuat.getRotationMatrix();
	printVector3AsEuler(euler1);
}

void printTransform(Math::Transform trans) {
	Math::Matrix mat = trans.getModelMatrix();
	printMatrix(mat);
}

void TransformUnitTest() {
	using namespace Math;
	using Math::Vector3;
	Math::Transform testTrans = Math::Transform();
	testTrans.doTranslate(Math::Vector3(1, 1, 1));
	testTrans.doScale(Vector3(2, 2, 2));
	testTrans.doRotate(Vector3(0, 180, 0));
	printTransform(testTrans);
}


void ViewMatrixUnitTest() {
	using namespace Math;
	using Math::Vector3;
	Matrix viewMat = Matrix::lookAt(Vector3(0, 0,10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	printMatrix(viewMat);
}

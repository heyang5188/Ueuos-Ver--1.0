
#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <queue>


////#include "AbstractDrawCommand.h"
#include "DrawCommand/TriangeCommand.h"
#include "DrawCommand/QuadCommand.h"
//#include "Math/Vector2.h"
//#include "Math/Vector3.h"
#include "UMath.h"

//TEST 
void Vector2UnitTest();
void Vector3UnitTest();
//

float trs[] = {
	1.0,0.0,0.0,0.1,
	0.0,1.2,0.0,0.3,
	0.0,0.0,1.0,0.0,
	0.0,0.0,0.0,1.0
};


using namespace std;
vector<AbstractDrawCommand*> renderVector;

const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec4 color;\n"
"uniform mat4 transform;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"gl_Position = transform*vec4(position.x, position.y, position.z, 1.0);\n"
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 当用户按下ESC键,我们设置window窗口的WindowShouldClose属性为true
	// 关闭应用程序
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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

	Vector3UnitTest();

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

	TriangeCommand tc = TriangeCommand();
	VertexInfo v1 = VertexInfo(-0.5f, -0.5f, 0.0f,1.0,0.0,0.0);
	VertexInfo v2 = VertexInfo(0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0);
	VertexInfo v3 = VertexInfo(0.0f, 0.5f, -1.0f, 0.0, 0.0, 1.0);
	vector<VertexInfo> data{v1,v2,v3};
	tc.setVertexData(data);
	QuadCommand quad = QuadCommand(Vector3(-0.5, 0.5), Vector3(-0.5, -0.5), Vector3(0.5, 0.5), Vector3(0.5, -0.5));
	renderVector.push_back(&quad);
	renderVector.push_back(&tc);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(glPro);		
		GLint tranformLoc = glGetUniformLocation(glPro,"transform");
		glUniformMatrix4fv(tranformLoc,1,GL_TRUE,(GLfloat*)trs);
		for (vector<AbstractDrawCommand*>::iterator it = renderVector.begin(); it != renderVector.end(); ++it) {
			(*it)->doDraw();
		}

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
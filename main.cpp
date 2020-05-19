
#include <iostream>
#include <sstream>
#include <string>
#define GLEW_STATIC
#include "GL/glew.h"	// Important - this header must come before glfw3 header
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "OpenGLCubeMesh.h"
#include "GrainGrowth.h"
#include <windows.h>
#include <time.h>

using namespace std;

// Global Variables
const char* APP_TITLE = "Introduction to Modern OpenGL - Camera";
int gWindowWidth = 1024;
int gWindowHeight = 768;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;
bool rotationFlag = true;
float cubeAngle = 0.0f;
glm::vec3 cubePos;
const std::string texture1 = "textures/wooden_crate.jpg";

// Function prototypes
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void showFPS(GLFWwindow* window);
bool initOpenGL();

//-----------------------------------------------------------------------------
// Main Application Entry Point
//-----------------------------------------------------------------------------
int main()
{
	if (!initOpenGL())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return -1;
	}
	

	/*************************************************************/
	/*                      LOAD FROM GUI                        */
	/*************************************************************/
	int x = 35;
	int y = 35;
	int z = 35;
	int number_of_grains = 400;
	double probability = 0.9;
	
	cout << "X space size: ";
	cin >> x;
	cout << "Y space size: ";
	cin >> y;
	cout << "Z space size: ";
	cin >> z;
	cout << "Number of grains: ";
	cin >> number_of_grains;
	cout << "Probability: ";
	cin >> probability;



	/*************************************************************/
	/*                 GENERATE CUBE VERTICES                    */
	/*************************************************************/
	int n = x * y * z * 108;
	OpenGLCubeMesh m1 = OpenGLCubeMesh(x, y, z, 0.0);
	m1.normalizeVertices();
	int i = 0;
	float * vert_pos = m1.getVertices();

	/*************************************************************/
	/*                 GENERATE CUBE COLORS                      */
	/*************************************************************/
	srand(time(NULL));
	GrainGrowth g1 = GrainGrowth(x+2, y+2, z+2, number_of_grains, probability);
	g1.randomizeGrain();
	//g1.printMatrix();
	g1.startGrowth();
	//g1.saveToFile();
	//g1.printMatrix();
	//float* vert_colors = g1.getColors();
	float* vert_colors = g1.getNormalizedColorsAmount();






	





	// Cube position
	cubePos = glm::vec3(0.0f, 0.0f, -4.0f);



	// 2. Set up buffers on the GPU
	GLuint vbo, vbo2, vao;

	glGenBuffers(1, &vbo);					// Generate an empty vertex buffer on the GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);		// "bind" or set as the current buffer we are working with
	glBufferData(GL_ARRAY_BUFFER, n*sizeof(float), vert_pos, GL_STATIC_DRAW);	// copy the data from CPU to GPU

	glGenBuffers(1, &vbo2);																// Generate an empty vertex buffer on the GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);												// "bind" or set as the current buffer we are working with
	glBufferData(GL_ARRAY_BUFFER, x*y*z*4*36* sizeof(float), vert_colors, GL_STATIC_DRAW);	// copy the data from CPU to GPU
	

	
	// The vertex array object (VAO) is a little descriptor that defines which data from vertex buffer objects should be used as input 
	// variables to vertex shaders.
	glGenVertexArrays(1, &vao);									// Tell OpenGL to create new Vertex Array Object
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);							// Make the position buffer the current one
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);	// Define a layout for the first vertex buffer "0"
	glEnableVertexAttribArray(0);								// Enable the first attribute or attribute "0"






	// Now bind the color VBO and set the vertix attrib pointer
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);						// Make the color buffer the current one, now
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);	// Define a layout for the second vertex buffer "1"
	glEnableVertexAttribArray(1);								// Enable the first attribute or attribute "1"

	

	ShaderProgram shaderProgram;
	shaderProgram.loadShaders("shaders/basic.vert", "shaders/basic.frag");

	double lastTime = glfwGetTime();
	

	// Rendering loop
	while (!glfwWindowShouldClose(gWindow))
	{
		showFPS(gWindow);

		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		// Poll for and process events
		glfwPollEvents();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		glm::mat4 model(1.0), view(1.0), projection(1.0);

		// Update the cube position and orientation.  Rotate first then translate
		
		if (rotationFlag)
		{
			cubeAngle += (float)(deltaTime * 20.0f);
			if (cubeAngle >= 360.0f) cubeAngle = 0.0f;
		}
		
		// Rotates around the cube center
		model = glm::translate(model, cubePos) * glm::rotate(model, glm::radians(cubeAngle), glm::vec3(0.0f, 1.0f, 0.0f));

		// Uncomment this line and comment the one above to flip the transformation of the cube.  Watch what happens!
		// Rotates around??
		//model = glm::rotate(model, glm::radians(cubeAngle), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(model, cubePos);

		glm::vec3 camPos(0.0f, 0.0f, 0.0f);
		glm::vec3 targetPos(0.0f, 0.0f, -1.0f);
		glm::vec3 up(0.0f, 1.0f, 0.0f);

		// Create the View matrix
		view = glm::lookAt(camPos, camPos + targetPos, up);

		// Create the projection matrix
		projection = glm::perspective(glm::radians(45.0f), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 100.0f);

		// Must be called BEFORE setting uniforms because setting uniforms is done
		// on the currently active shader program.
		shaderProgram.use();

		// Pass the matrices to the shader
		shaderProgram.setUniform("model", model);
		shaderProgram.setUniform("view", view);
		shaderProgram.setUniform("projection", projection);
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, x*y*z*36);
		glBindVertexArray(0);

		// Swap front and back buffers
		glfwSwapBuffers(gWindow);

		lastTime = currentTime;
	}

	// Clean up
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();

	return 0;
}

//-----------------------------------------------------------------------------
// Initialize GLFW and OpenGL
//-----------------------------------------------------------------------------
bool initOpenGL()
{
	// Intialize GLFW
	// GLFW is configured.  Must be called before calling any GLFW functions
	if (!glfwInit())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// forward compatible with newer versions of OpenGL as they become available but not backward compatible (it will not run on devices that do not support OpenGL 3.3

	// Create an OpenGL 3.3 core, forward compatible context window
	gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	if (gWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make the window's context the current one
	glfwMakeContextCurrent(gWindow);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	// Set the required callback functions
	glfwSetKeyCallback(gWindow, glfw_onKey);
	glfwSetFramebufferSizeCallback(gWindow, glfw_onFramebufferSize);

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	// Define the viewport dimensions
	glViewport(0, 0, gWindowWidth, gWindowHeight);
	glEnable(GL_DEPTH_TEST);

	return true;
}

//-----------------------------------------------------------------------------
// Is called whenever a key is pressed/released via GLFW
//-----------------------------------------------------------------------------
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		gWireframe = !gWireframe;
		if (gWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
	{
		rotationFlag = !rotationFlag;
	}
	if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
	{
		
		cubeAngle = 180.0f;
	}
	if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
	{

		cubeAngle = 65.0f;
	}

}

//-----------------------------------------------------------------------------
// Is called when the window is resized
//-----------------------------------------------------------------------------
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
	gWindowWidth = width;
	gWindowHeight = height;
	glViewport(0, 0, gWindowWidth, gWindowHeight);
}

//-----------------------------------------------------------------------------
// Code computes the average frames per second, and also the average time it takes
// to render one frame.  These stats are appended to the window caption bar.
//-----------------------------------------------------------------------------
void showFPS(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); // returns number of seconds since GLFW started, as double float

	elapsedSeconds = currentSeconds - previousSeconds;

	// Limit text updates to 4 times per second
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		// The C++ way of setting the window title
		std::ostringstream outs;
		outs.precision(3);	// decimal places
		outs << std::fixed
			<< APP_TITLE << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		// Reset for next average.
		frameCount = 0;
	}

	frameCount++;
}

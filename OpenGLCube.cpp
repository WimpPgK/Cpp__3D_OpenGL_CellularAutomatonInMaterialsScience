#include "OpenGLCube.h"

OpenGLCube::OpenGLCube()
{
    //ctor

    float pom[] = {
		// front face
		-1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f, 
		 1.0f,  1.0f,  1.0f, 
		-1.0f,  1.0f,  1.0f, 
		-1.0f, -1.0f,  1.0f, 
		 1.0f, -1.0f,  1.0f, 

		// back face
		-1.0f,  1.0f, -1.0f, 
		 1.0f, -1.0f, -1.0f, 
		 1.0f,  1.0f, -1.0f, 
		-1.0f,  1.0f, -1.0f, 
		-1.0f, -1.0f, -1.0f, 
		 1.0f, -1.0f, -1.0f, 

		// left face
		-1.0f,  1.0f, -1.0f, 
		-1.0f, -1.0f,  1.0f, 
		-1.0f,  1.0f,  1.0f, 
		-1.0f,  1.0f, -1.0f, 
		-1.0f, -1.0f, -1.0f, 
		-1.0f, -1.0f,  1.0f, 

		// right face
		 1.0f,  1.0f,  1.0f, 
		 1.0f, -1.0f, -1.0f, 
		 1.0f,  1.0f, -1.0f, 
		 1.0f,  1.0f,  1.0f, 
		 1.0f, -1.0f,  1.0f, 
		 1.0f, -1.0f, -1.0f, 

		 // top face
		-1.0f,  1.0f, -1.0f, 
		 1.0f,  1.0f,  1.0f, 
		 1.0f,  1.0f, -1.0f, 
		-1.0f,  1.0f, -1.0f, 
		-1.0f,  1.0f,  1.0f, 
		 1.0f,  1.0f,  1.0f, 

		 // bottom face
		-1.0f, -1.0f,  1.0f, 
		 1.0f, -1.0f, -1.0f, 
		 1.0f, -1.0f,  1.0f, 
		-1.0f, -1.0f,  1.0f, 
		-1.0f, -1.0f, -1.0f, 
		 1.0f, -1.0f, -1.0f, 
    };
    for(int i = 0 ; i < 108 ; i++)
    {
        vertices[i] = pom[i];
    }

}

void OpenGLCube::setPosition(float x, float y, float z)
{
    int i;
	for(i = 0 ; i < 108 ; i+= 3)
    {
       vertices[i] +=  x;
       vertices[i+1] +=  y;
       vertices[i+2] +=  z;
    }
}



OpenGLCube::~OpenGLCube()
{
    //dtor
}


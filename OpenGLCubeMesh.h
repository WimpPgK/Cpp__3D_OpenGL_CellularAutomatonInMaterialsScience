#ifndef OPENGLCUBEMESH_H
#define OPENGLCUBEMESH_H


class OpenGLCubeMesh
{
    public:
        int x;
		int y;
		int z;
		float gap;

		float* vertices;




        OpenGLCubeMesh(int, int, int, float);
        void saveToFile();
        void printVertices();
		void normalizeVertices();
		float* getVertices();

        ~OpenGLCubeMesh();


    protected:

    private:
};

#endif // OPENGLCUBEMESH_H

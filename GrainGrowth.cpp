#include "GrainGrowth.h"
#include "Grain.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

GrainGrowth::GrainGrowth(int x, int y, int z, int number_of_inclusioin, double probability)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->number_of_inclusioin = number_of_inclusioin;
	this->probability = probability;

    int i = 0;
    int j = 0;
    int k = 0;

    id = new Id[number_of_inclusioin];
    matrix01 = new Grain**[x];
    matrix02 = new Grain**[x];

    for(i = 0 ; i < x ; i++)
    {
        matrix01[i] = new Grain*[y];
        matrix02[i] = new Grain*[y];
        for(j = 0 ; j < y ; j++)
        {
            matrix01[i][j] = new Grain[z];
            matrix02[i][j] = new Grain[z];
        }
    }
    //double licznik = 0;
    for(i = 0 ; i < x ; i++)
    {
        for(j = 0 ; j < y ; j++)
        {
            for(k = 0 ; k < z ; k++)
            {
                matrix01[i][j][k].setPosition(i,j,k);
				matrix01[i][j][k].id = 0;
				matrix02[i][j][k].id = 0;
            }
        }
    }
}


void GrainGrowth::randomizeGrain()
{
    srand(time(NULL));
    int i;
    // initialization of id tab for inclusion
    for(i = 0 ; i < number_of_inclusioin ; i++)
    {
        id[i].SetColor((double)rand()/(RAND_MAX), (double)rand()/(RAND_MAX), (double)rand()/(RAND_MAX), 1);
        //cout << &id[i] << endl;
        //cout << id[i].color_r << "  " << id[i].color_g << "   " <<  id[i].color_b <<"  " << id[i].alpha<< endl;

    }
    // set random position for inclusion
    for(i = 0 ; i < number_of_inclusioin ; i++)
    {
        int random_x_position = rand()%x;
        int random_y_position = rand()%y;
        int random_z_position = rand()%z;
        //cout << random_x_position << endl;
        matrix01[random_x_position][random_y_position][random_z_position].setId(&id[i]);
    }
}


void GrainGrowth::startGrowth()
{
    int i,j,k;
    Neighbourhood n1;
   

    bool process = true;
    int counter = 0;
    while(process)    // 1 msc step
    {
        process =  false;
        for(i = 0 ; i < x ; i++)
        {
            for(j = 0 ; j < y ; j++)
            {
                for(k = 0 ; k < z ; k++)
                {
                    matrix02[i][j][k].alpha = matrix01[i][j][k].alpha;
                    matrix02[i][j][k].color_b = matrix01[i][j][k].color_b;
                    matrix02[i][j][k].color_g = matrix01[i][j][k].color_g;
                    matrix02[i][j][k].color_r = matrix01[i][j][k].color_r;
                    matrix02[i][j][k].id = matrix01[i][j][k].id;
                    matrix02[i][j][k].position_x = matrix01[i][j][k].position_x;
                    matrix02[i][j][k].position_y = matrix01[i][j][k].position_y;
                }
            }
        }

        for(i = 1 ; i + 1 < x ; i++)
        {
            for(j = 1 ; j + 1 < y  ; j++)
            {
                for(k = 1 ; k + 1 < z  ; k++)
                {
                    //if(n1.getBestNeighbour(i,j,k,matrix02)== 0)
                    if(matrix01[i][j][k].id == 0)
                    {
						//cout << "i " << i << "  j  " << j << "   k   " << k << endl;
                        process = true;
                    }
                    matrix01[i][j][k].id = n1.getBestNeighbour(i,j,k,matrix02);
                    //n1.getBestNeighbour(i,j,k,matrix02);
                    //cout << matrix01[i][j][k].id  << endl;
                }
            }
        }
        //printMatrix();
        //cout << "*********************************************" << endl;
        counter ++;
        cout << "Iteracja: " << counter << endl;

    }


}








//********************************************************************************************************/

void GrainGrowth::printMatrix()
{
    int i,j,k;

	//delete[] id;
    for(i = 0 ; i < x ; i++)
    {
        for(j = 0 ; j < y ; j++)
        {
            for(k = 1 ; k < z ; k++)
            {
                if(matrix01[i][j][k].id != 0)
                {
                   cout << matrix01[i][j][k].id  <<" " ;
                }
                else
                {
                    cout << matrix01[i][j][k].id << " ";
                }

            }
            cout << endl;
        }

        cout << endl << endl <<endl;
    }
}


// return (r,g,b,alpha) for every cube
// 1 cube contain only 1 rgba
float* GrainGrowth::getColors()
{
	float* colors = new float[x * y * z * 4];
	int counter = 0;
	int i, j, k;
	for (i = 1; i + 1 < x; i++)
	{
		for (j = 1; j + 1 < y; j++)
		{
			for (k = 1;k + 1 < z; k++)
			{
				colors[counter] = matrix01[i][j][k].id->color_r;
				colors[counter+1] = matrix01[i][j][k].id->color_g;
				colors[counter+2] = matrix01[i][j][k].id->color_b;
				colors[counter + 3] = matrix01[i][j][k].id->alpha;
				counter += 4;
			}
		}
	}
	return colors;

}


// 1 cube is is build with 36 triangles
// our logic is build for cube build from 1 point
// if we want to cerate OpenGl buffer we ned to define
// every triangle point
float* GrainGrowth::getNormalizedColorsAmount()
{
	float* colors = new float[x * y * z * 4*36];
	int counter = 0;
	int i, j, k, m;
	for (i = 1; i + 1 < x; i++)
	{
		for (j = 1; j + 1 < y; j++)
		{	
			for (k = 1; k + 1 < z; k++)
			{
				for (m = 0; m < 36; m++)
				{	

					try
					{
						
						colors[counter] = matrix02[i][j][k].id->color_r;
						colors[counter + 1] = matrix02[i][j][k].id->color_g;
						colors[counter + 2] = matrix02[i][j][k].id->color_b;
						colors[counter + 3] = matrix02[i][j][k].id->alpha;
						counter += 4;
					}
					catch(string blad)
					{
						cout << "Blad pamieci " << endl;
						colors[counter] = 1;
						colors[counter + 1] = 1;
						colors[counter + 1] = 1;
						colors[counter + 1] = 1;
					}

					
				}

			}
			
		}
	}
	cout << "*****************  " << counter << endl;
	return colors;
}



void GrainGrowth::saveToFile()
{
	FileOperatorColor f1;
	f1.saveToFile(matrix01, x, y, z);

}

GrainGrowth::~GrainGrowth()
{
	
	int i = 0;
	int j = 0;
	int k = 0;

	/*
	for (i = 0; i < y; i++)
	{
		for (j = 0; j < z; j++)
		{
			delete [] matrix01[i][j];
			delete [] matrix02[i][j];
		}
	}

	for (i = 0; i < x; i++)
	{
		delete [] matrix01[i];
		delete [] matrix02[i];
		
	}
	delete matrix01;
	delete matrix02;
	*/
}
#include "FileOperatorColor.h"
#include<iostream>
#include<fstream>

using namespace std;


FileOperatorColor::FileOperatorColor()
{

}

void FileOperatorColor::saveToFile(Grain*** matrix, int x, int y, int z)
{
	ofstream file("color.txt");
	int i,j,k;
	for (i = 1; i + 1 < x; i++)
	{
		for (j = 1; j + 1 < y; j++)
		{
			for (k = 1;k + 1 < z; k++)
			{
				file << matrix[i][j][k].id->color_r << " ";
				file << matrix[i][j][k].id->color_g << " ";
				file << matrix[i][j][k].id->color_b << " ";
				file << matrix[i][j][k].id->alpha <<endl;

			}
		}
	}
}

FileOperatorColor::~FileOperatorColor()
{

}

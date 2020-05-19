#include "FileOperator.h"
#include<iostream>
#include<fstream>

using namespace std;


FileOperator::FileOperator()
{

}

void FileOperator::saveToFile(float* vertices, int n)
{
    ofstream file("model.txt");
    int i;
    for(i = 0 ; i < n ; i++)
    {
        file << vertices[i] << " ";
        if((i+1)%4 == 0)
        {
            file << endl;
        }
    }
    file.close();

}

FileOperator::~FileOperator()
{

}

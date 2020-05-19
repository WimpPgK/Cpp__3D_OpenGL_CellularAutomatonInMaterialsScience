#include "Neighbourhood.h"
using namespace std;
#include <windows.h>
#include <time.h>


Neighbourhood::Neighbourhood()
{
    int i;
    for(i = 0 ; i < 26 ; i++)
    {

    }
}
void mostFrequentValue_NaiveAlgorithm(Id**);



Id* Neighbourhood::getBestNeighbour(int x, int y, int z, Grain*** matrix)
{

    int licznik;
	Id* returnValue;
    
	

	//create moore tab
	//check neighbour
	Moore m1 = Moore();
	pom = m1.GetNeighborTab(x, y, z, matrix);
	returnValue = mostFrequentValue_NaiveAlgorithm(pom, 26, 20);
	if (returnValue != 0)
	{	
		//cout << "warunek1" << endl;
		return returnValue;
	}
	



	//create nearest moore
	//check neighbour
	NearestMoore n1 = NearestMoore();
	pom = n1.GetNeighborTab(x, y, z, matrix);
	returnValue = mostFrequentValue_NaiveAlgorithm(pom, 6, 4);
	if (returnValue != 0)
	{	
		//cout << "warunek2" << endl;
		return returnValue;
	}
	


	
	//create further moore
	//check neighbour
	FurtherMoore f1 = FurtherMoore();
	pom = f1.GetNeighborTab(x, y, z, matrix);
	returnValue = mostFrequentValue_NaiveAlgorithm(pom, 20, 16);
	if (returnValue != 0)
	{
		//cout << "warunek3" << endl;
		return returnValue;
	}
	


	

	
	// CONDITION 4
	//double randomValue = double(rand()/(RAND_MAX));
	//cout << randomValue << endl;
	Moore m2 = Moore();
	
	
	double probability = 0.1;



	if (double(rand() / (RAND_MAX)) < probability)
	{
		//cout << "warunek4" << endl;
		pom = m2.GetNeighborTab(x, y, z, matrix);
		return mostFrequentValue_NaiveAlgorithm(pom, 26, 0);
		
	}







	//create futher moore
	//check neighbour
	//chance of change


  

       

    



    //cout << mostFrequentValue_NaiveAlgorithm(pom)  << "  ";
    return 0;
}


Id* Neighbourhood::mostFrequentValue_NaiveAlgorithm(Id** tab, int n, int minFreq)
{
    int i,j;
    int counter = 0;
    int maxValue = 0;
    Id* mostFrequent = 0;
    Id* pom = 0;


    for(i = 0 ; i < n ; i++)
    {
        pom = tab[i];
        for (j = 0 ; j < n ; j++)
        {
            if(pom == tab[j] && tab[j] != 0)
            {
                //cout <<"counter dziala" << endl;
                counter++;
            }
        }
        if(counter > maxValue)
        {
            maxValue = counter;
            mostFrequent = pom;
        }
        counter = 0;

    }

	delete[] tab;

    if(mostFrequent != 0 && maxValue >= minFreq)
    {

		return mostFrequent;    //cout << mostFrequent << "AAA" << endl;
        

    }
	return 0;

}



Neighbourhood::~Neighbourhood()
{
	cout << "kasuje" << endl;
}

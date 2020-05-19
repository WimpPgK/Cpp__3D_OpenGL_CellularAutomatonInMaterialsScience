#include "NearestMoore.h"

NearestMoore::NearestMoore()
{
	pom = new Id * [6];
}

Id** NearestMoore::GetNeighborTab(int x, int y, int z, Grain*** matrix)
{

	// over the grain
	pom[0] = matrix[x][y][z + 1].getId();
	
	// on the same level
	pom[1] = matrix[x][y+1][z].getId();
	pom[2] = matrix[x][y-1][z].getId();
	pom[3] = matrix[x+1][y][z].getId();
	pom[4] = matrix[x-1][y][z].getId();
	
	// under the grain
	pom[5] = matrix[x][y][z - 1].getId();
	
	return pom;
}


NearestMoore::~NearestMoore()
{
}

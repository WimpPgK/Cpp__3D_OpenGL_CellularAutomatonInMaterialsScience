#include "FurtherMoore.h"

FurtherMoore::FurtherMoore()
{
	pom = new Id * [20];
}


Id** FurtherMoore::GetNeighborTab(int x, int y, int z, Grain*** matrix)
{

	//over the grain
	pom[0] = matrix[x + 1][y + 1][z + 1].getId();
	pom[1] = matrix[x + 1][y][z + 1].getId();
	pom[2] = matrix[x + 1][y - 1][z + 1].getId();
	pom[3] = matrix[x][y + 1][z + 1].getId();
	pom[4] = matrix[x][y - 1][z + 1].getId();
	pom[5] = matrix[x - 1][y + 1][z + 1].getId();
	pom[6] = matrix[x - 1][y][z + 1].getId();
	pom[7] = matrix[x - 1][y - 1][z + 1].getId();

	// on the same level
	pom[8] = matrix[x + 1][y + 1][z].getId();
	pom[9] = matrix[x + 1][y - 1][z].getId();
	pom[10] = matrix[x - 1][y + 1][z].getId();
	pom[11] = matrix[x - 1][y - 1][z].getId();


	// under the grain
	pom[12] = matrix[x + 1][y + 1][z - 1].getId();
	pom[13] = matrix[x + 1][y][z - 1].getId();
	pom[14] = matrix[x + 1][y - 1][z - 1].getId();
	pom[15] = matrix[x][y + 1][z - 1].getId();
	pom[16] = matrix[x][y - 1][z - 1].getId();
	pom[17] = matrix[x - 1][y + 1][z - 1].getId();
	pom[18] = matrix[x - 1][y][z - 1].getId();
	pom[19] = matrix[x - 1][y - 1][z - 1].getId();

	return pom;
}

FurtherMoore::~FurtherMoore()
{
}

#include "Moore.h"
#include "Id.h"
#include "Grain.h"

Moore::Moore()
{
	//over the grain
	pom = new Id*[26];

}

Id** Moore::GetNeighborTab(int x, int y, int z, Grain*** matrix)
{
	
	pom[0] = matrix[x + 1][y + 1][z + 1].getId();
	pom[1] = matrix[x + 1][y][z + 1].getId();
	pom[2] = matrix[x + 1][y - 1][z + 1].getId();
	pom[3] = matrix[x][y + 1][z + 1].getId();
	pom[4] = matrix[x][y][z + 1].getId();
	pom[5] = matrix[x][y - 1][z + 1].getId();
	pom[6] = matrix[x - 1][y + 1][z + 1].getId();
	pom[7] = matrix[x - 1][y][z + 1].getId();
	pom[8] = matrix[x - 1][y - 1][z + 1].getId();

	// on the same level
	pom[9] = matrix[x + 1][y + 1][z].getId();
	pom[10] = matrix[x + 1][y][z].getId();
	pom[11] = matrix[x + 1][y - 1][z].getId();
	pom[12] = matrix[x][y + 1][z].getId();
	pom[13] = matrix[x][y - 1][z].getId();
	pom[14] = matrix[x - 1][y + 1][z].getId();
	pom[15] = matrix[x - 1][y][z].getId();
	pom[16] = matrix[x - 1][y - 1][z].getId();


	// under the grain
	pom[17] = matrix[x + 1][y + 1][z - 1].getId();
	pom[18] = matrix[x + 1][y][z - 1].getId();
	pom[19] = matrix[x + 1][y - 1][z - 1].getId();
	pom[20] = matrix[x][y + 1][z - 1].getId();
	pom[21] = matrix[x][y][z - 1].getId();
	pom[22] = matrix[x][y - 1][z - 1].getId();
	pom[23] = matrix[x - 1][y + 1][z - 1].getId();
	pom[24] = matrix[x - 1][y][z - 1].getId();
	pom[25] = matrix[x - 1][y - 1][z - 1].getId();

	return pom;
}

Moore::~Moore()
{

}

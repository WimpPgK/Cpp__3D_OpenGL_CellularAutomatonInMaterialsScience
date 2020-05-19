#include "Id.h"
#include "Grain.h"
#pragma once
class NearestMoore
{		
	public:
			Id** pom;
		
			NearestMoore();
			Id** GetNeighborTab(int x, int y, int z, Grain*** matrix);
			virtual ~NearestMoore();
};


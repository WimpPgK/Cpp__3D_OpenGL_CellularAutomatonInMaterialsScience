#include "Id.h"
#include "Grain.h"
#pragma once
class FurtherMoore
{
	public:
		FurtherMoore();

		Id** pom;
		Id** GetNeighborTab(int x, int y, int z, Grain*** matrix);

		virtual ~FurtherMoore();
};


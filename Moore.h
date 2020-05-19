#pragma once
#include "Id.h"
#include "Grain.h"
class Moore
{
	public:
		Id** pom;

		Moore();
		Id** GetNeighborTab(int x, int y, int z, Grain*** matrix);
		virtual ~Moore();

};


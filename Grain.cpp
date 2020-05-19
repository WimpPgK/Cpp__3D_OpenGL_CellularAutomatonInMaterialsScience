#include "Grain.h"

Grain::Grain()
{
    id = 0;
    position_x = -1;
    position_y = -1;
    position_z = -1;
	alpha = -1;

}

void Grain::setPosition(int position_x, int position_y, int position_z)
{
    this->position_x = position_x;
    this->position_y = position_y;
    this->position_z = position_z;
}
void Grain::setId(Id* id)
{
    this->id = id;
}

Id* Grain::getId()
{
    return id;
}

Grain::~Grain()
{

}

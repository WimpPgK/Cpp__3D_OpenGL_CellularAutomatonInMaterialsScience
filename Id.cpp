#include "Id.h"

Id::Id()
{
    this->color_r = 0;
    this->color_g = 0;
    this->color_b = 0;
	
}

void Id::SetColor(double color_r, double color_g, double color_b, double alpha)
{
    this->color_r = color_r;
    this->color_g = color_g;
    this->color_b = color_b;
    this->alpha = alpha;

}
Id::~Id()
{
   
}

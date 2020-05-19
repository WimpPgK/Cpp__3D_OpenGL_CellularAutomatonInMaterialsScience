#ifndef NEIGHBOURHOOD_H
#define NEIGHBOURHOOD_H


#include "Id.h"
#include "Grain.h"
#include "iostream"
#include "Moore.h"
#include "FurtherMoore.h"
#include "NearestMoore.h"



class Neighbourhood
{
    public:
		Id** pom;
        Neighbourhood();
        Id* getBestNeighbour(int, int, int, Grain***);
        Id* mostFrequentValue_NaiveAlgorithm(Id**, int, int);
        virtual ~Neighbourhood();

    protected:

    private:

        void mostFrequentValue_NaiveAlgorithm();
};

#endif // NEIGHBOURHOOD_H

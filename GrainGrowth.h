#ifndef GRAINGROWTH_H
#define GRAINGROWTH_H
#include "Grain.h"
#include "Id.h"
#include "Neighbourhood.h"
#include "FileOperatorColor.h"


class GrainGrowth
{
    public:
        int x;
        int y;
        int z;
        int number_of_inclusioin;
		double probability;
        Id* id;
        Grain*** matrix01;
        Grain*** matrix02;

        void printMatrix();
        GrainGrowth(int, int, int, int, double);
        void startGrowth();
        void randomizeGrain();
		float* getColors();
		float* getNormalizedColorsAmount();
		void saveToFile();
        virtual ~GrainGrowth();

    protected:

    private:
};

#endif // GRAINGROWTH_H

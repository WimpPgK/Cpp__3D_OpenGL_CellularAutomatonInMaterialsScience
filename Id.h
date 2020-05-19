#ifndef ID_H
#define ID_H


class Id
{
    public:
        double color_r;
        double color_g;
        double color_b;
        double alpha;

        void SetColor(double,double,double,double);
        Id();
        virtual ~Id();

    protected:

    private:
};

#endif // ID_H

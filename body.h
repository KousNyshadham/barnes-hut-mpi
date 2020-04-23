#ifndef BODY
#define BODY

class Body{
    private:
    double index;
    double xpos;
    double ypos;
    double mass;
    double xvel;
    double yvel; 

    public:
    Body(double index, double xpos, double ypos, double mass, double xvel, double yvel);

};
#endif
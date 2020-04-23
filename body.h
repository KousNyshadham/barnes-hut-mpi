#ifndef BODY
#define BODY

class Body{
    private:
    double xpos;
    double ypos;
    double mass;
    double xvel;
    double yvel; 
    bool internal;

    public:
    double index;
    Body();
    Body(double index, double xpos, double ypos, double mass, double xvel, double yvel, bool internal);

};
#endif
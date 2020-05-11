#ifndef BODY
#define BODY

class Body{
    public:
    double xpos;
    double ypos;
    double mass;
    double xvel;
    double yvel; 
    double xforce;
    double yforce;
    bool internal;
    int index;

    Body();
    Body(int index, double xpos, double ypos, double mass, double xvel, double yvel, bool internal);
    void addForce(Body b);
    static Body add(Body a, Body b);
    static Body specializedAdd(Body a, Body b);
    void update();
    void resetForce();
};
#endif
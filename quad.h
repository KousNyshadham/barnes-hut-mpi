#ifndef QUAD
#define QUAD

class Quad{
    private:
    double x;
    double y;
    public:
    Quad(double x, double y, double l);
    Quad* NW();
    Quad* NE();
    Quad* SW();
    Quad* SE();
    double l;
    bool contains(double x, double y);
};
#endif
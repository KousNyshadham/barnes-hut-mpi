#ifndef QUADTREE
#define QUADTREE
#include "body.h"
#include "quad.h"

class QuadTree{
    private:
    QuadTree* NE;
    QuadTree* NW;
    QuadTree* SE;
    QuadTree* SW;

    public:
    Body body;
    Quad* quad;
    QuadTree(Quad* quad);
    ~QuadTree();
    void insert(Body ins);
    void updateForce(int mod, Body*);
};

#endif
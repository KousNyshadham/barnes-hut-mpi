#ifndef QUADTREE
#define QUADTREE
#include "body.h"
#include "quad.h"

class QuadTree{
    private:
    Body* body;
    QuadTree* NE;
    QuadTree* NW;
    QuadTree* SE;
    QuadTree* SW;

    public:
    Quad* quad;
    QuadTree(Quad* quad);
    ~QuadTree();
    void insert(Body* ins);
    void updateForce(Body* mod);
};

#endif
#ifndef QUADTREE
#define QUADTREE
#include "body.h"
#include "quad.h"

class QuadTree{
    private:
    Body body;
    Quad* quad;
    QuadTree* NE;
    QuadTree* NW;
    QuadTree* SE;
    QuadTree* SW;

    public:
    QuadTree(Quad quad);
    void insert(Body body);
};

#endif
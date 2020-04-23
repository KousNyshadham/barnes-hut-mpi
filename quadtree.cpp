#include "quadtree.h"
#include "quad.h"

QuadTree::QuadTree(Quad quad){
    this->quad = &quad;
}

void QuadTree::insert(Body ins){
    if(body.index == -1){
        body = ins;
    }
    else{

    }
}
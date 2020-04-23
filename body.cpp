#include "body.h"
Body::Body(){
    index = -1;
}
Body::Body(double index, double xpos, double ypos, double mass, double xvel, double yvel, bool internal){
    this->index = index;
    this->xpos = xpos;
    this->ypos = ypos;
    this->mass = mass;
    this->xvel = xvel;
    this->yvel = yvel;
    this->internal = internal;
}
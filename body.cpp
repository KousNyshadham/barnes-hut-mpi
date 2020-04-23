#include "body.h"
Body::Body(double index, double xpos, double ypos, double mass, double xvel, double yvel){
    this->index = index;
    this->xpos = xpos;
    this->ypos = ypos;
    this->mass = mass;
    this->xvel = xvel;
    this->yvel = yvel;
}
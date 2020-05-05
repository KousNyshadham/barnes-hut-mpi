#include "body.h"
#include "global.h"
#include <math.h>
#include <iostream>
Body::Body(int index, double xpos, double ypos, double mass, double xvel, double yvel, bool internal){
    this->index = index;
    this->xpos = xpos;
    this->ypos = ypos;
    this->mass = mass;
    this->xvel = xvel;
    this->yvel = yvel;
    this->xforce=0;
    this->yforce=0;
    this->internal = internal;
}

void Body::update(){
    double ax = xforce/mass;
    double ay = yforce/mass;
    xpos = xpos + xvel * dt + 0.5*ax*pow(dt,2);
    ypos = ypos + yvel * dt + 0.5*ay*pow(dt,2);
    xvel = xvel + ax*dt;
    yvel = yvel + ay*dt;
    if(xpos < 0 || xpos > 4 || ypos < 0 || ypos > 4){
        mass = -1;
    }
}

void Body::resetForce(){
    this->xforce = 0;
    this->yforce = 0;
}

void Body::addForce(Body* b){
    double G = 0.0001;
    double distance = sqrt(pow(xpos-b->xpos,2)+pow(ypos-b->ypos,2));
    double rlimit = 0.03;
    double denominator = distance < rlimit ? (distance * rlimit * rlimit) : (distance * distance * distance);
    double dx = b->xpos-this->xpos;
    double dy = b->ypos-this->ypos;
    this->xforce+= (G*this->mass*b->mass*dx)/denominator;
    this->yforce+= (G*this->mass*b->mass*dy)/denominator;
}

Body* Body::specializedAdd(Body* a, Body* b){
    double m = a->mass + b->mass;
    double x = (a->xpos*a->mass + b->xpos*b->mass)/m;
    double y = (a->ypos*a->mass + b->ypos*b->mass)/m;
    delete a;
    return new Body(-69, x, y, m, -69,-69, true);
}
Body* Body::add(Body* a, Body* b){
    double m = a->mass + b->mass;
    double x = (a->xpos*a->mass + b->xpos*b->mass)/m;
    double y = (a->ypos*a->mass + b->ypos*b->mass)/m;
    return new Body(-69, x, y, m, -69,-69, true);
}
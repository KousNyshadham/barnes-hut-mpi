#include "quad.h"

Quad::Quad(double x, double y, double l){
    this->x = x;
    this->y = y;
    this->l = l;
}

Quad* Quad::NW(){
    return new Quad(x,y+l/2, l/2);
}

Quad* Quad::NE(){
    return new Quad(x+l/2,y+l/2, l/2);
}

Quad* Quad::SW(){
    return new Quad(x,y, l/2);
}

Quad* Quad::SE(){
    return new Quad(x+l/2,y, l/2);
}
bool Quad::contains(double x, double y){
   if((x >= this->x && x <= this->x+l) && (y>= this->y && y <= this->y +l)){
       return true;
   } 
   return false;
}
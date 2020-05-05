#include "quadtree.h"
#include "quad.h"
#include "global.h"
#include <math.h>

QuadTree::QuadTree(Quad* quad){
    body = nullptr;
    this->quad = quad;
    NE = nullptr;
    NW = nullptr;
    SE = nullptr;
    SW = nullptr;
}

QuadTree::~QuadTree(){
    if(body == nullptr || body->internal == false){
        delete this->quad;
    }
    else{
        delete this->quad;
        delete this->body;
        delete this->NE;
        delete this->NW;
        delete this->SE;
        delete this->SW;
    }
}

void QuadTree::updateForce(Body* mod){
    if(body == nullptr){
        return;
    }
    else{
        if(body->internal == false){
            if(mod != body){
                mod->addForce(body);
            }
        }
        else{
            double distance = sqrt(pow(body->xpos-mod->xpos,2)-pow(body->ypos-mod->ypos,2));
            if(this->quad->l/distance<theta){
                mod->addForce(body);
            }
            else{
                this->SW->updateForce(mod);
                this->NW->updateForce(mod);
                this->SE->updateForce(mod);
                this->NE->updateForce(mod);
            }
        }
    }
}

void QuadTree::insert(Body* ins){
    if(body == nullptr){
        body = ins;
    }
    else{
        if(body->internal == false){
            NE = new QuadTree(quad->NE());
            NW = new QuadTree(quad->NW());
            SE = new QuadTree(quad->SE());
            SW = new QuadTree(quad->SW());
            if(SW->quad->contains(body->xpos, body->ypos)){
                SW->insert(body);
            }
            else if(SE->quad->contains(body->xpos, body->ypos)){
                SE->insert(body);
            }
            else if(NW->quad->contains(body->xpos, body->ypos)){
                NW->insert(body);
            }
            else if(NE->quad->contains(body->xpos, body->ypos)){
                NE->insert(body);
            }
            if(SW->quad->contains(ins->xpos, ins->ypos)){
                SW->insert(ins);
            }
            else if(SE->quad->contains(ins->xpos, ins->ypos)){
                SE->insert(ins);
            }
            else if(NW->quad->contains(ins->xpos, ins->ypos)){
                NW->insert(ins);
            }
            else if(NE->quad->contains(ins->xpos, ins->ypos)){
                NE->insert(ins);
            }
            body = Body::add(body,ins);
        }
        else{
            if(SW->quad->contains(ins->xpos, ins->ypos)){
                SW->insert(ins);
            }
            else if(SE->quad->contains(ins->xpos, ins->ypos)){
                SE->insert(ins);
            }
            else if(NW->quad->contains(ins->xpos, ins->ypos)){
                NW->insert(ins);
            }
            else if(NE->quad->contains(ins->xpos, ins->ypos)){
                NE->insert(ins);
            }
            body = Body::specializedAdd(body,ins);
        }
    }
}
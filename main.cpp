#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "body.h"
#include "quadtree.h"
#include "quad.h"
#include "global.h"
int steps;
double theta;
double dt;
bool visualization;
int n;
int main(int argc, char* argv[]){
    std::string inputfilename;
    std::string outputfilename;
    // TODO: use library for arg parsing 
    for(int i = 1; i < argc; i++){
        std::string arg = std::string(argv[i]);
        if(arg == "-i"){
            inputfilename = argv[++i];
        }
        if(arg == "-o"){
            outputfilename = argv[++i];
        }
        if(arg == "-s"){
            steps = std::stoi(argv[++i]);
        }
        if(arg == "-t"){
            theta = std::stod(argv[++i]);
        }
        if(arg == "-d"){
            dt = std::stod(argv[++i]);
        }
        if(arg == "-V"){
            visualization = true;
        }
    }
    // TODO: improve reading input
    std::ifstream inputfile;
    inputfile.open(inputfilename);
    std::string stringn;
    std::getline(inputfile, stringn);
    n = std::stoi(stringn);
    Body* bodies[n];
    for(int i = 0; i < n; i++){
        std::string line;
        std::getline(inputfile, line);
        std::vector<double> bodyprops;
        std::string value = "";
        for(int j = 0; j < line.size(); j++){
            if(line[j] == '\t'){
                bodyprops.push_back(std::stod(value));
                value = "";
            }
            else{
                value = value + line[j];
            }
        }
        if(value != ""){
            bodyprops.push_back(std::stod(value));
        }
        Body* body = new Body((int)bodyprops[0],bodyprops[1],bodyprops[2],bodyprops[3],bodyprops[4],bodyprops[5], false);
        bodies[i] = body;
    }
    for(int i = 0; i < steps; i++){
        Quad* quad = new Quad(0, 0, 4);
        QuadTree* quadtree = new QuadTree(quad);
        for(int j = 0; j < n; j++){
            quadtree->insert(bodies[j]);
        }
        for(int j = 0; j < n; j++){
            bodies[j]->resetForce();
            quadtree->updateForce(bodies[j]);
            bodies[j]->update();
        }
        free(quadtree);
    }
    std::ofstream out;
    out.open(outputfilename);
    out.setf(std::ios::scientific);
    for(int i = 0; i < n; i++){
        out << bodies[i]->index << " " << bodies[i]->xpos << " " << bodies[i]->ypos << " " << bodies[i]->mass << " " << bodies[i] ->xvel << " " << bodies[i] ->yvel << std::endl;
        free(bodies[i]);
    }
    out.close();
}
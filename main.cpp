#include <string>
#include "body.h"
#include <vector>
#include <fstream>
#include <iostream>
int main(int argc, char* argv[]){
    std::string inputfilename;
    std::string outputfilename;
    int steps;
    double theta;
    double dt;
    bool visualization;
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
    int n = std::stoi(stringn);
    std::vector<Body> bodies;
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
        Body body(bodyprops[0],bodyprops[1],bodyprops[2],bodyprops[3],bodyprops[4],bodyprops[5]);
        bodies.push_back(body);
    }
}
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "body.h"
#include "quadtree.h"
#include "quad.h"
#include "global.h"
#include "mpi.h"
int steps;
double theta;
double dt;
bool visualization;
int n;
std::vector<Body> bodies;
int main(int argc, char* argv[]){
    int numtasks;
    int rank;
    const int datatag = 1;
    const int ranktag = 2;
    const int sendtag = 3;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
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
	double t1, t2;
	t1 = MPI_Wtime();
    if(rank == 0){
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
            Body body((int)bodyprops[0],bodyprops[1],bodyprops[2],bodyprops[3],bodyprops[4],bodyprops[5], false);
            bodies.push_back(body);
        }
        for(int i = 1; i < numtasks; i++){
            MPI_Send(bodies.data(), n*sizeof(Body), MPI_BYTE, i, datatag, MPI_COMM_WORLD);
        }
    }
    for(int i = 0; i < steps; i++){
        if(rank == 0){
            Quad* quad = new Quad(0, 0, 4);
            QuadTree* quadtree = new QuadTree(quad);
            for(int j = 0; j < n; j++){
                quadtree->insert(bodies[j]);
            }
            for(int j = 0; j < n/numtasks; j++){
                bodies[j].resetForce();
                quadtree->updateForce(j, bodies.data());
                bodies[j].update();
            }
            free(quadtree);
            for(int j = 1; j < numtasks; j++){
                int recrank;
                MPI_Recv(&recrank, 1, MPI_INT, j, ranktag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                Body recv_data[n];
                MPI_Recv(recv_data, n*sizeof(Body), MPI_BYTE, j, sendtag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int k = recrank*n/numtasks; k < recrank*n/numtasks+n/numtasks; k++){
                    bodies[k].xpos = recv_data[k].xpos;
                    bodies[k].ypos = recv_data[k].ypos;
                    bodies[k].mass = recv_data[k].mass;
                    bodies[k].xvel = recv_data[k].xvel;
                    bodies[k].yvel = recv_data[k].yvel;
                }
                if(i != steps-1){
                    MPI_Send(bodies.data(), n*sizeof(Body), MPI_BYTE, j, datatag, MPI_COMM_WORLD);
                }
            }
        }
        else{
            Quad* quad = new Quad(0, 0, 4);
            QuadTree* quadtree = new QuadTree(quad);
            Body recv_data[n];
            MPI_Recv(recv_data, n*sizeof(Body), MPI_BYTE, 0, datatag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int j = 0; j < n; j++){
                quadtree->insert(recv_data[j]);
            }
            for(int j = rank * n/numtasks; j < rank*n/numtasks+n/numtasks; j++){
                recv_data[j].resetForce();
                quadtree->updateForce(j, recv_data);
                recv_data[j].update();
            }
            MPI_Send(&rank, 1, MPI_INT, 0, ranktag, MPI_COMM_WORLD);
            MPI_Send(recv_data, n*sizeof(Body), MPI_BYTE, 0, sendtag, MPI_COMM_WORLD);
            free(quadtree);
        }
    }
	t2 = MPI_Wtime();
    MPI_Finalize();
    if(rank == 0){
		std::cout << t2-t1 << std::endl;
        std::ofstream out;
        out.open(outputfilename);
        out.setf(std::ios::scientific);
        for(int i = 0; i < n; i++){
            out << bodies[i].index << " " << bodies[i].xpos << " " << bodies[i].ypos << " " << bodies[i].mass << " " << bodies[i].xvel << " " << bodies[i].yvel << std::endl;
        }
        out.close();
    }
}

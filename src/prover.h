#ifndef PROVER_H
#define PROVER_H

#include "network.h"

class Prover{
public:
    Prover(std::ifstream& infile);
    ~Prover();
    bool SolveGraph();
    bool BeginExchange(int k, char* hostname, char* port);
    bool GenerateCommitments();
    bool ProcessEdgeRequests();
private:
    int32_t* requests;
    int commitnum;
    Graph* g;
    Graph* graphs;
    Network network;
};

#endif
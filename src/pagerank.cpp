//
// Created by Andrea Ferlini on 03/10/2017.
//

#include "pagerank.h"

void computePageRank(double *p, AdjacencyList& adjList, double alpha, int threshold, bool debug){

    int iteration=0;
    double ranks;
    double tot_rank=0;
    // init p[i]
    double p0 = (double) 1/adjList.num_vertices;
    double p_in_neighbours = 0;
    if (debug)
        cout << "[PAGE RANK COMPUTATION] - number of vertices: " << adjList.num_vertices << endl;

    for(unsigned int i=0; i < adjList.num_vertices; i++){
        p[i]= p0;
        //cout << "[PAGE RANK COMPUTATION] - init value of p[" << i << "]: " << p[i] << endl;
    }


    // PAGE RANK COMPUTATION
    for (iteration = 0; iteration < threshold; iteration ++){

        for(unsigned int i=0; i < adjList.num_vertices; i++) {
            if (adjList.getDegreeOut(i) != 0) {
                // Transition Matrix
                p[i] = p[i] /(double) (adjList.getDegreeOut(i));
                if (debug){
                    cout << "[PAGE RANK COMPUTATION] - degree of " << i << ": " << adjList.getDegreeOut(i) << endl;
                    cout << "[PAGE RANK COMPUTATION] - transition matrix p[" << i << "]: " << p[i] << endl;
                }
            } else {
                p[i] = 1.0/adjList.num_vertices;
            }
        }

        for(unsigned int i=0; i < adjList.num_vertices; i++) {
            p_in_neighbours = 0;
            if (debug)
                cout << "[PAGE RANK COMPUTATION] - calculate p[" << i << "]: " << p[i] << endl;
            if (adjList.getDegreeIn(i)>0){
                for (unsigned int j = 0; j < adjList.getDegreeIn(i); j++) {
                    unsigned int neighbour = adjList.getFirstNeighbourIdIn(i)+j;

                    if (adjList.getDegreeIn(adjList.in_neighbours_list[neighbour]) != 0){
                        // sum of all the prob. of coming from a neigh. to [i]
                        // every of them is given by: prob of being in the neigh * prob of reach that node
                        // (number of links into that node -> the more and the easier getting there)
                        p_in_neighbours += p[adjList.in_neighbours_list[neighbour]]
                                           * (1.0/adjList.getDegreeIn(adjList.in_neighbours_list[neighbour]));

                    }else{
                        // if no links directed to the neighbour node -> the only way to get into it is p0
                        p_in_neighbours += p[adjList.in_neighbours_list[neighbour]] * p0;
                    }

                    if (debug)
                        cout << "[PAGE RANK COMPUTATION] - update value of p[" << i << "]: " << p[i] << endl;
                }
                // page rank of [i] = arriving in [i] thanks to random teleport (alpha * p0) +
                // probability of coming from one of [i]'s neighbours -> sum of all the prob. of coming from a neigh.
                p[i] = (alpha * p0) + ((1 - alpha) * p_in_neighbours);
                if (debug)
                    cout << "[PAGE RANK COMPUTATION] - update value of p[" << i << "]: " << p[i] << endl;
            } else {
                // if no links in [i]
                p[i] = (alpha * p0);
            }
        }

        //TODO plot k random nodes pagerank values @ every iteration
    }
    
    // normalization
    ranks = 0;
    for (unsigned int i=0; i < adjList.num_vertices; i++){
        ranks = ranks + p[i];
        if (debug)
            cout << "ranks = " << ranks << " @ iteration " << i << endl;
    }

    tot_rank = 0;
    for (unsigned int i=0; i < adjList.num_vertices; i++){
        p[i] += (1-ranks)/(double)adjList.num_vertices;
        tot_rank += p[i];
    }
    cout << "[PAGE RANK COMPUTATION] - Total Page Rank: " << tot_rank << endl;

    printMinMax(p, adjList);
}

void printMinMax(double *p, AdjacencyList& adjList){

    double max_rank = 0;
    unsigned int node_max_rank = 0;

    double min_rank = -1;
    unsigned int node_min_rank = 0;

    for (unsigned int i=0; i < adjList.num_vertices; i++){
        if (p[i] > max_rank){
            max_rank = p[i];
            node_max_rank = i;
        }

        if (adjList.getDegreeOut(i) > 0.0 || adjList.getDegreeIn(i) > 0.0){
            if (min_rank < 0){
                min_rank = p[i];
                node_min_rank = i;
            }
            if (p[i] < min_rank){
                min_rank = p[i];
                node_min_rank = i;
            }
        }
    }

    cout << endl << endl;
    cout << "Node with highest rank: " << node_max_rank+1 << endl;
    cout << "Page Rank: " << p[node_max_rank] << endl;
    cout << endl;

    cout << "Node with lowest rank: " << node_min_rank+1 << endl;
    cout << "Page Rank: " << p[node_min_rank] << endl;
    cout << endl;
}
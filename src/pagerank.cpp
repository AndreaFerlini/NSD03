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
    //for (iteration = 0; iteration < threshold; iteration ++){
        for(unsigned int i=0; i < adjList.num_vertices; i++) {
            if (adjList.getDegreeOut(i) != 0) {
                // Transition Matrix
                p[i] = p[i] / (adjList.getDegreeOut(i));
                if (debug){
                    cout << "[PAGE RANK COMPUTATION] - degree of " << i << ": " << adjList.getDegreeOut(i) << endl;
                    cout << "[PAGE RANK COMPUTATION] - transition matrix p[" << i << "]: " << p[i] << endl;
                }
            } else {
                p[i] = 0;
            }
        }
        for(unsigned int i=0; i < adjList.num_vertices; i++) {
            p_in_neighbours = 0;
            if (debug)
                cout << "[PAGE RANK COMPUTATION] - calculate p[" << i << "]: " << p[i] << endl;
            if (adjList.getDegreeIn(i)>0){
                for (unsigned int j = 0; j < adjList.getDegreeIn(i); j++) {
                    p_in_neighbours += p[adjList.in_neighbours_list[(adjList.in_list_beginning[i] + j)]];
                    if (debug)
                        cout << "[PAGE RANK COMPUTATION] - update value of p[" << i << "]: " << p[i] << endl;
                }
                p[i] += (alpha * p0) + (1 - alpha) * p_in_neighbours;
                if (debug)
                    cout << "[PAGE RANK COMPUTATION] - update value of p[" << i << "]: " << p[i] << endl;
            } else {
                p[i] = (alpha * p0);
            }
        }
    //}

    // normalization
    ranks = 0;
    for (unsigned int i=0; i < adjList.num_vertices; i++){
        ranks = ranks + p[i];
        if (debug)
            cout << "ranks = " << ranks << " @ iteration " << i << endl;
    }

    tot_rank = 0;
    for (unsigned int i=0; i < adjList.num_vertices; i++){
        p[i] += (1-ranks)/adjList.num_vertices;
        tot_rank += p[i];
    }
    cout << "[PAGE RANK COMPUTATION] - Total Page Rank: " << tot_rank << endl;
}
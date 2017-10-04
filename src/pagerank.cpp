//
// Created by Andrea Ferlini on 03/10/2017.
//

#include "pagerank.h"

void computePageRank(double *p, AdjacencyList& adjList, double alpha, int threshold){

    int iteration=0;
    double ranks;
    double tot_rank=0;
    // init p[i]
    double p0 = (double) 1/adjList.num_vertices;
    //cout << "[PAGE RANK COMPUTATION] - number of vertices: " << adjList.num_vertices << endl;

    for(unsigned int i=0; i < adjList.num_vertices; i++){
        p[i]= p0;
        //cout << "[PAGE RANK COMPUTATION] - init value of p[" << i << "]: " << p[i] << endl;
    }


    // page rank computation
    for(unsigned int i=0; i < adjList.num_vertices; i++){
        if(adjList.getDegreeIn(i) != 0){
            // Transition Matrix
            p[i]=p[i]/(adjList.getDegreeIn(i));
            //cout << "[PAGE RANK COMPUTATION] - degree of " << i << ": " << adjList.getDegree(i) << endl;
            //cout << "[PAGE RANK COMPUTATION] - transition matrix p[" << i << "]: " << p[i] << endl;
        } else {
            p[i] = 0;
        }
//        while(iteration < threshold){
            //cout << "[PAGE RANK COMPUTATION] - calculate p[" << i << "]: " << p[i] << endl;
            for (unsigned int j = 0; j < adjList.getDegreeIn(i); j++) {
                p[i] += alpha * p0 + (1 - alpha) * p[adjList.in_neighbours_list[(adjList.in_list_beginning[i] + j)]];
                //cout << "[PAGE RANK COMPUTATION] - update value of p[" << i << "]: " << p[i] << endl;
            }
//            iteration ++;
//        }

    }
    // normalization
    ranks = 0;
    for (unsigned int i=0; i < adjList.num_vertices; i++){
        ranks = ranks + p[i];
        //cout << "ranks = " << ranks << " @ iteration " << i << endl;
    }


    //cout << "[PAGE RANK COMPUTATION] - Total Page Rank: " << ranks << endl;
    tot_rank = 0;
    for (unsigned int i=0; i < adjList.num_vertices; i++){
        p[i] += (1-ranks)/adjList.num_vertices;
        tot_rank += p[i];
    }
    cout << "[PAGE RANK COMPUTATION] - Total Page Rank: " << tot_rank << endl;
}
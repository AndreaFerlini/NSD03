//
// Created by Andrea Ferlini on 03/10/2017.
//

#ifndef SRC_PAGERANK_H
#define SRC_PAGERANK_H

#include "loadgraph.h"

void computePageRank(double *p, AdjacencyList& adjList, double alpha, int threshold);

#endif //SRC_PAGERANK_H

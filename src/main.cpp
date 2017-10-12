#include <iostream>
#include "loadgraph.h"
#include "pagerank.h"

int main() {

    string filename = "../graphs/wiki.txt";
    //string filename = "../graphs/sample.graph";
    //string filename = "../../graphs/sample_weighted.graph";

    ifstream file(filename);

    bool debug = false;
    bool is_weighted = false;
    //bool is_weighted = true;

    AdjacencyList loadedGraph;

    double alpha = 0.15;
    double *page_rank_array;
    int th = 20;

    cout << "STARTED" << endl;

    if (!file.good())
        cout << "No such file... " << endl;

    // Load the Graph as AdjList
    if (loadAdjListContiguous(filename, loadedGraph, is_weighted,debug))
        return -1;

    cout << "[MAIN] - Print loaded graph" << endl;
    if(debug)
        loadedGraph.print(debug);

    page_rank_array = new double [loadedGraph.num_vertices];

    computePageRank(page_rank_array, loadedGraph, alpha, th, debug);

    if (debug){
        for (unsigned int i=0; i < loadedGraph.num_vertices; i++){
            cout << page_rank_array[i] << " ";
        }
    }

    cout << "[MAIN] - Writing files to plot" << endl;

    {
        fstream output1,
                output2,
                output3,
                output4,
                output5,
                output6;


        output1.open("../output/pr-in_deg.out", ios::out);
        output2.open("../output/pr-out_deg.out", ios::out);
        output3.open("../output/pr015-pr01.out", ios::out);
        output4.open("../output/pr015-pr02.out", ios::out);
        output5.open("../output/pr015-pr05.out", ios::out);
        output6.open("../output/pr015-pr09.out", ios::out);


        cout << "          - ../output/pr-in_deg.out" << endl;
        cout << "          - ../output/pr-out_deg.out" << endl;

        for (int v=0; v<loadedGraph.num_vertices; v++){
            output1 << page_rank_array[v] << " " << loadedGraph.getDegreeIn(v) << endl;
            output2 << page_rank_array[v] << " " << loadedGraph.getDegreeOut(v) << endl;
        }

        cout << "          - ../output/pr015-pr01.out" << endl;
        auto* pgr_arr = new double [loadedGraph.num_vertices];
        computePageRank(pgr_arr, loadedGraph, 0.1, th, debug);

        for (int v=0; v<loadedGraph.num_vertices; v++){
            output3 << page_rank_array[v] << " " << pgr_arr[v] << endl;
        }

        cout << "          - ../output/pr015-pr02.out" << endl;
        computePageRank(pgr_arr, loadedGraph, 0.2, th, debug);

        for (int v=0; v<loadedGraph.num_vertices; v++){
            output4 << page_rank_array[v] << " " << pgr_arr[v] << endl;
        }

        cout << "          - ../output/pr015-pr05.out" << endl;
        computePageRank(pgr_arr, loadedGraph, 0.5, th, debug);

        for (int v=0; v<loadedGraph.num_vertices; v++){
            output5 << page_rank_array[v] << " " << pgr_arr[v] << endl;
        }


        cout << "          - ../output/pr015-pr09.out" << endl;
        computePageRank(pgr_arr, loadedGraph, 0.9, th, debug);

        for (int v=0; v<loadedGraph.num_vertices; v++){
            output6 << page_rank_array[v] << " " << pgr_arr[v] << endl;
        }

        delete[] pgr_arr;


        output1.close();
        output2.close();
        output3.close();
        output4.close();
        output5.close();
        output6.close();



        // plot the file

        cout << "[MAIN] - Plotting..." << endl;
        string command = "cd ../output && ./plot_scatters.plt";
        system(command.c_str());

    }


    delete[] page_rank_array;
    return 0;
}
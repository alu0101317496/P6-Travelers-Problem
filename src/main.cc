#include "../include/Greedy.h"
#include "../include/BruteForce.h"


void random_graph_generator(int node_number) {
    std::ofstream file("random_graph.txt");
    file << node_number << std::endl;
    for (int i = 0; i < node_number; ++i) {
        for (int j = 0; j < node_number; ++j) {
            if (i != j) {
                if(node_number < 27) {
                    file << char(65+i) << " " << char(65+j) << " " << rand() % 100 << std::endl;
                } else {
                    file << "n" << i << " " << "n" << j << " " << rand() % 100 << std::endl;
                }
            }
        }
    }
    file.close();
}

/**
 * @brief Constructs a new method and solves 
 * the graph with the given algorithm.
 * 
 */
int protected_main(int argc, char** argv) {
    Method* metGreedy;
    Method* metPDynam;
    Method* metBForce;
    std::string filename;
    int option;
    int node_number;
    if (argc == 3) {
        option = atoi(argv[2]);
        filename = argv[1];
    } else {
        option = atoi(argv[1]);
        std::cout << "Insert the number of nodes: ( < 27 for notation purposes)\n";
        std::cin >> node_number;
        random_graph_generator(node_number);
        filename = "random_graph.txt";
    }
    metGreedy = new Greedy(filename);
    metBForce = new BruteForce(filename);
    
    Pair solutionGreed, solutionBForce, solutionPDynam;
    solutionBForce.cost = 0;
    solutionPDynam.cost = 0;

    // Brute Force
    clock_t startBForce = clock();
    solutionBForce = metBForce->SolveMethod();
    clock_t endBForce = clock();

    // Dynamic Programming
    clock_t startPDynam = clock();
    clock_t endPDynam = clock();

    //Greedy    
    clock_t startgreed = clock();
    solutionGreed = metGreedy->SolveMethod();
    clock_t endgreed = clock();

    double BForce_time = Clocker(startBForce, endBForce);
    double PDynam_time = Clocker(startPDynam, endPDynam);
    double greed_time = Clocker(startgreed, endgreed);

    printf("THE WAY: %s\n", solutionGreed.result.c_str());
    printf("BForce cost: %d\nBForce time: %lfs\n------\nPDynam cost: %d\nPDynam time: %lfs\n------\nGreedy cost: %d\nGreedy time: %lfs\n----\nTime average: %lfs",
    solutionBForce.cost, BForce_time, solutionPDynam.cost, PDynam_time, solutionGreed.cost, greed_time, (BForce_time + PDynam_time + greed_time)/3);
    return 0;
}

int main(int argc, char** argv) {
    try {
        return protected_main(argc, argv);
    } catch(...) {
        
    }
}

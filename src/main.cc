/**
 * @file main.cc
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022
 * @page https://github.com/alu0101317496/P6-Travelers-Problem
 */

#include "../include/Greedy.h"
#include "../include/BruteForce.h"

#define SIZENAME 14

template<class T> 
void print_element(T t) {
    std::cout << std::setw(SIZENAME) << std::setfill(' ') << t;
}

void random_graph_generator(int node_number, std::string filename) {
    std::ofstream file(filename);
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
    int node_number;
    if (argc == 2) {
        node_number = atoi(argv[1])+1;
    } else {
        node_number = 5+1;
    }
    std::vector<std::string> filenames;
    for(int i = 2; i < node_number;++i) {
        filename = "random_graph" + std::to_string(i) + ".txt";
        random_graph_generator(node_number, filename);
        filenames.push_back(filename);
    }

    

   
    Pair solutionGreed, solutionBForce, solutionPDynam;
    solutionBForce.cost = 0;
    solutionPDynam.cost = 0;

    double BForce_time, PDynam_time, Greedy_time;
    std::vector<Triple> triples;
    Triple auxtriple;

    for (int i = 0; i < filenames.size(); ++i) {
        metGreedy = new Greedy(filenames[i]);
        metBForce = new BruteForce(filenames[i]); 
        // Brute Force
        clock_t startBForce = clock();
        // Esta comentado porque da problemas, en el repo intentaré tenerlo solucionado. repo above
        solutionBForce = metBForce->SolveMethod();
        clock_t endBForce = clock();

        // Dynamic Programming
        clock_t startPDynam = clock();
        clock_t endPDynam = clock();

        //Greedy    
        clock_t startgreed = clock();
        solutionGreed = metGreedy->SolveMethod();
        clock_t endgreed = clock();

        BForce_time = Clocker(startBForce, endBForce);
        PDynam_time = Clocker(startPDynam, endPDynam);
        Greedy_time = Clocker(startgreed, endgreed);

        auxtriple.brute_force.cost = solutionBForce.cost;
        auxtriple.brute_force.time = BForce_time;
        auxtriple.greedy.cost = solutionGreed.cost;
        auxtriple.greedy.time = Greedy_time;
        auxtriple.dynamic.cost = solutionPDynam.cost;
        auxtriple.dynamic.time = PDynam_time;
        triples.push_back(auxtriple);
    }


    //MODIFICACION:
    double greedy_mean = 0;
    double dynamic_mean = 0;
    double brute_mean = 0;
    for (int i = 0; i < triples.size(); ++i) {
        greedy_mean += triples[i].greedy.time;
        //dynamic_mean += triples[i].dynamic.time;
        brute_mean += triples[i].brute_force.time;
    }
    greedy_mean = greedy_mean / triples.size();
    //dynamic_mean = dynamic_mean / triples.size();
    brute_mean = brute_mean / triples.size();
    print_element("");
    print_element("Greedy cost");
    print_element("Greedy time");
    print_element("Dynamic cost");
    print_element("Dynamic time");
    print_element("Brute force cost");
    print_element("Brute Force time");
    std::cout << '\n';
    for (int i = 0; i < triples.size(); ++i) {
        print_element("Nodes: " + std::to_string(i+2)); 
        print_element(std::to_string(triples[i].greedy.cost));
        print_element(std::to_string(triples[i].greedy.time));
        print_element(std::to_string(triples[i].dynamic.cost));
        print_element(std::to_string(triples[i].dynamic.time));
        print_element(std::to_string(triples[i].brute_force.cost));
        print_element(std::to_string(triples[i].brute_force.time));
        std::cout << '\n';
    }
    std::cout << '\n';
    print_element("Greedy mean");
    print_element(std::to_string(greedy_mean));
    std::cout << '\n';
    print_element("Dynamic mean");
    print_element(std::to_string(dynamic_mean));
    std::cout << '\n';
    print_element("Brute force mean");
    print_element(std::to_string(brute_mean));



    return 0;
}

int main(int argc, char** argv) {
    try {
        return protected_main(argc, argv);
    } catch(...) {
        
    }
}

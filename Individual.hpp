#include<vector>
#include<iostream>


#ifndef individualHpp
#define individualHpp

using namespace std;
namespace metaheuristica{
    class Individual{
        public:
            std::vector<int> superA;
            float fitness;
            

            Individual(std::vector<int>, float);
            Individual(std::vector<int>);
            Individual();

            std::vector<int> get_machine_cell();
            void print_solution();
            void set_machine_cell(std::vector<int>);
            float get_fitness();
            void set_fitness(float);
    };


    Individual::Individual(std::vector<int> machine_cell, float fit){
        superA = machine_cell;
        fitness = fit;
    }

    Individual::Individual(std::vector<int> machine_cell){
        superA = machine_cell;
        fitness = 0;
    }

    Individual::Individual(){
        fitness = 0;
    }


    std::vector<int> Individual::get_machine_cell(){
        return superA;
    }
    void Individual::print_solution(){
        for(auto dato : superA){
            cout << dato << " ";
        }
    }
    void Individual::set_machine_cell(std::vector<int> machine_cell){
        superA = machine_cell;
    }
    float Individual::get_fitness(){
        return fitness;
    }
    void Individual::set_fitness(float fit){
        fitness = fit;
    }
};

#endif
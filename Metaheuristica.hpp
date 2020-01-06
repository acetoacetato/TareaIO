#include<iostream>
#include<string>
#include<vector>
#include<list>

#include "Individual.hpp"
#include "MCDPRandomSolution.hpp"
#include "MCDPData.hpp"
#include "MCDPModel.hpp"

#ifndef metaheuristicaHpp
#define metaheuristicaHpp

namespace metaheuristica{
    class Metaheuristica{
        public:
            int numberIndividual;
            int numberIteration;
            float consultationFactor;
            Individual bestSolution;
            std::vector<Individual> poblation;
            MCDPData* data;

            Metaheuristica(int nIndividual, int nIteracion, metaheuristica::MCDPData* datos);

            void generateInitialPoblation();
            void ordenaBacterias();
            std::vector<int> mutate(std::vector<int>, int, int);
            void run();
    };

    Metaheuristica::Metaheuristica(int nIndividual, int nIteracion, MCDPData* datos){
        numberIndividual = nIndividual;
        numberIteration = nIteracion;
        data = datos;   
    }

    void Metaheuristica::generateInitialPoblation(){
        for (int i = 0; i < numberIndividual; i++) {
            // Inicialite procedure.
            MCDPRandomSolution randomSolution(data->getF_weight(), data->getF_size(), data->n);
            float randomSolutionFitness = 0;
            randomSolution.createRandomSolution();
            MCDPModel boctorModel(data->f_weight, data->f_size, data->n,
                    randomSolution.get_machine_cell());
            randomSolutionFitness = boctorModel.calculateFitness();
            // Create Solution
            Individual individual(randomSolution.get_machine_cell(), randomSolutionFitness);
            // Add Solution in poblation
            poblation.push_back(individual);
        }
    }

    void Metaheuristica::ordenaBacterias(){
        bool orden = false;
        int i = 0;
        Individual aux;
        while(i<poblation.size() && orden == false){
            i+=1;
            orden = true;
            for (int j = 0; j < poblation.size()-1; j++) {
                if(poblation[j+1].fitness < poblation[j].fitness){
                    orden=false;
                    Individual aux(poblation[j].get_machine_cell(), poblation[j].fitness);
                    poblation[j].set_machine_cell(poblation[j+1].get_machine_cell());
                    poblation[j].set_fitness(poblation[j+1].fitness); 
                    poblation[j+1].set_machine_cell(aux.get_machine_cell());
                    poblation[j+1].set_fitness(aux.get_fitness()); 
                }
            }
        }
    }


    std::vector<int> Metaheuristica::mutate(std::vector<int> M,int A, int B){
        int aux;
        aux=M[A];
        M[A]=M[B];
        M[B]=aux;
        return M;
    }



    void Metaheuristica::run() {
        cout << "empieza a correr" << endl;
        generateInitialPoblation();
        ordenaBacterias();
        cout << "mejor fitness INICIAL: " << poblation[0].fitness << endl;
        
        int iteration = 0;
        float mejorFitness = 99999999;

        while (iteration < numberIteration) {
            
            for(int k=0 ; k< poblation.size();k++){
                std::vector<int> initial = poblation[k].get_machine_cell();
                for(int i=0; i < (data->n -1); i++){
                    for(int j = i+1 ; j < data->n ; j++){
                        std::vector<int> M = mutate(initial, i, j);
                        Individual pk(M);
                        MCDPModel boctorModel(data->f_weight, data->f_size, data->n, M);
                        pk.set_fitness(boctorModel.calculateFitness());
                        if(pk.get_fitness()<=poblation[0].get_fitness()){
                            poblation[0].set_fitness(pk.get_fitness());
                            poblation[0].set_machine_cell(pk.get_machine_cell());
                        }
                    }
                }
            }
            ordenaBacterias();
            if (poblation[0].get_fitness() < mejorFitness) {
                mejorFitness = poblation[0].get_fitness();
                cout << "mejor fitness: " << mejorFitness << " iteracion: " << iteration << endl;

            }
            cout << "iteracion: " << iteration << endl;
            
            
            iteration++;
        }
        cout << "best solution: " << mejorFitness << endl;
        poblation[0].print_solution();
   
        
    }
    //</editor-fold>
}

#endif
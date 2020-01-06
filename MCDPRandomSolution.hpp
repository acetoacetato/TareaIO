#include<iostream>
#include<vector>



using namespace std;

#ifndef mcdpRandomSolutionHpp
#define mcdpRandomSolutionHpp

namespace metaheuristica{
    class MCDPRandomSolution{
        public:
            //mismos datos que el data
            std::vector<std::vector<int>> f_weight;
            std::vector<int> f_size;
            std::vector<int> superA;
            int N;

            MCDPRandomSolution(std::vector<std::vector<int>>, std::vector<int>, int);

            void createRandomSolution();
            std::vector<int> shuffleArray(std::vector<int>);
            std::vector<int> get_machine_cell();
            std::vector<int> set_machine_cell(std::vector<int>);
    };


    MCDPRandomSolution::MCDPRandomSolution(std::vector<std::vector<int>> weights, std::vector<int> sizes, int n) {
        f_weight = weights;
        f_size = sizes;
        N = n;
    }

    void MCDPRandomSolution::createRandomSolution(){
        for(int i=0; i<N ; i++){
            superA.push_back(i+1);
        }
        std::vector<int> auxArray = shuffleArray(superA);

    }

    std::vector<int> MCDPRandomSolution::shuffleArray(std::vector<int> arr){
        for(int i=0; i<arr.size() ; i++){
            int random = rand() % (i+1);
            cout << random << endl;
            int aux = arr[random];
            arr[random] = arr[i];
            arr[i] = aux;
        }
        return arr;
    }

    std::vector<int> MCDPRandomSolution::get_machine_cell(){
        return superA;
    }
    std::vector<int> MCDPRandomSolution::set_machine_cell(std::vector<int> vec){
        superA = vec;
    }


}

#endif
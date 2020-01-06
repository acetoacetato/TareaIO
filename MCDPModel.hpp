#include<iostream>
#include<vector>

using namespace std;


#ifndef mcdpModelHpp
#define mcdpModelHpp

namespace metaheuristica{
    class MCDPModel{
        public:
            //mismos datos que el data
            std::vector<std::vector<int>> f_weight;
            std::vector<int> f_size;
            std::vector<int> superA;
            int N;

            MCDPModel(std::vector<std::vector<int>>, std::vector<int>, int, std::vector<int>);

            float calculateFitness();
            float distance(int, int);
    };


    MCDPModel::MCDPModel(std::vector<std::vector<int>> weights, std::vector<int> sizes, int n, std::vector<int> arreglo){
        f_size = sizes;
        f_weight = weights;
        N = n;
        superA = arreglo;
    }


    float MCDPModel::calculateFitness(){
        float sum = 0;
        
        for (int k = 0; k < (N-1); k++) {
            for (int i = k+1; i < N; i++) {
                sum = sum + distance(superA[k]-1, superA[i]-1) * f_weight[superA[i]-1][superA[k]-1];
            }
        }
        return sum;
    }


    float MCDPModel::distance(int i, int j){
        float sum= (f_size[i]/2)+ (f_size[j]/2);
        for(int k=i+1; k < j;k++){
            sum= sum + f_size[k];
        }
        return sum;
    }
}

#endif
#include "MCDPRandomSolution.hpp"
#include "Individual.hpp"
#include "MCDPData.hpp"
#include "Metaheuristica.hpp"

using namespace std;
using namespace metaheuristica;
int main(){
    string fileName = "QAP_sko56_04_n.txt";
    int numberPoblation = 10;
    int numberIteration = 50;
    cout << "hola" << endl;
    metaheuristica::MCDPData data(fileName);
    data.printInstance();
    cout << "generado" << endl;
    metaheuristica::Metaheuristica meta(numberPoblation, numberIteration, &data);

    meta.run();
    return 0;
}
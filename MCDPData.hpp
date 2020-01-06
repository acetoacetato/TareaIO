#include<iostream>
#include<vector>
#include<string>
#include<fstream>


using namespace std;

#ifndef mcdpDataHpp
#define mcdpDataHpp


namespace metaheuristica {
    class MCDPData{
        public:
            int n;
            string name;
            std::vector<int> f_size;
            std::vector<std::vector<int>> f_weight;

            MCDPData(string fileName);
            void printInstance();
            int getProblemSize();
            int getWeight(int, int);
            int getFacilitySize(int);
            int getTotalDistance(std::vector<int>);

            int getN();
            std::vector<int> getF_size();
            std::vector<std::vector<int>> getF_weight();
        

    };

    MCDPData::MCDPData(string fileName){
        std::ifstream file(fileName);
        string line;
        n = -1;
        int i = -1;
        if(file.is_open()){
            while(getline(file, line)){
                cout << line << endl;
                if(line.rfind("#", 0) == 0){
                    continue;
                }
                if(n < 0){
                    cout << "primera iteracion = " << line << endl;
                    n = stoi(line);
                    cout << "e";
                    std::vector<std::vector<int>> auxWeight(n, std::vector<int>(n));
                    f_weight = auxWeight;
                    std::vector<int> auxSize(n);
                    f_size = auxSize;
                    cout <<"termina la primera " << endl;
                    continue;
                } 

                if(i == -1){
                    cout << "segunda iteracion" << endl;
                    string delimiter = ",";
                    size_t pos = 0;
                    string token;
                    int iterator = 0;
                    while ((pos = line.find(delimiter)) != std::string::npos) {
                        token = line.substr(0, pos);
                        f_size[iterator] = stoi(token);
                        line.erase(0, pos + delimiter.length());
                        iterator++;
                    }
                    f_size[iterator] = stoi(line);
                    i=0;
                    continue;
                }

                cout << "continuo"<< endl;
                string delimiter = ",";
                size_t pos = 0;
                string token;
                int iterator = 0;
                while ((pos = line.find(delimiter)) != std::string::npos) {
                    token = line.substr(0, pos);
                    f_weight[i][iterator] = stoi(token);
                    line.erase(0, pos + delimiter.length());
                    iterator++;
                }
                f_weight[i][iterator] = stoi(line);

                i++;
                
            }

            file.close();
        }
    }

    void MCDPData::printInstance () {
    /*
     * FUNCTION: imprime por pantalla la información de la instancia
     * INPUT: ninguno
     * OUTPUT: ninguno
     */
        cout << "Numero de instalaciones: " <<  n << endl;
        cout << "Tamaños: " << endl;
        for (int k=0; k<n; k++) {
        cout << f_size[k] << " ";
        }
        cout << endl;
        cout << "Pesos: " << endl;
        for (int i=0; i<n; i++) {
            for (int k=0; k<n; k++) {
                cout << f_weight[i][k] << " ";
            }
            cout << endl;
        }
  };

    int MCDPData::getProblemSize(){
        return n;
    }
    int MCDPData::getWeight(int i, int j){
        if (i>=n || i<0 || j>=n || j<0) {
            return -1;
        }
        return(f_weight[i][j]);
    }
    int MCDPData::getFacilitySize(int i){ 
        if (i>=n || i<0) {
            return -1;
        }
        return(f_size[i]);
    }
    int MCDPData::getTotalDistance(std::vector<int> sol){
        double total = 0.0;
        double middle_distance;
        int p1, p2;

        // Calcular la distancia de todas las combinaciones de 
        // puestos
        for (int i=0; i < (n-1); i++) {
        // Indice del puesto en la posición 1
        p1 = sol[i];
        middle_distance = 0.0;
        for (int j=(i+1); j<n; j++) {
            p2 =  sol[j];
            total = total + (f_size[p1]/2 + middle_distance + f_size[p2]/2); 
            middle_distance = middle_distance + f_size[p2]; 
        }
        }
        return(total);
    }

    int MCDPData::getN(){
        return n;
    }
    std::vector<int> MCDPData::getF_size(){
        return f_size;
    }
    std::vector<std::vector<int>> MCDPData::getF_weight(){
        return f_weight;
    }

}

#endif
#include <iostream>
#include <vector>
#include <random>
#include "simulated_annealing.h"
#include "knapsack.h"
#include "item.h"

using namespace std;

void construct_initial_solution(Knapsack *ks) 
{
    random_device rd;  // Obtém uma semente do hardware
    mt19937 gen(rd()); // Inicializa o gerador Mersenne Twister
    uniform_int_distribution<> dis(0, ks->get_items_set().size() - 1); // Define a distribuição
    int tries = 100;

    while(ks->get_weight() <= ks->get_max_weight() && tries-->= 0) {
        // Gera um índice aleatório
        int random_index = dis(gen);
        ks->add_item(random_index);
    }
}

int main(int argc, char **argv) {
    Knapsack *ks = Knapsack::read_knapsack_instance("./kpcg_instances/C10_BPPC_5_0_5.txt_0.1.dat");
    //ks->show_items_set();
    
    cout << ks->get_max_weight() << endl;

    construct_initial_solution(ks);

    cout << *ks << endl;

    cout << "Start simulated annealing..." << endl;
    simulated_annealing(ks, 1000, 0.01, 100, 0.99);
    cout << "Finished!" << endl;

    cout << *ks << endl;

    delete ks;
}
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
    Knapsack *ks = Knapsack::read_knapsack_instance("./kpcg_instances/C3_BPPC_1_0_2.txt_0.1.dat");
    //ks->show_items_set();
    
    construct_initial_solution(ks);

    cout << *ks << endl;

    cout << "Starting simulated annealing..." << endl;
    simulated_annealing(ks);

    delete ks;
}

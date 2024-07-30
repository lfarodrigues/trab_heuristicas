#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include "simulated_annealing.h"
#include "knapsack.h"
#include "item.h"

using namespace std;

void construct_initial_solution(Knapsack *ks, long long seed)
{
    mt19937 gen(seed); // Inicializa o gerador Mersenne Twister
    uniform_int_distribution<> dis(0, ks->get_items_set().size() - 1); // Define a distribuição
    int tries = 100;

    while(ks->get_weight() <= ks->get_max_weight() && tries-->= 0) {
        // Gera um índice aleatório
        int random_index = dis(gen);
        ks->add_item(random_index);
    }
}

#define ARG_FILENAME 1
#define ARG_SEED 2

int main(int argc, char **argv) {
    if (argc <= ARG_FILENAME) {
        cout << "Faltam parametros" << endl;
        cout << "./main <caminho> <semente>" << endl;
        return 1;
    }

    long long seed;
    if (argc <= ARG_SEED) {
        seed = time(0);
    } else {
        seed = stoi(argv[ARG_SEED]);
    }
    srand(seed);
    cout << "Seed: " << seed << endl;

    char* filename = argv[ARG_FILENAME];
    Knapsack *ks = Knapsack::read_knapsack_instance(filename);
    construct_initial_solution(ks, seed);
    cout << *ks << endl;

    cout << "Starting simulated annealing..." << endl;
    simulated_annealing(ks);

    delete ks;
}

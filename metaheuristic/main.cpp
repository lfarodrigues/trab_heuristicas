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

void run_test(const char* filename, long long seed) {
    cout << filename << endl;
    srand(seed);
    cout << "Seed: " << seed << endl;
    Knapsack *ks = Knapsack::read_knapsack_instance(filename);
    construct_initial_solution(ks, seed);
    cout << *ks << endl;

    simulated_annealing(ks);
    delete ks;
}

int main(int argc, char **argv) {
    auto files = {
        "../kpcg_instances/C1_BPPC_8_0_9.txt_0.1.dat",
//        "../kpcg_instances/C3_BPPC_1_0_2.txt_0.1.dat",
//        "../kpcg_instances/C10_BPPC_5_0_5.txt_0.1.dat",
//        "../kpcg_instances/R1_BPPC_2_0_5.txt_0.1.dat",
//        "../kpcg_instances/R3_BPPC_4_0_9.txt_0.1.dat",
//        "../kpcg_instances/R10_BPPC_1_0_6.txt_0.1.dat",
//        "../kpcg_instances/test_1000_2000_r0.05-0.dat",
//        "../kpcg_instances/HB10.dat",
//        "../kpcg_instances/HB11.dat",
//        "../kpcg_instances/HB12.dat",
    };

    auto seeds = {
        5953, 6143, 6311, 6481, 6679, 6841, 7001, 7211, 7417, 7573,
    };

    for (auto file : files) {
        for (auto seed : seeds) {
            run_test(file, seed);
            cout << endl << endl;
        }
    }
}

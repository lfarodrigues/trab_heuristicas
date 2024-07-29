#include <math.h>
#include <random>
#include <ctime>
#include "simulated_annealing.h"
#include "knapsack.h"
#include "item.h"

void simulated_annealing(Knapsack *ks) {
    float alpha = 0.99999999;
    
    int cmax = 50000; // numero de loops

    int t_o = 200;
    int c = 0;
    int t = t_o;
    int temp_change = cmax;
    int best_value = ks->get_value();
    int best_weight = ks->get_weight();
    int best_num_items = ks->get_num_items();
    
    int tempChange = cmax;

    srand(time(0)); // gerador de numeros aleatorios

    for (c; c < cmax; c++){
        int in = ks->pick_random_item();      // escolhemos um item aleatorio
        int out = ks->get_minor_value_item(); // escolhemos o item de menor valor/peso da mochila

        int curr_value = ks->get_value();

        if (ks->change_item(in, out)) { // foi capaz de inserir o item 
            int new_value = ks->get_value();
            int delta = new_value - curr_value;

            double u = static_cast<double>(rand()) / RAND_MAX;
            
            if(delta>0 || exp(-fabs(delta)/t)>u) {
                temp_change-=1;
                if (temp_change%10==0)
                    t=alpha*t;
                if (ks->get_value() >= best_value) {
                    best_value = ks->get_value();
                    best_weight = ks->get_weight();
                    best_num_items = ks->get_num_items();
                }
            } else { // reverte
                ks->change_item(out, in);
            }
        }
    }

    cout << "Finished" << endl << endl;
    cout << "Value: " << best_value << endl;
    cout << "Weight: " << best_weight << endl;
    cout << "Items: " << best_num_items << endl;
}

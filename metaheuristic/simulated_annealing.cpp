#include <math.h>
#include "simulated_annealing.h"
#include "knapsack.h"
#include "item.h"

void simulated_annealing(Knapsack *ks, float ti, float tf, int max_iters, float cooling) {
    while(ti > tf) {
        for(int i = 0; i < max_iters; i++) {
            int id_in = ks->pick_random_item();
            int id_out = ks->get_minor_value_item();
            int curr_value = ks->get_value();
            
            if(ks->change_item(id_in, id_out)) { // se consegue aplicar a alteração
                int delta = ks->get_value() - curr_value; 
                if(delta > 0 || exp(-delta / ti) > ((double)rand() / RAND_MAX)) { // se aumenta o valor da mochila com a alteração

                } else {
                    ks->change_item(id_out, id_in);
                }
            }        
        }

        ti *= cooling;
    }
}
void do_step_on_neighborhood() {

}
void evaluate() {

}
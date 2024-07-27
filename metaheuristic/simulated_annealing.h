#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

class Knapsack;

void simulated_annealing(Knapsack *ks, float ti, float tf, int max_iters, float cooling);
void do_step_on_neighborhood();
void evaluate();

#endif
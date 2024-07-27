#ifndef ITEM_H
#define ITEM_H
#include <vector>
#include <map>

using namespace std;
// Interface
class Item
{
    private:
        int id;
        int value;
        int weight;
        int is_in_kanapsack;
    public:
        Item();
        Item(int id, int value, int weight);
        ~Item();

        void set_value(int value) { this->value = value; }
        void set_weight(int weight) { this->weight = weight; }
        void set_is_in_knapsack(int x) { this->is_in_kanapsack = x; }
        
        int get_id() const {return this->id; }
        int get_value() const { return this->value; }
        int get_weight() const { return this->weight; }
        int get_is_in_knapsack() const { return this->is_in_kanapsack; }
};

#endif
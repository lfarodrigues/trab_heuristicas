#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <memory>
using namespace std;

class Item;

class Knapsack
{
    private:
        int max_weight;
        int weight;
        int value;
        int num_items;
        int minor_value_item;

        // shared memory
        map<int, Item> *items; 
        shared_ptr<vector<vector<int>>> conflict_matrix;

        void update_minor_value_item(int id);
        int search_minor_value_item();
        //set<int> knapsack_itens_ids;
    public:
        Knapsack(int max_weight, map<int, Item> *items, shared_ptr<vector<vector<int>>> conflict_matrix);
        ~Knapsack();

        static Knapsack* read_knapsack_instance(const char* path);

        bool add_item(int id);
        void remove_item(int id);
        
        int get_max_weight() const { return this->max_weight; }
        int get_weight() const { return this->weight; }
        int get_value() const { return this->value; }
        int get_num_items() const { return this->num_items; }
        int get_minor_value_item() const { return this->minor_value_item; }
        int pick_random_item_knapsack();
        int pick_random_item();

        bool change_item(int item_in, int item_out);
        bool has_conflict(int id);

        vector<int> get_items_in_knapsack();

        int is_item_in_knapsack(int id);
        map<int, Item>& get_items_set() { return *(this->items); } // returns the item set
        
        void show_items_set();
        void show_conflict_matrix();
        //set<int>& get_items_in_knapsack() { return this->knapsack_itens_ids; } // returns the list of itens ids in knapsack

        friend ostream& operator<<(ostream& os, const Knapsack& ks);
};

#endif

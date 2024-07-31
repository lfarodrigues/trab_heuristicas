#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include "knapsack.h"
#include "item.h"

// Implementation
Knapsack::~Knapsack() {
    delete items;

}
Knapsack::Knapsack(int max_weight, map<int, Item> *items, shared_ptr<vector<vector<int>>> conflict_matrix)
{
    if(!items || !conflict_matrix) {
        throw invalid_argument("items or conflict matrix ptr null!");
    }

    this->max_weight = max_weight;
    this->weight = 0;
    this->value = 0;
    this->items = items;
    this->num_items = 0;
    this->minor_value_item = -1;
    this->conflict_matrix = conflict_matrix;
}

Knapsack* Knapsack::read_knapsack_instance(const char* path)
{
    int n, c, v, p, w; // max weight
    char line[256];

    map<int, Item> *items = new map<int, Item>();
    shared_ptr<vector<vector<int>>> conflict_matrix;
    
    FILE *hdl = fopen(path, "r");

    if(!hdl) {
        cout << "The file doest not exist" << endl;
        return NULL;
    }

    // Lê o arquivo linha por linha
    while (fgets(line, sizeof(line), hdl)) {
        if (strncmp(line, "param n := ", 11) == 0) {
            // Extrai o valor de n
            sscanf(line, "param n := %d;", &n);
            cout << "n: " << n << endl;
        } else if (strncmp(line, "param c := ", 11) == 0) {
            // Extrai o valor de c
            sscanf(line, "param c := %d;", &c);
            cout << "c: " << c << endl;
        } else if ((strncmp(line, "param : V : p w :=", 18) == 0) || (strncmp(line, "param: V : p w :=", 17) == 0)) {
            // Ignora o cabeçalho e lê os dados até encontrar um ';'
            while (fgets(line, sizeof(line), hdl)) {
                if (strchr(line, ';') != NULL) {
                    break; // Encontra o ponto e vírgula e sai do loop
                }
                // Processa os dados conforme necessário
                sscanf(line, "%d %d %d", &v, &p, &w);

//                cout << "v: " << v << " p: " << p << " w: " << w << endl;

                Item item(v, p, w);
                (*items)[v] = item;
            }   
        } else if (strncmp(line, "set E :=", 8) == 0){ // read the conflict nodes and fill the conflict matrix
            conflict_matrix = make_shared<vector<vector<int>>>(n, vector<int>(n, -1));
            while (fgets(line, sizeof(line), hdl)) {
                int id1, id2;
                sscanf(line, "%d %d", &id1, &id2);
                (*conflict_matrix)[id1][id2] = 1;
            }
        }
    }

    fclose(hdl);

    Knapsack *ks = new Knapsack(c, items, conflict_matrix);
    return ks;
}

// Passa o id do item para adicionar na mochila
bool Knapsack::add_item(int id) {
    auto it = (*items).find(id); // na maioria das vezes acesso em tempo cte
    if(it == (*items).end()) {
        cout << "Item not found in items dictionary!" << endl;
        return false;
    }
    else if(it->second.get_weight() + this->weight <= this->max_weight 
            && !it->second.get_is_in_knapsack()
            && !this->has_conflict(id)){
        Item item = it->second;
        this->weight += item.get_weight();
        this->value += item.get_value();
        item.set_is_in_knapsack(1);
        this->num_items++;

        // update in map
        (*items).erase(id);
        (*items)[id] = item;

        this->update_minor_value_item(id);

#ifdef DEBUG
        cout << "Item added! " << "New weight: " << this->weight << " New value: " << this->value << endl;
#endif
        
        return true;
    } else {
        //cout << "The knapsack is full or item already added!" << endl;
        return false;
    }
}

void Knapsack::update_minor_value_item(int id) {
    if(this->minor_value_item < 0) 
        this->minor_value_item = id;
    else if((*items)[this->minor_value_item].get_is_in_knapsack()){     
        float proportion_item = (*items)[id].get_value()/(*items)[id].get_weight();
        int proportion_min = (*items)[this->minor_value_item].get_value()/(*items)[this->minor_value_item].get_weight();

        if(proportion_item < proportion_min) {
            this->minor_value_item = id;
        }
    }
}

int Knapsack::search_minor_value_item() {
    vector<int> ids = this->get_items_in_knapsack();
    int minor = ids[0];
    for(int i = 1; i < ids.size(); i++) {
        float curr_item_prop = (*items)[ids[i]].get_value()/(*items)[ids[i]].get_weight();
        float minor_prop = (*items)[minor].get_value()/(*items)[minor].get_weight();
        if (curr_item_prop < minor_prop)
            minor = ids[i];
    }

    return minor;
}

// Passa o id do item para remover da mochila
void Knapsack::remove_item(int id) {
    if((*items)[id].get_is_in_knapsack()){ // se o item está na mochila
        Item item = (*items)[id];
        this->value -= item.get_value();
        this->weight -= item.get_weight();
        this->num_items--;
        item.set_is_in_knapsack(0);

        (*items).erase(id);
        (*items)[id] = item;
        
        if (id == this->minor_value_item) 
            this->minor_value_item = this->search_minor_value_item();
    }
}

int Knapsack::is_item_in_knapsack(int id) {
    auto it = (*items).find(id);
    if(it == (*items).end()) 
        return -1; // id de item nao encontrado

    return (*items)[id].get_is_in_knapsack();
}

int Knapsack::pick_random_item_knapsack(){
        // Cria um vetor de chaves do mapa de itens
        vector<int> ids = get_items_in_knapsack();
    
        // Gera um índice aleatório
        int random_index = std::rand() % ids.size();
        int random_key = ids[random_index];
        
        return random_key;
}

int Knapsack::pick_random_item(){
    // Gera um índice aleatório
    int random_index = std::rand() % (*items).size();
    return random_index;
}

bool Knapsack::change_item(int item_in, int item_out) {
    Item in = (*items)[item_in];
    Item out = (*items)[item_out];

    if(!(*items)[item_in].get_is_in_knapsack() && (*items)[item_out].get_is_in_knapsack()){ // se o item que estamos adicionando nao estiver na mochila e o retirado estiver
        // se cabe
        if(this->get_weight() + in.get_weight() <= this->max_weight) {
            this->add_item(item_in);
            return true;
        }
        // se nao cabe mas, pode substituir
        else if ( this->get_weight() - out.get_weight() + in.get_weight() <= this->max_weight ) {
            this->remove_item(item_out);
            this->add_item(item_in);
            return true;
        }
    }

    return false;
}

bool Knapsack::has_conflict(int id) {
    vector<int> ks_ids = this->get_items_in_knapsack();
    // get the
    for(auto ks_id : ks_ids)
        if((*conflict_matrix)[ks_id][id]==1 || (*conflict_matrix)[id][ks_id]==1){
            //cout << "Conflict!" << endl;
            return true;
        }

    return false;
}

vector<int> Knapsack::get_items_in_knapsack() {
    vector<int> items_in_knapsack;
    for (const auto& pair : (*items)) {
        if (pair.second.get_is_in_knapsack()) {
            items_in_knapsack.push_back(pair.first);
        }
    }
    return items_in_knapsack;
}

void Knapsack::show_items_set(){
    if(this->items == NULL) {
        cout << "Item set not initialized!" << endl;
        return;
    } 
    for(auto& item : this->get_items_set()) {
        int id = item.second.get_id();
        int value = item.second.get_value();
        int weight = item.second.get_weight();

        cout << "Item: " << id << " Value: " << value << " Weight: " << weight << endl;
    }
}

void Knapsack::show_conflict_matrix(){
    if (!this->conflict_matrix) {
        cout << "Matriz não inicializada." << std::endl;
        return;
    }
    for (const auto& row : *(this->conflict_matrix)) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << std::endl;
    }
}

ostream& operator<<(ostream& os, const Knapsack& ks){                
    os << "{Knapsack {\"weight\": \"" << (ks.get_weight()) << "\", \"value\": \"" << (ks.get_value()) << "\", \"num_itens\": \"" << (ks.get_num_items()) << "\"}}";     
    return os;
}

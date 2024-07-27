#include "item.h"

Item::Item()
{

}
Item::Item(int id, int value, int weight)
{
    this->id = id;
    this->value = value;
    this->weight = weight;
    this->is_in_kanapsack = 0;
}

Item::~Item()
{

}

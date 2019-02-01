#include "item.h"
#include <iostream>
Item::Item(std::string name, double cost) {
    this->name = name;
    this->cost = cost;
}

bool operator==(Item item1, Item item2) {
    return item1.name == item2.name;
}

bool operator!=(Item item1, Item item2) {
    return item1.name != item2.name;
}

bool operator<(Item item1, Item item2) {
    return item1.name < item2.name;
}

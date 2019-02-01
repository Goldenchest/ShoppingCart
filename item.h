#include <string>
class Item {
    public:
        Item(std::string name, double cost);
        double cost;
        std::string name;
};
bool operator==(Item item1, Item item2);
bool operator!=(Item item1, Item item2);
bool operator<(Item item1, Item item2);

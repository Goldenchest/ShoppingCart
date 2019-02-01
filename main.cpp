#include "shopping_cart.h"
#include <iostream>
using namespace std;

bool isEqual(double d1, double d2) { // Check if two doubles are equal
    return std::abs(d1 - d2) < 0.0001;
}

int main() {
    // Create catalog (desired: generate catalog by parsing catalog.csv)
    std::set<Item> catalog;
    catalog.insert(Item("apple", 1.2));
    catalog.insert(Item("orange", 2.4));
    catalog.insert(Item("banana", 0.6));
    catalog.insert(Item("pear", 0.9));
    // Initialize ShoppingCart
    ShoppingCart cart = ShoppingCart("MA", catalog); // Pretend we are in Massachusetts for now.
    // Initialize coupons (desired: generate coupons by parsing coupons.csv)
    std::vector<Coupon> coupons;
    coupons.push_back(Coupon("apple", 0.0, true));
    coupons.push_back(Coupon("pear", 0.4, false));
    // Shop
    cart.addToCart("apple", 1);
    cart.addToCart("orange", 1);
    cart.addToCart("apple", 4);
    cart.addToCart("pear", 5);
    cart.removeItem("apple", 1);
    cart.addToCart("banana", 3);
    cart.addToCart("pineapple", 1); // this should do nothing, because pineapple is not in catalog.
    cart.printCart();
    // Verify output
    assert(cart.getCount("apple") == 4);
    assert(cart.getCount("orange") == 1);
    assert(cart.getCount("banana") == 3);
    assert(cart.getCount("pineapple") == 0); // pineapple does not exist in catalog.
    cart.calculateCosts();
    // Verify pre-coupon costs
    assert(isEqual(cart.getPreTaxCost(), 13.5));
    assert(isEqual(cart.getSalesTax(), 0.84375));
    assert(isEqual(cart.getTotalCost(), 14.3438));
    //////////////////////////
    cout << "BEFORE COUPONS" << endl;
    cout << "Subtotal: " << cart.getPreTaxCost() << endl;
    cout << "Tax: " << cart.getSalesTax() << endl;
    cout << "Total: " << cart.getTotalCost() << endl;
    cout << "\nAFTER COUPONS:" << endl;
    cart.applyCoupons(coupons);
    // Verify post-coupon costs
    assert(isEqual(cart.getPreTaxCost(), 10.5));
    assert(isEqual(cart.getSalesTax(), 0.65625));
    assert(isEqual(cart.getTotalCost(), 11.1562));
    //////////////////////////
    cout << "Subtotal: " << cart.getPreTaxCost() << endl;
    cout << "Tax: " << cart.getSalesTax() << endl;
    cout << "Total: " << cart.getTotalCost() << endl;
}

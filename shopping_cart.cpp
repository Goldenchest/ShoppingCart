#include "shopping_cart.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>
using namespace std;

ShoppingCart::ShoppingCart(std::string geoLocation, const std::set<Item> &catalog) {
    m_taxPercent = 0.0625; // hard-code tax to be 6.25% for now. However, should use geoLocation to look up tax from taxes.csv
    m_catalog = catalog;
    m_preTaxCost = 0.0;
    m_totalSalesTax = 0.0;
}

void ShoppingCart::printCart() {
    cout << "PRINTING CART" << endl;
    for (auto it = m_cart.begin(); it != m_cart.end(); ++it) {
        std::string itemName = it->first;
        auto item = m_catalog.find(Item(itemName, -1.0));
        // print name, quantity, and cost
        cout << itemName << '\t' << it->second << '\t' << item->cost << endl;
    }
    cout << endl;
}

void ShoppingCart::addToCart(std::string itemName, int quantity) {
    if (quantity < 1) {
        return;
    }
    auto item = m_catalog.find(Item(itemName, -1.0));
    if (item == m_catalog.end()) { // item not in catalog
        return;
    }
    auto it = m_cart.find(itemName);
    if (it == m_cart.end()) { // item not in cart
        m_cart.insert(std::make_pair(itemName, quantity));
        m_shadowCart.insert(std::make_pair(itemName, quantity));
    } else { // item already in cart
        it->second += quantity; // add quantity to cart
        it = m_shadowCart.find(itemName);
        assert(it != m_shadowCart.end());
        it->second += quantity; // add to shadow cart
    }
}

void ShoppingCart::clearCart() {
    m_cart.clear();
    m_shadowCart.clear();
}

void ShoppingCart::removeItem(std::string itemName, int quantity) {
    if (quantity < 1) {
        return;
    }
    auto item = m_catalog.find(Item(itemName, -1.0));
    if (item == m_catalog.end()) { // item not in catalog
        return;
    }
    // Remove from m_cart
    auto it = m_cart.find(itemName);
    if (it == m_cart.end()) {
        return;
    }
    // it->second is quantity of item
    if (it->second > quantity) { // if cart has more than quantity
        it->second -= quantity; // decrement quantity
    } else {
        m_cart.erase(itemName); // else remove item entirely
    }
    // Remove from m_shadowCart
    it = m_shadowCart.find(itemName);
    if (it == m_cart.end()) {
        return;
    }
    it->second -= quantity; // m_shadowCart can have negative quantity
}

void ShoppingCart::removeAll(std::string itemName) {
    m_cart.erase(itemName);
    m_shadowCart.erase(itemName);
}

void ShoppingCart::applyCoupon(Coupon coupon) {
    auto item = m_catalog.find(Item(coupon.itemName, -1.0));
    if (item == m_catalog.end()) { // item not in catalog
        return; // coupon does nothing
    }
    // Erase the item and re-insert it with updated cost
    m_catalog.erase(item);
    // Will do nothing if coupon.discount == 0.0
    m_catalog.insert(Item(item->name, item->cost * (1.0 - coupon.discount)));
    if (coupon.bogo) {
        auto it = m_shadowCart.find(coupon.itemName);
        if (it == m_shadowCart.end()) { // item not in m_shadowCart
            return; // nothing more to do
        }
        it->second -= 1; // bogo means one of the items is free
    }
    calculateCosts(); // recalculate costs of cart
    cout << "COUPON APPLIED: " << coupon.itemName << "\tDISCOUNT " << coupon.discount << "\tBOGO " << coupon.bogo << endl;
}

void ShoppingCart::applyCoupons(std::vector<Coupon> coupons) {
    for (int i=0; i<coupons.size(); i++) {
        applyCoupon(coupons[i]);
    }
}

int ShoppingCart::getCount(std::string itemName) {
    auto it = m_cart.find(itemName);
    if (it == m_cart.end()) {
        return 0;
    }
    return it->second; // this is the quantity of the item
}

void ShoppingCart::calculateCosts() {
    m_preTaxCost = 0.0;
    m_totalSalesTax = 0.0;
    // Calculate costs using m_shadowCart (it is the one affected by coupons)
    for (auto it=m_shadowCart.begin(); it != m_shadowCart.end(); ++it) {
        std::string itemName = it->first;
        int itemQuantity = std::max(it->second, 0); // treat negative quantity as 0
        auto item = m_catalog.find(Item(itemName, -1.0));
        assert(item != m_catalog.end()); // assert that each item exists in catalog
        double itemCost = item->cost;
        m_preTaxCost += itemCost * itemQuantity; // increment total cost
        m_totalSalesTax += itemCost * itemQuantity * m_taxPercent; // increment sales tax
    }
}

double ShoppingCart::getSalesTax() {
    return m_totalSalesTax;
}

double ShoppingCart::getPreTaxCost() {
    return m_preTaxCost;
}

double ShoppingCart::getTotalCost() {
    return m_preTaxCost + m_totalSalesTax;
}

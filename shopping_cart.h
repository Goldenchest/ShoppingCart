#include "item.h"
#include "coupon.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>

class ShoppingCart {
    private:
        std::set<Item> m_catalog;
        std::map<std::string, int> m_cart;
        std::map<std::string, int> m_shadowCart; // apply bogo coupons
        double m_taxPercent;
        double m_preTaxCost;
        double m_totalSalesTax;
    public:
        ShoppingCart(std::string geoLocation, const std::set<Item> &catalog);
        void printCart();
        void addToCart(std::string itemName, int quantity);
        void clearCart();
        void removeItem(std::string itemName, int quantity);
        void removeAll(std::string itemName);
        void applyCoupon(Coupon coupon);
        void applyCoupons(std::vector<Coupon> coupons);
        int getCount(std::string itemName);
        void calculateCosts();
        double getSalesTax();
        double getPreTaxCost();
        double getTotalCost();
};

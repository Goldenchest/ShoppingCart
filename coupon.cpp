#include "coupon.h"

Coupon::Coupon(std::string itemName, double discount, bool bogo) {
    this->itemName = itemName;
    this->discount = discount;
    this->bogo = bogo;
}

#include <string>
class Coupon {
    public:
        std::string itemName;
        double discount;
        bool bogo;
        Coupon(std::string itemName, double discount, bool bogo);
};

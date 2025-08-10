#include <iostream>

class Burger {
    public:
    std::string breadType;
    std::string sauceType;
    std::string meatType;
    std::string cheeseType;
        void orderBurger() {
            std::cout << "Ordering a burger with: " 
                      << breadType << ", " 
                      << sauceType << ", " 
                      << meatType << ", " 
                      << cheeseType << std::endl;
        }
};


class BurgerBuilder{
    Burger burger;
    public:
        BurgerBuilder& setBreadType(const std::string& bread) {
            burger.breadType = bread;
            return *this;
        }

        BurgerBuilder& setSauceType(const std::string& sauce) {
            burger.sauceType = sauce;
            return *this;
        }

        BurgerBuilder& setMeatType(const std::string& meat) {
            burger.meatType = meat;
            return *this;
        }

        BurgerBuilder& setCheeseType(const std::string& cheese) {
            burger.cheeseType = cheese;
            return *this;
        }

        Burger build() {
            return burger;
        }
};

int main(){
     BurgerBuilder builder;
     Burger myBurger = builder.setBreadType("Whole Wheat").setSauceType("Ketchup").setMeatType("Chicken").setCheeseType("Cheddar").build();
     myBurger.orderBurger();
     Burger myVeggieBurger = builder.setBreadType("Gluten Free").setSauceType("Mustard").setCheeseType("Vegan Cheese").build();
     myVeggieBurger.orderBurger();
     return 0;
}
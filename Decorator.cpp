//// coffee -> class
/// coffee with whipped cream -> 


/// component / decorator(component)
#include <iostream>

class Coffee {
public: 
    virtual void prepare() const = 0; // Pure virtual function
    virtual double cost() const = 0;
};


class SimpleCoffee : public Coffee {
public: 
    void prepare() const override {
        std::cout << "Preparing simple coffee." << std::endl;
    }
    double cost() const override {
        return 1.0; // Base cost of simple coffee
    }
};  

// -- Decorator---
class CoffeeDecorator : public Coffee {
public:

 Coffee* coffee;
    CoffeeDecorator(Coffee* coffee) : coffee(coffee) {}
    void prepare() const override {
        coffee->prepare(); // Call the wrapped coffee's prepare method
    }
    double cost() const override {
        return coffee->cost(); 
    }
};



class MilkDecorator : public CoffeeDecorator {
public: 
    MilkDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    void prepare() const override {
        CoffeeDecorator::prepare(); // Call the base class's prepare method
        std::cout << "Adding milk." << std::endl;
    }
    double cost() const override {
        return coffee->cost() + 0.5; // Add cost of milk
    }
};


class WhippedCreamDecorator : public CoffeeDecorator {
public:
    WhippedCreamDecorator(Coffee* coffee) : CoffeeDecorator(coffee) {}

    void prepare() const override {
        CoffeeDecorator::prepare(); // Call the base class's prepare method
        std::cout << "Adding whipped cream." << std::endl;
    }
    double cost() const override {
        return coffee->cost() + 0.7; // Add cost of whipped cream
    }
};



int main(){
    Coffee* coffee = new SimpleCoffee();
    coffee = new MilkDecorator(coffee);
    coffee = new WhippedCreamDecorator(coffee);

    coffee->prepare();
    std::cout << "Total cost: " << coffee->cost() << std::endl;

    delete coffee;
    return 0;
}
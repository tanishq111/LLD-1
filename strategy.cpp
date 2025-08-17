// payment strategeis -> neft,debit,credit
#include <iostream>

class PaymentStrategy {
public: 
    virtual void pay(int amount) = 0; 
};


class NEFTPayment : public PaymentStrategy {
public: 
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using NEFT." << std::endl;
    }
};

class DebitCardPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Debit Card." << std::endl;
    }
};

class CreditCardPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Credit Card." << std::endl;
    }
};


class ShoppinCart{
    private:
    int totalAmount;
    PaymentStrategy* paymentStrategy;
public:
    ShoppingCart() : totalAmount(0), paymentStrategy(nullptr) {}

    void setPaymentStrategy(PaymentStrategy* strategy) {
        paymentStrategy = strategy;
    }

    void addItem(int price) {
        totalAmount += price;
    }

    void checkout() {
        if (paymentStrategy) {
            paymentStrategy->pay(totalAmount);
        } else {
            std::cout << "No payment strategy set." << std::endl;
        }
    }
};


int main(){
    ShoppinCart cart;
    cart.addItem(100);
    cart.addItem(200);
    cart.setPaymentStrategy(new NEFTPayment());
    ////
    cart.setPaymentStrategy(new DebitCardPayment());
    cart.checkout();
}
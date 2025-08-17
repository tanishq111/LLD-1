#include <iostream>

class BankAccount {
public:
    virtual void deposit(double amount) = 0; // Pure virtual function
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() const = 0;
};


class BankAccountImpl : public BankAccount { // internet banking implementation
    public:
    void  deposit(double amount) override {
        balance += amount;
        std::cout << "Deposited: " << amount << ", New Balance: " << balance << std::endl;
    }

    void withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
            std::cout << "Withdrew: " << amount << ", New Balance: " << balance << std::endl;
        } else {
            std::cout << "Insufficient funds for withdrawal of: " << amount << std::endl;
        }
    }

    double getBalance() const override {
        return balance;
    }
};


class DebitCard : public BankAccount {
     BankAccountImpl* account;
public:
    DebitCard(BankAccountImpl* acc) : account(acc) {} // constructor to initialize the account

    void deposit(double amount) override {
        account->deposit(amount);
    }

    void withdraw(double amount) override {
        account->withdraw(amount);
    }

    double getBalance() const override {
        return account->getBalance();
    }
};
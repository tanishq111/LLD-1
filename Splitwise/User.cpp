#include <iostream>
#include <string>
using namespace std;

class User{
    private:
        string name;
        string email;
        double balance;
    public:
        User(string name, string email);
        void addExpense(double amount);
        void addIncome(double amount);
        double getBalance();
        string getName();
        string getEmail();
};
#include <iostream>
#include "User.cpp"

class Split {
   User user;
   double amount;
   public:
       Split(User user, double amount);
       User getUser();
       double getAmount();
};





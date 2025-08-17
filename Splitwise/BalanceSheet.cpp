#include<map>
#include<string>
#include "User.cpp"
#include "Split.cpp"

class BalanceSheet {
    map<string,map<string,double>> balanceSheet;

    public:
     void updateBalance(User paidBy, vector<Split> splits ){
        for(auto split:splits){
            balanceSheet[paidBy.getName()][split.getUser().getName()] += split.getAmount();
            balanceSheet[split.getUser().getName()][paidBy.getName()] -= split.getAmount();
        }
     }


     void settleBalance(User payer, User payee, double amount) {
        balanceSheet[payer.getName()][payee.getName()] -= amount;
        balanceSheet[payee.getName()][payer.getName()] += amount;
     }

     void printBalanceSheet() {
        for (const auto& payer : balanceSheet) {
            cout << "Payer: " << payer.first << endl;
            for (const auto& payee : payer.second) {
                cout << "  Payee: " << payee.first << ", Amount: " << payee.second << endl;
            }
        }
     }
};

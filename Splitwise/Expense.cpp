#include <string>
#include "User.cpp"
#include "Group.cpp"
#include "Split.cpp"

class Expense{
    double amount;
    string description;
    User paidBy;
    Group group;
    vector<Split> splits;
    public:
    Expense(double amt, const string& desc, const User& user, const Group& grp)
        : amount(amt), description(desc), paidBy(user), group(grp) {}

    double getAmount() const {
        return amount;
    }

    string getDescription() const {
        return description;
    }

    User getPaidBy() const {
        return paidBy;
    }

    Group getGroup() const {
        return group;
    }
};

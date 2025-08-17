#include "User.cpp"
#include "Group.cpp"
#include "Expense.cpp"
#include "Balance.cpp"

class SplitWiseService {
    static SplitWiseService* instance;
    map<string, User> users;
    map<string, Group> groups;
    map<string, Expense> expenses;
    SplitWiseService();

    public:
    static SplitWiseService* getInstance() {
        if (!instance) {
            instance = new SplitWiseService();
        }
        return instance;
    }

    User CreateUser(const string& name, const string& email) {
        User user(name, email);
        users[email] = user;
        return user;
    }

    Group CreateGroup(const string& groupName, const vector<User>& members) {
        Group group(groupName, members);
        groups[groupName] = group;
        return group;
    }

    Expense addExpense(string expenseId, string description, double amount, string paidBy,
                                   SplitType splitType, map<string,double> splitData, string groupName) {
                Expense expense(amount, description, users[paidBy], groups[groupName]);
                expenses[expenseId] = expense;
                                    
                // if splitType is -> % or Exact??
                map<string, double> splits;
                for (const auto& [user, share] : splitData) {
                    splits[user] = share;
                }

                SplitStrategy strategy = SplitStrategyFactory::createSplitStrategy(splitType);
                vector<Split> splits = strategy->splitAmount(amount, splits);
                BalanceSheet::updateBalances(users[paidBy], splits);
                return expense;
    }

    // settle method
}
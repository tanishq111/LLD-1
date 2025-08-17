#include <vector>
#include "User.cpp"
#include "Split.cpp"

enum SplitType {
    EXACT,
    PERCENTAGE,
    EQUAL,
};

class SplitStrategy {
    virtual vector<Split> splitAmount(double totalAmount, vector<User> users) = 0;
};


class EqualSplitStrategy : public SplitStrategy {  /// revisit
    vector<Split> splitAmount(double totalAmount, map<User,int> users) override {
        vector<Split> splits;
        double equalShare = totalAmount / users.size();
        for (const auto& [user, share] : users) {
            splits.emplace_back(user, equalShare);
        }
        return splits;
    }
};


class PercentageSplitStrategy : public SplitStrategy {
    vector<Split> splitAmount(double totalAmount, map<User,int> users) override {
        vector<Split> splits;
        for (const auto& [user, share] : users) {
            double percentage = share;  // Assuming User has a method to get their percentage
            splits.emplace_back(user, totalAmount * percentage / 100);
        }
        return splits;
    }
};


class ExactSplitStrategy : public SplitStrategy {
    vector<Split> splitAmount(double totalAmount, map<User,int> users) override {
        vector<Split> splits;
        for (const auto& [user, share] : users) {
            double exactAmount = share;  // Assuming User has a method to get their exact amount
            splits.emplace_back(user, exactAmount);
        }
        return splits;
    }
};



class SplitStrategyFactory {
public:
    static unique_ptr<SplitStrategy> createSplitStrategy(SplitType type) {
        switch (type) {
            case EQUAL:
                return make_unique<EqualSplitStrategy>();
            case PERCENTAGE:
                return make_unique<PercentageSplitStrategy>();
            case EXACT:
                return make_unique<ExactSplitStrategy>();
            default:
                throw invalid_argument("Invalid split type");
        }
    }
};

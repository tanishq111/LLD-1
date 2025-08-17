#include<iostream>


class ExpenseReport {
    private:
    int amount; 
    std::string description; 
     public:
    ExpenseReport(int amt, const std::string& desc) : amount(amt), description(desc) {}
    int getAmount() const {
        return amount;
    }
    std::string getDescription() const {
        return description;
    }
};


class Approver{
    public:
    Approver *next; // pointer to the next approver in the chain
    virtual void setNext(Approver* next) {
        this->next = next;
    }

    virtual void process(ExpenseReport* report) {
            if(next != nullptr) {
                next->process(report);
            } else {
                std::cout << "No approver available for this report." << std::endl;
            }
    }
};


class Manager : public Approver {
    private:
    int approvalLimit; // maximum amount this manager can approve
    public:
    Manager(int limit) : approvalLimit(limit) {}
    void process(ExpenseReport* report) override { // has-a
        if(report->getAmount() <= approvalLimit) {
            std::cout << "Manager approved the expense report: " << report->getDescription() << std::endl;
        } else {
            Approver::process(report);
        }
    }
};

class Director : public Approver {
    private:
    int approvalLimit; // maximum amount this director can approve
    public:
    Director(int limit) : approvalLimit(limit) {}
    void process(ExpenseReport* report) override {
        if(report->getAmount() <= approvalLimit) {
            std::cout << "Director approved the expense report: " << report->getDescription() << std::endl;
        } else {
            Approver::process(report);
        }
    }
};

class VicePresident : public Approver {
    private:
    int approvalLimit; // maximum amount this vice president can approve
    public:
    VicePresident(int limit) : approvalLimit(limit) {}
    void process(ExpenseReport* report) override {
        if(report->getAmount() <= approvalLimit) {
            std::cout << "Vice President approved the expense report: " << report->getDescription() << std::endl;
        } else {
            Approver::process(report);
        }
    }
};



int main() {
    // Create approvers
    Manager manager(1000);
    Director director(5000);
    VicePresident vp(10000);

    // Set up the chain of responsibility
    manager.setNext(&director);
    director.setNext(&vp);

    // Create expense reports
    ExpenseReport report1(800, "Office Supplies");
    ExpenseReport report2(3000, "Conference Expenses");
    ExpenseReport report3(12000, "New Equipment");

    // Process expense reports
    manager.process(&report1); // Should be approved by Manager
    manager.process(&report2); // Should be approved by Director
    manager.process(&report3); // Should be approved by Vice President

    return 0;
}
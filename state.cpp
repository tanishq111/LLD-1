#include <iostream>
#include <memory>
#include <string>

class VendingMachine; 

// State interface
class State {
public:
    virtual ~State() = default;
    virtual void insertCoin() = 0;
    virtual void ejectCoin() = 0;
    virtual void selectItem() = 0;
    virtual void dispenseItem() = 0;
protected:
    VendingMachine* m_machine;
};

// Context: The Vending Machine
class VendingMachine {
private:
    std::unique_ptr<State> m_currentState;
    int m_itemCount = 0;

    // Pointers to all possible states
    std::unique_ptr<State> m_noCoinState;
    std::unique_ptr<State> m_hasCoinState;
    std::unique_ptr<State> m_soldState;
    std::unique_ptr<State> m_emptyState;

    friend class NoCoinState;
    friend class HasCoinState;
    friend class SoldState;
    friend class EmptyState;

public:
    VendingMachine(int initialItemCount);

    void setState(std::unique_ptr<State> state) {
        m_currentState = std::move(state);
    }

    void insertCoin() { m_currentState->insertCoin(); }
    void ejectCoin() { m_currentState->ejectCoin(); }
    void selectItem() {
        m_currentState->selectItem();
        m_currentState->dispenseItem(); // Dispense is an internal action after selection
    }

    void releaseItem() {
        std::cout << "Dispensing an item..." << std::endl;
        if (m_itemCount > 0) {
            m_itemCount--;
        }
    }

    int getItemCount() const { return m_itemCount; }
};

// ConcreteState implementations
class NoCoinState : public State {
public:
    NoCoinState(VendingMachine* machine) { m_machine = machine; }
    void insertCoin() override;
    void ejectCoin() override { std::cout << "You haven't inserted a coin." << std::endl; }
    void selectItem() override { std::cout << "You selected an item, but there's no coin." << std::endl; }
    void dispenseItem() override { std::cout << "You need to pay first." << std::endl; }
};

class HasCoinState : public State {
public:
    HasCoinState(VendingMachine* machine) { m_machine = machine; }
    void insertCoin() override { std::cout << "You can't insert another coin." << std::endl; }
    void ejectCoin() override;
    void selectItem() override;
    void dispenseItem() override { std::cout << "No item dispensed." << std::endl; }
};

class SoldState : public State {
public:
    SoldState(VendingMachine* machine) { m_machine = machine; }
    void insertCoin() override { std::cout << "Please wait, we're already giving you an item." << std::endl; }
    void ejectCoin() override { std::cout << "Sorry, you already selected an item." << std::endl; }
    void selectItem() override { std::cout << "Selecting twice doesn't get you another item." << std::endl; }
    void dispenseItem() override;
};

class EmptyState : public State {
public:
    EmptyState(VendingMachine* machine) { m_machine = machine; }
    void insertCoin() override { std::cout << "You can't insert a coin, the machine is sold out." << std::endl; }
    void ejectCoin() override { std::cout << "You can't eject, you haven't inserted a coin yet." << std::endl; }
    void selectItem() override { std::cout << "You selected an item, but there are no items." << std::endl; }
    void dispenseItem() override { std::cout << "No items to dispense." << std::endl; }
};

// VendingMachine constructor needs to be after states are defined
VendingMachine::VendingMachine(int initialItemCount) : m_itemCount(initialItemCount) {
    m_noCoinState = std::make_unique<NoCoinState>(this);
    m_hasCoinState = std::make_unique<HasCoinState>(this);
    m_soldState = std::make_unique<SoldState>(this);
    m_emptyState = std::make_unique<EmptyState>(this);

    if (m_itemCount > 0) {
        m_currentState = std::make_unique<NoCoinState>(this);
    } else {
        m_currentState = std::make_unique<EmptyState>(this);
    }
}

// State method implementations that cause transitions
void NoCoinState::insertCoin() {
    std::cout << "You inserted a coin." << std::endl;
    m_machine->setState(std::make_unique<HasCoinState>(m_machine));
}

void HasCoinState::ejectCoin() {
    std::cout << "Coin returned." << std::endl;
    m_machine->setState(std::make_unique<NoCoinState>(m_machine));
}

void HasCoinState::selectItem() {
    std::cout << "You selected an item..." << std::endl;
    m_machine->setState(std::make_unique<SoldState>(m_machine));
}

void SoldState::dispenseItem() {
    m_machine->releaseItem();
    if (m_machine->getItemCount() > 0) {
        m_machine->setState(std::make_unique<NoCoinState>(m_machine));
    } else {
        std::cout << "Oops, out of items!" << std::endl;
        m_machine->setState(std::make_unique<EmptyState>(m_machine));
    }
}


void demonstrateState() {
    VendingMachine machine(2); // Vending machine with 2 items

    std::cout << "--- Test Case 1: Successful Purchase ---" << std::endl;
    machine.insertCoin();
    machine.selectItem();

    std::cout << "\n--- Test Case 2: Eject Coin ---" << std::endl;
    machine.insertCoin();
    machine.ejectCoin();
    machine.selectItem(); // Should fail

    std::cout << "\n--- Test Case 3: Second Purchase & Sold Out ---" << std::endl;
    machine.insertCoin();
    machine.selectItem();

    std::cout << "\n--- Test Case 4: Machine is Empty ---" << std::endl;
    machine.insertCoin(); // Should fail
    machine.selectItem(); // Should fail

    std::cout << "\nDemonstration complete. The machine's behavior changed based on its internal state." << std::endl;
}

int main() {
    demonstrateState();
    return 0;
}
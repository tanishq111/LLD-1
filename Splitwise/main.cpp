int main(){
    auto service = SplitwiseService::getInstance();

    auto u1 = service->createUser("U1", "Alice", "alice@mail.com");
    auto u2 = service->createUser("U2", "Bob", "bob@mail.com");
    auto u3 = service->createUser("U3", "Charlie", "charlie@mail.com");

    auto g1 = service->createGroup("G1", "Trip", {"U1", "U2", "U3"});

    // Expense: Alice paid 300, split equally
    service->addExpense("E1", "Dinner", 300, "U1", SplitType::EQUAL, {{"U1",0},{"U2",0},{"U3",0}}, "G1");

    // Expense: Bob paid 200, exact split
    service->addExpense("E2", "Snacks", 200, "U2", SplitType::EXACT, {{"U1",100},{"U2",50},{"U3",50}}, "G1");

    // Expense: Charlie paid 500, percentage split
    service->addExpense("E3", "Hotel", 500, "U3", SplitType::PERCENTAGE, {{"U1",40},{"U2",40},{"U3",20}}, "G1");

    service->printBalances();
}
#include <vector>
#include "User.cpp"

class Group{
    vector<User> users;
    string name;
    string description;
    public:
    void addUser(const User& user) {
        users.push_back(user);
    }

    vector<User> getUsers() const {
        return users;
    }
};
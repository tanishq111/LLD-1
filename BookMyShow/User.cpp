#include "Booking.cpp"
#include <vector>   // observer
#include "Observer.cpp"
class User{
    int userId;
    string name;
    string email;
    vector<Booking> bookingHistory;
    vector<string> preferences;
public:
    User(int id, const string& name, const string& email)
        : userId(id), name(name), email(email) {}

    int getUserId() const { return userId; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    void notify(){
        cout<<"Send Message for a movie";
    }
};

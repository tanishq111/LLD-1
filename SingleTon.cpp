#include <iostream>

class DataBaseConnection {
public:
    static DataBaseConnection& getInstance() {
        static DataBaseConnection instance;
        return instance;
    }
    void connect() {
        std::cout << "Connecting to database..." << std::endl;
    }
private:
    DataBaseConnection() { // private constructor -> cannot be instantiated from outside
        std::cout << "Creating database connection..." << std::endl;
    }
};


int main() {
    DataBaseConnection& dbConnection = DataBaseConnection::getInstance();
    dbConnection.connect();

    // Uncommenting the following line will cause a compilation error
    //DataBaseConnection anotherConnection = new DataBaseConnection(); // Error: constructor is private

    return 0;
}


// usecases:
// DB connections
// Loggers
// Configuration managers
// Hardware interfaces
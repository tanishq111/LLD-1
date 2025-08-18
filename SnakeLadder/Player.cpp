#include<string>
class Player {
     private:
     std::string name;
     int position;
     bool winner;

     public:
     Player(std::string name) : name(name), position(0), winner(false) {}

     std::string getName() const {
         return name;
     }

     int getPosition() const {
         return position;
     }

     bool isWinner() const {
         return winner;
     }

     void setPosition(int pos) {
         position = pos;
     }

     void setWinner(bool win) {
         winner = win;
     }
};
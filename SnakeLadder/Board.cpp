#include<map>
class Board{
     private:
     int size;
     std::map<int,int> snakes;
     std::map<int,int> ladders;

     public:
     Board(int size) : size(size) {}

     int getSize() const {
         return size;
     }

     void addSnake(int start, int end) {
         snakes[start] = end;
     }

     void addLadder(int start, int end) {
         ladders[start] = end;
     }

     int getNextPosition(int pos){ //next position 
        if(snakes.find(pos) != snakes.end()) {
            return snakes[pos]; // snake
        } else if(ladders.find(pos) != ladders.end()) {
            return ladders[pos]; // ladder
        }
        return pos;  
     }

     int displayCurrentState(){
         std::cout << "Board State:" << std::endl;
         std::cout << "Snakes:" << std::endl;
         for (const auto& pair : snakes) {
             std::cout << "  " << pair.first << " -> " << pair.second << std::endl;
         }
         std::cout << "Ladders:" << std::endl;
         for (const auto& pair : ladders) {
             std::cout << "  " << pair.first << " -> " << pair.second << std::endl;
         }
     }
};

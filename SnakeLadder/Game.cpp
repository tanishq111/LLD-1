#include "Board.cpp"
#include "Player.cpp"
#include "queue"
#include "Dice.cpp"
class Game{
    Board board;
    Dice dice;
    std::queue<Player> players;
    bool gameOver;
    Player currentPlayer;

    public:
    void addPlayer(const Player& player) {
        players.push(player);
    }

    void setupBoard(){
        board.addLadder(3, 22);
        board.addLadder(5, 8);
        board.addLadder(11, 26);
        board.addLadder(20, 29);
        board.addSnake(17, 4);
        board.addSnake(19, 7);
        board.addSnake(21, 9);
        board.addSnake(27, 1);
    }

    void makeAMove(){
        if(players.empty()) {
            std::cout << "No players in the game!" << std::endl;
            return;
        }

        // the player at front of the queue will make a move
        currentPlayer = players.front();
        players.pop();
        int nextpos = currentPlayer.getPosition() + dice.roll();
        movePlayer(currentPlayer, nextpos);
        if(checkWin(currentPlayer)){
            currentPlayer.setWinner(true);
            gameOver = true;
            return;
        }
    }

    void Play(){
        // this will keep calling makeAMove until the game is over
        while(!gameOver) {
            makeAMove();
        }
    }

    void movePlayer(Player player, int nextpos){
          if(nextpos > board.getSize()) {
            std::cout << player.getName() << " cannot move to " << nextpos << " as it exceeds board size." << std::endl;
            players.push(player); // re-queue the player
            return;
          }

          int nextPosition = board.getNextPosition(nextpos);
          player.setPosition(nextPosition);
          players.push(player);
    }

    bool checkWin(){
        return currentPlayer.getPosition() == board.getSize();
    }

};
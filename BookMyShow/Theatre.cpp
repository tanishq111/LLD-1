#include "Screen.cpp"
#include "Observer.cpp"
class Theater{
    std::vector<Screen> screens;
public:
    void addScreen(const Screen& screen) {
        screens.push_back(screen);
    }

/// create show
  void createShow(int screenNumber, int startTime, int endTime, const Movie& movie) {
      Show show(startTime, endTime, movie); // here you can set a pricing strategy
      addShowToScreen(screenNumber, show);
  }

    // add a show
    void addShowToScreen(int screenNumber, const Show& show) { // when action movie is addedd user should get a notification
        for (auto& screen : screens) {
            if (screen.getScreenNumber() == screenNumber) {
                screen.addShow(show);
                return;
            }
        }
        // assume i am adding an action movie
        actionMovieObserver.onMovieAdded(movie);
        std::cout << "Screen not found!" << std::endl;
    }

    void removeShowFromScreen(int screenNumber, const Show& show) {
        for (auto& screen : screens) {
            if (screen.getScreenNumber() == screenNumber) {
                screen.removeShow(show);
                return;
            }
        }
        std::cout << "Screen not found!" << std::endl;
    }
};

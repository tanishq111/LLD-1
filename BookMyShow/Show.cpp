#include "Movie.cpp"

class Show{
    int startTime; // in minutes from midnight
    int endTime;   // in minutes from midnight
    Movie movie;
    int Price; // for simplicity i am hardcoding price, you can implement a strategy pattern later
    // pricing strategy
public:
    Show(int start, int end, const Movie& movie)
        : startTime(start), endTime(end), movie(movie) {}

    // Getters for show details
    int getStartTime() const { return startTime; }
    int getEndTime() const { return endTime; }
    Movie getMovie() const { return movie; }
};

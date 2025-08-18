#include <vector>
#include <algorithm>
#include "User.cpp"
class MovieSubject { // observers
public:
    virtual void onMovieAdded(const Movie& movie) = 0;
    virtual void onMovieRemoved(const Movie& movie) = 0;
};


class ActionMovieObserver : public MovieSubject {
    vector<User*> users;
public:
    void addObserver(User* user) {
        users.push_back(user);
    }

    void removeObserver(User* user) {
        users.erase(std::remove(users.begin(), users.end(), user), users.end());
    }

    void notifyObservers(const Movie& movie) {
        for (auto& user : users) {
            user->notify();
        }
    }

    void onMovieAdded(const Movie& movie) override {
        if (movie.getGenre() == "Action") {
            std::cout << "Action movie added: " << movie.getTitle() << std::endl;
        }
        notifyObservers();
    }

};


class RomanticMovieObserver : public MovieSubject {
    vector<User*> users;
public:
    void addObserver(User* user) {
        users.push_back(user);
    }

    void removeObserver(User* user) {
        users.erase(std::remove(users.begin(), users.end(), user), users.end());
    }

    void notifyObservers(const Movie& movie) {
        for (auto& user : users) {
            user->notify(movie);
        }
    }

    void onMovieAdded(const Movie& movie) override {
        if (movie.getGenre() == "Romance") {
            std::cout << "Romantic movie added: " << movie.getTitle() << std::endl;
        }
        notifyObservers(movie);
    }

};
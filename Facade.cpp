#include <iostream>

class DVDPlayer {
public: 
    void on() const {
        std::cout << "DVD Player is now ON." << std::endl;
    }
    void off() const {
        std::cout << "DVD Player is now OFF." << std::endl;
    }
    void play(const std::string& movie) const {
        std::cout << "Playing movie: " << movie << std::endl;
    }
    void stop() const {
        std::cout << "Stopping the DVD Player." << std::endl;
    }
};

class Projector {
public:
    void on() const {
        std::cout << "Projector is now ON." << std::endl;
    }
    void off() const {
        std::cout << "Projector is now OFF." << std::endl;
    }
    void setInput(const std::string& input) const {
        std::cout << "Setting projector input to: " << input << std::endl;
    }
};



class SoundSystem {
public:
    void on() const {
        std::cout << "Sound System is now ON." << std::endl;
    }
    void off() const {
        std::cout << "Sound System is now OFF." << std::endl;
    }
    void setVolume(int level) const {
        std::cout << "Setting sound system volume to: " << level << std::endl;
    }
};

class HomeTheaterFacade {
public:
    HomeTheaterFacade(DVDPlayer* dvd, Projector* projector, SoundSystem* soundSystem)
        : dvdPlayer(dvd), projector(projector), soundSystem(soundSystem) {}

    void watchMovie(const std::string& movie) const {
        projector->on();
        projector->setInput("DVD");
        soundSystem->on();
        soundSystem->setVolume(10);
        dvdPlayer->on();
        dvdPlayer->play(movie);
    }

    void endMovie() const {
        dvdPlayer->stop();
        dvdPlayer->off();
        soundSystem->off();
        projector->off();
    }
};

int main(){
    DVDPlayer dvdPlayer;
    Projector projector;
    SoundSystem soundSystem;
    HomeTheaterFacade homeTheater(&dvdPlayer, &projector, &soundSystem);
    homeTheater.watchMovie("Inception");
    homeTheater.endMovie();
    return 0;
}
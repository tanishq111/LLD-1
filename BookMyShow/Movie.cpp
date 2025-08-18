class Movie{
    std::string title;
    std::string genre;
    int duration; // in minutes
public:
    Movie(const std::string& title, const std::string& genre, int duration)
        : title(title), genre(genre), duration(duration) {}

    std::string getTitle() const { return title; }
    std::string getGenre() const { return genre; }
    int getDuration() const { return duration; }
};

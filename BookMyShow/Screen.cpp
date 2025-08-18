class Screen{
    int screenNumber;
    std::vector<Show> shows;
public:
    Screen(int number) : screenNumber(number) {}

    void addShow(const Show& show) {
        shows.push_back(show);
    }

    // Other screen-related methods
};

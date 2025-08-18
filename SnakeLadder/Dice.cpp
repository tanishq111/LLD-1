class Dice{
    private:
    int sides;
    public:
    Dice(int s) : sides(s) {}
    int roll() {
        return rand() % sides + 1;
    }
};
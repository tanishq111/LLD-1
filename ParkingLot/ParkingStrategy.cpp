#include "ParkingSpot.cpp"
#include "ParkingFloor.cpp"

class ParkingStrategy{
    public:
    virtual ParkingSpot findParkingSpot(Vehicle* vehicle) = 0;
};


class BestFitParkingStrategy : public ParkingStrategy {
    public:
    ParkingSpot findParkingSpot(Vehicle* vehicle) override {
        // Implement best-fit parking spot search logic
    }
};

class NearestFitParkingStrategy : public ParkingStrategy {
    public:
    ParkingSpot findParkingSpot(Vehicle* vehicle) override {
        // Implement nearest-fit parking spot search logic
    }
};


class FirstFitParkingStrategy : public ParkingStrategy {
    public:
    ParkingSpot findParkingSpot(Vehicle* vehicle) override {
        // Implement first-fit parking spot search logic
    }
};
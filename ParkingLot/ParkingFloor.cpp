#include "ParkingSpot.cpp"
#include <vector>
#include "Vehicle.cpp"

class ParkingFloor{
    int floorNumber;
    vector<ParkingSpot> spots;

public:
    ParkingFloor(int number, int numSpots) : floorNumber(number) {}
    void addSpot(const ParkingSpot& spot) {
        spots.push_back(spot);
    }


    ParkingSpot findAvailableSpot(Vehicle* vehicle) {
        for (auto& spot : spots) {
            if (spot.isAvailable() && spot.canFit(vehicle)) {
                return spot;
            }
        }
        throw std::runtime_error("No available spot for the vehicle.");
    }

    void displayAvailableSpots() const {
        for (const auto& spot : spots) {
            if (spot.isAvailable()) {
                std::cout << "Spot " << spot.getId() << " is available." << std::endl;
            }
        }
    }

    vector<ParkingSpot> getAllSpots() const {
        return spots;
    }
};
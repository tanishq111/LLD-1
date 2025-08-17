#include "Vehicle.cpp"
#include <string>
class ParkingSpot {
    VehicleSize spotSize;
    string spotId;
    bool isOccupied = false;
    Vehicle* parkedVehicle = nullptr;
    public:
    ParkingSpot(VehicleSize size, const string& id) : spotSize(size), spotId(id) {}

    bool canFit(Vehicle* vehicle) const {
        if (isOccupied) return false;
        return spotSize >= vehicle->getSize();
    }

    bool parkVehicle(Vehicle* vehicle) {
        if (!canFit(vehicle)) return false;
        isOccupied = true;
        parkedVehicle = vehicle;
        return true;
    }

    void UnparkVehicle() {
        isOccupied = false;
        parkedVehicle = nullptr;
    }

    bool isAvailable() const {
        return !isOccupied;
    }

    string getId() const {
        return spotId;
    }

    VehicleSize getSize() const {
        return spotSize;
    }
};

#include "ParkingTicket.cpp"
class FeeStrategy {
public:
    virtual double calculateFee(ParkingTicket* ticket, long exitTime) = 0;
};


class VehicleFeeStrategy : public FeeStrategy {
public:
    double calculateFee(ParkingTicket* ticket, long exitTime) override {
        // Implement fee calculation logic for vehicles
        return 0.0;
    }
};


class FlatFeeStrategy : public FeeStrategy {
public:
    double calculateFee(ParkingTicket* ticket, long exitTime) override {
        // Implement flat fee calculation logic
        return 10.0;  // Flat fee of $10
    }
};
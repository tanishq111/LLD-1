#include "ParkingFloor.cpp"
#include <vector>
#include "ParkingTicket.cpp"
#include "FeeStrategy.cpp"
#include "ParkingStrategy.cpp"

class ParkingLotSystem {
    vector<ParkingFloor> floors;
    vector<ParkingTicket> activeTickets;
    FeeStrategy fee;
    ParkingStrategy parking;

    public:
    void addFloor(const ParkingFloor& floor) {
        floors.push_back(floor);
    }
    void setFeeStrategy(const FeeStrategy& feeStrategy) {
        fee = feeStrategy;
    }


    ParkingTicket parkVehicle(Vehicle* vehicle, long entryTime){
            ParkingSpot spot = parking.findParkingSpot(vehicle);
            if(spot){
                auto ticket = new ParkingTicket(vehicle,spot, entryTime, fee);
                activeTickets.push_back(ticket);
                spot.setOccupied(true);
                spot.setVehicle(vehicle);
                return ticket;
            }
    }


    double unParkVehicle(ParkingTicket* ticket, long exitTime){
        ParkingSpot spot = ticket->getSpot();
        spot.setOccupied(false);
        spot.setVehicle(nullptr);
        activeTickets.remove(ticket);
        double fee = FeeStrategy::calculateFee(ticket, exitTime);
        return fee;
    }
};
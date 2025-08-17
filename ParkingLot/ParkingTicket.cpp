#include <string>
#include <ctime>
#include "Vehicle.cpp"
#include "ParkingSpot.cpp"
using namespace std;

class ParkingTicket{
    string ticketId;
    Vehicle* vehicle;
    ParkingSpot* spot;
    long entry;
    long exit;

public:
    ParkingTicket(const string& id, Vehicle* v, ParkingSpot* s)
        :  vehicle(v), spot(s), entry(time(nullptr)), exit(0) {}

    string getId() const { return ticketId; }
    Vehicle* getVehicle() const { return vehicle; }
    ParkingSpot* getSpot() const { return spot; }
    long getEntryTime() const { return entry; }
    long getExitTime() const { return exit; }
};

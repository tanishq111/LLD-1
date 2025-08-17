int main(){
    ParkingLotSystem parkingLot;

    // Add floors
    ParkingFloor floor1(1);
    ParkingFloor floor2(2);
    parkingLot.addFloor(floor1);
    parkingLot.addFloor(floor2);

    // Set fee strategy
    parkingLot.setFeeStrategy(new HourlyFeeStrategy());

    // Set parking strategy
    parkingLot.setParkingStrategy(new BestFitParkingStrategy());

    // Park a vehicle
    Vehicle* vehicle = new Car("ABC123");
    ParkingTicket* ticket = parkingLot.parkVehicle(vehicle, getCurrentTime());

    // Unpark the vehicle
    double fee = parkingLot.unParkVehicle(ticket, getCurrentTime());
    cout << "Parking fee: " << fee << endl;

    return 0;
}
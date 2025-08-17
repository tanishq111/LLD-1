#include <iostream>
#include <string>

enum class VehicleSize {
    COMPACT,
    STANDARD,
    LARGE
};

class Vehicle{
    VehicleSize size;
    string licensePlate;
public:
    Vehicle(VehicleSize s, const string& plate) : size(s), licensePlate(plate) {}
    VehicleSize getSize() const { return size; }
    string getLicensePlate() const { return licensePlate; }
};


class Car : public Vehicle {
public:
    Car(const string& plate) : Vehicle(VehicleSize::STANDARD, plate) {}
};

class Bike : public Vehicle {
public:
    Bike(const string& plate) : Vehicle(VehicleSize::COMPACT, plate) {}
};

class Truck : public Vehicle {
public:
    Truck(const string& plate) : Vehicle(VehicleSize::LARGE, plate) {}
};
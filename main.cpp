#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Forward Declaration for later use
class Customer;

class Vehicle {
protected:
    string vehicleID;
    string brand;
    //string type; we dont need to write type now as type was bike or car so for that we made diff child classes
    float rentPerDay;
    bool isAvailable;

public:
    // Default constructor
    Vehicle() : vehicleID(0), brand(""), rentPerDay(0.0), isAvailable(true) {}

    // Parameterized constructor
    Vehicle(string id, string b, float rent, bool avail = true)
        : vehicleID(id), brand(b), rentPerDay(rent), isAvailable(avail) {}

    // Getters
    string getID() const { return vehicleID; }
    string getBrand() const { return brand; }
    bool getAvailability() const { return isAvailable; }

    // Setters
    void setAvailability(bool avail) { isAvailable = avail; }
    
    // Polymorphism: We want displayDetails() and calculateRent() to behave differently in child classes.
    // Virtual functions: Required so that Vehicle* can point to a Car or Bike and call the correct overridden method.
    // Display function
    virtual void displayDetails() const {
        cout << "\n--- Vehicle Info ---\n";
        cout << "ID: " << vehicleID << "\nBrand: " << brand
             << "\nRent/Day: ₹" << rentPerDay
             << "\nAvailable: " << (isAvailable ? "Yes" : "No") << endl;
    }
    // Rent calculation function
    virtual int calculateRent(int days) const {
        return rentPerDay * days;
    }
    // Virtual destructor
    virtual ~Vehicle() {}
};

// Car class inherited from Vehicle
class Car : public Vehicle {
    int numSeats;

public:  
    Car(string id, string b, float rent, int seats) : Vehicle(id, b, rent), numSeats(seats) {}
    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Seats: " << numSeats << endl;
    }
    int calculateRent(int days) const override {
        return rentPerDay * days + 100;  // maybe a flat booking fee
    }
};

// Bike class inherited from Vehicle
class Bike : public Vehicle {
    bool hasCarrier;

public:
    Bike(string id, string b, float rent, bool carrier) : Vehicle(id, b, rent), hasCarrier(carrier) {}
    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "Carrier: " << (hasCarrier ? "Yes" : "No") << endl;
    }
    int calculateRent(int days) const override {
        return rentPerDay * days;
    }
};

// Main for testing
int main() {
    vector<Vehicle*> vehicles;

    vehicles.push_back(new Car("C101", "Honda City", 1200, 5));//new Car(...) and new Bike(...) dynamically allocate objects and return a pointer.Since Car and Bike are derived from Vehicle, the vector<Vehicle*> can hold them.This is an example of upcasting — storing derived class objects in base class pointers.
    vehicles.push_back(new Bike("B201", "Yamaha", 500, true));

    //This loop prints details of each vehicle and calculates rent for 3 days.
    for (auto v : vehicles) {
        v->displayDetails();//Even though v is of type Vehicle*, the correct overridden function in Car or Bike is called at runtime — this is runtime polymorphism in action.
        cout << "Rent for 3 days: " << v->calculateRent(3) << "\n\n";
    }

    // Clean up
    for (auto v : vehicles)
        delete v;

    return 0;

  
// Inheritance - Car and Bike inherit from Vehicle
// Polymorphism	- Base class pointer (Vehicle*) calls derived class methods (Car, Bike)
// Virtual Functions - displayDetails() and calculateRent() behave polymorphically
// Dynamic Allocation - Objects are created using new
// Vectors & Pointers - vector<Vehicle*> holds heterogeneous vehicle objects
// Memory Management - delete used to prevent memory leaks
}

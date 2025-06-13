#include <iostream>
#include <string>
using namespace std;

// Forward Declaration for later use
class Customer;

class Vehicle {
protected:
    int vehicleID;
    string brand;
    string type;
    float rentPerDay;
    bool isAvailable;

public:
    // Default constructor
    Vehicle() : vehicleID(0), brand(""), type(""), rentPerDay(0.0), isAvailable(true) {}

    // Parameterized constructor
    Vehicle(int id, string b, string t, float rent, bool avail = true)
        : vehicleID(id), brand(b), type(t), rentPerDay(rent), isAvailable(avail) {}

    // Getters
    int getID() const { return vehicleID; }
    string getBrand() const { return brand; }
    string getType() const { return type; }
    float getRentPerDay() const { return rentPerDay; }
    bool getAvailability() const { return isAvailable; }

    // Setters
    void setAvailability(bool avail) { isAvailable = avail; }

    // Display function
    virtual void display() const {
        cout << "\n--- Vehicle Info ---\n";
        cout << "ID: " << vehicleID << "\nBrand: " << brand
             << "\nType: " << type << "\nRent/Day: ₹" << rentPerDay
             << "\nAvailable: " << (isAvailable ? "Yes" : "No") << endl;
    }

    // Virtual destructor
    virtual ~Vehicle() {}
};

// Main for testing
int main() {
    Vehicle v1(101, "Honda", "Bike", 250);
    v1.display();

    return 0;
}

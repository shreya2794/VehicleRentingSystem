#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime> // for time functions
#include <cstring> // for strlen
#include <algorithm>  //  for all_of
#include <cctype>     //  for isdigit

using namespace std;

// Forward Declaration for later use
//if sometimes we call a function before defining it like I wrote function resetAllVehicles later and called it before in the admin menu so it will show an error like function not defined in scope so we have to ways like first is to write that function earlier or before admin menu or to forward declare that 
//This tells the compiler the function will be defined later.
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
    Vehicle() : vehicleID(""), brand(""), rentPerDay(0.0), isAvailable(true) {}

    // Parameterized constructor
    Vehicle(string id, string b, float rent, bool avail = true)
        : vehicleID(id), brand(b), rentPerDay(rent), isAvailable(avail) {}

    // Getters
    string getID() const { return vehicleID; }
    string getBrand() const { return brand; }
    bool getAvailability() const { return isAvailable; }
    float getRentPerDay() const { return rentPerDay; }//new day 3 In Vehicle class (for rent getter)


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

    //new day 3 //getter
    int getSeats() const { return numSeats; }

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

    //day 3
    bool hasCarrierFn() const { return hasCarrier; }

};

// Customer class (day 5)
class Customer{
    string name;
    string phoneNumber; //If you store this in an int or long, the leading 0 is lost. // Phone Numbers Are Not Used for Calculations9They're identifiers, not numeric values.) //Country codes, dashes, brackets, or spaces: //An int can’t hold such large numbers:                     
    string rentedVehicleID;
    int rentDays;

public:
    Customer(string n, string phone = "") : name(n), phoneNumber(phone), rentedVehicleID(""), rentDays(0) {
        loadRental();  // Try loading any existing rental
    }

    string getName() const { return name; }
    string getPhone() const { return phoneNumber; }
    string getRentedVehicleID() const { return rentedVehicleID; }
    int getRentDays() const { return rentDays; }

    bool hasRented() const {
        return !rentedVehicleID.empty();
    }

    void rentVehicle(const string& vid, int days) {
        rentedVehicleID = vid;
        rentDays = days;
        saveRental();  // Save to file
    }

    void returnVehicle() {
        rentedVehicleID = "";
        rentDays = 0;
        removeRental();  // Remove from file
    }

     void saveRental() {
        ofstream out("current_rentals.txt", ios::app);
        out << name << "," << phoneNumber << "," << rentedVehicleID << "," << rentDays << "\n";
        out.close();
    }

    void loadRental() {
        ifstream in("current_rentals.txt");
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string n, phone, vid, daysStr;
            getline(ss, n, ',');
            getline(ss, phone, ',');
            getline(ss, vid, ',');
            getline(ss, daysStr, ',');

            if (n == name && phone == phoneNumber) {
                rentedVehicleID = vid;
                rentDays = stoi(daysStr);
                break;
            }
        }
        in.close();
    }

    void removeRental() {
        ifstream in("current_rentals.txt");
        vector<string> lines;
        string line;
        while (getline(in, line)) {
            if (line.find(name + "," + phoneNumber + "," + rentedVehicleID) != 0) {
                lines.push_back(line);
            }
        }
        in.close();

        ofstream out("current_rentals.txt");
        for (const auto& l : lines)
            out << l << "\n";
        out.close();
    }
};

// FileManager Class (day 4)
class FileManager {
public:
    static void saveVehiclesToFile(const vector<Vehicle*>& vehicles, const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error opening file for writing.\n";
            return;
        }

        for (const auto& v : vehicles) {
            if (Car* car = dynamic_cast<Car*>(v)) {
                outFile << "Car," << car->getID() << "," << car->getBrand() << ","
                        << car->getRentPerDay() << "," << car->getAvailability() << ","
                        << car->getSeats() << "\n";
            } else if (Bike* bike = dynamic_cast<Bike*>(v)) {
                outFile << "Bike," << bike->getID() << "," << bike->getBrand() << ","
                        << bike->getRentPerDay() << "," << bike->getAvailability() << ","
                        << bike->hasCarrierFn() << "\n";
            }
        }

        outFile.close();
    }

    static void loadVehiclesFromFile(vector<Vehicle*>& vehicles, const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "No vehicle file found. Starting with empty list.\n";
            return;
        }

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string type, id, brand;
            float rent;
            bool avail;

            getline(ss, type, ',');
            getline(ss, id, ',');
            getline(ss, brand, ',');
            ss >> rent;
            ss.ignore();
            ss >> avail;
            ss.ignore();

            if (type == "Car") {
                int seats;
                ss >> seats;
                auto* car = new Car(id, brand, rent, seats);
                car->setAvailability(avail);
                vehicles.push_back(car);
            } else if (type == "Bike") {
                bool carrier;
                ss >> carrier;
                auto* bike = new Bike(id, brand, rent, carrier);
                bike->setAvailability(avail);
                vehicles.push_back(bike);
            }
        }

        inFile.close();
    }
};

//DAY 6
// Rental History
void logRentalHistory(const string& customerName, const string& phone, const string& vehicleID, int days, const string& action, int totalBill = 0, int lateFee = 0, int earlyPenalty = 0) {
    ofstream logFile("rental_history.txt", ios::app); // append mode
    if (!logFile) {
        cerr << "Error opening rental history file.\n";
        return;
    }

    string dateStr = "";
    if (action != "Returned") {
        // Only log date for Rented actions
        time_t now = time(0);
        tm* localtm = localtime(&now);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtm); // YYYY-MM-DD
        dateStr = buffer;
    }

    logFile << customerName << "," << phone << "," << vehicleID << ",";
    
    if (!dateStr.empty()) logFile << dateStr;
    logFile << "," << days << "," << action;

    if (action == "Returned") {
        logFile << ", Total: ₹" << totalBill;
        if (lateFee > 0)
            logFile << ", Late Fee: ₹" << lateFee;
        if (earlyPenalty > 0)
            logFile << ", Early Penalty: ₹" << earlyPenalty;
        logFile << ", Note: 20% extra/day for late, half-day charge for early return";
    }

    logFile << "\n";
    logFile.close();
}


//DAY 7
// Add a function to load existing rental info:
bool isNumber(const string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

bool loadCurrentRental(Customer& cust) {
    ifstream file("current_rentals.txt");
    if (!file) return false;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone, vid, daysStr;

        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, vid, ',');
        getline(ss, daysStr);

        if (name == cust.getName() && phone == cust.getPhone()) {
            if (!isNumber(daysStr)) {
                cout << "⚠️ Invalid rental day data for customer: " << name << "\n";
                return false;
            }

            int days = stoi(daysStr);
            cust.rentVehicle(vid, days);
            return true;
        }
    }
    return false;
}


//day6
// automatically update vehicle availability at program startup by reading from current_rentals.txt.
void updateVehicleAvailabilityFromCurrentRentals(vector<Vehicle*>& vehicles) {
    ifstream in("current_rentals.txt");
    if (!in.is_open()) return;

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string name, phone, vehicleID, daysStr;

        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, vehicleID, ',');
        getline(ss, daysStr, ',');

        // Mark this vehicle as unavailable
        for (auto& v : vehicles) {
            if (v->getID() == vehicleID) {
                v->setAvailability(false);
                break;
            }
        }
    }

    in.close();
}

// automatically remove an entry from current_rentals.txt when a return happens, so everything stays clean
void removeFromCurrentRentals(const string& name, const string& phone) {
    ifstream inFile("current_rentals.txt");
    ofstream tempFile("temp.txt");

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string fileName, filePhone;
        getline(ss, fileName, ',');
        getline(ss, filePhone, ',');

        // If not the returning customer, keep the line
        if (fileName != name || filePhone != phone) {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // Replace original file with updated temp file
    remove("current_rentals.txt");
    rename("temp.txt", "current_rentals.txt");
}

//DAY 4 

// Check if ID is unique
bool isUniqueID(const vector<Vehicle*>& vehicles, const string& id) {
    for (const auto& v : vehicles) {
        if (v->getID() == id)
            return false;
    }
    return true;
}

//day 7

string formatBill(const string& customerName, const string& phone, const string& vehicleID,
                  int expectedDays, int actualDays, float rentPerDay,
                  int baseRent, int lateFee, int earlyPenalty, int totalBill) {
    
    stringstream ss;
    ss << "\n--- Final Bill ---\n";
    ss << "Customer: " << customerName << " | Phone: " << phone << "\n";
    ss << "Vehicle ID: " << vehicleID << "\n";
    ss << "Days Kept: " << actualDays << " (Expected: " << expectedDays << ")\n";
    ss << "Rent per Day: ₹" << rentPerDay << "\n";
    ss << "Base Rent: ₹" << baseRent << "\n";
    
    if (lateFee > 0)
        ss << "Late Fee (20% per late day): ₹" << lateFee << "\n";
    if (earlyPenalty > 0)
        ss << "Early Return Penalty (Half Day Rent): ₹" << earlyPenalty << "\n";

    ss << "Total Bill: ₹" << totalBill << "\n";
    ss << "\nNote:\n• Late returns incur 20% extra rent/day.\n• Early returns charge half-day rent as penalty.\n";

    return ss.str();
}

void logBill(const string& formattedBill) {
    ofstream billFile("bill_log.txt", ios::app);
    if (!billFile) {
        cerr << "Error opening bill_log.txt\n";
        return;
    }
    billFile << formattedBill << "\n------------------------------------\n";
    billFile.close();
}



// generate bill for case 3 in customer menu
void generateFinalBill(Customer& cust, Vehicle* v, int actualDays) {
    int expectedDays = cust.getRentDays();
    int lateDays = max(0, actualDays - expectedDays);
    float rentPerDay = v->getRentPerDay();
    int baseRent = v->calculateRent(actualDays);
    int lateFee = lateDays > 0 ? static_cast<int>(lateDays * rentPerDay * 0.2) : 0;
    int earlyPenalty = (actualDays < expectedDays) ? static_cast<int>(rentPerDay / 2) : 0;
    int totalBill = baseRent + lateFee + earlyPenalty;

    // ✅ Use the shared formatting function
    string billText = formatBill(cust.getName(), cust.getPhone(), v->getID(),
                                 expectedDays, actualDays, rentPerDay,
                                 baseRent, lateFee, earlyPenalty, totalBill);

    // Display to user
    cout << "\033[1;33m" << billText << "\033[0m\n";

    // Log summary
    logRentalHistory(cust.getName(), cust.getPhone(), v->getID(), actualDays, "Returned", totalBill);

    // ✅ Log full bill
    logBill(billText);

    removeFromCurrentRentals(cust.getName(), cust.getPhone());
    cust.returnVehicle();
}




// ADMIN MENU
void adminMenu(vector<Vehicle*>& vehicles) {
    
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Vehicle\n2. View All Vehicles\n3. View Rental History\n0. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int typeChoice;
                cout << "Add:\n1. Car\n2. Bike\nEnter choice: ";
                cin >> typeChoice;

                string id, brand;
                float rent;

                while (true) {
                    cout << "Enter ID (start with 'C' for Car or 'B' for Bike): ";
                    cin >> id;

                    // Validate prefix
                    if ((typeChoice == 1 && id[0] != 'C') || (typeChoice == 2 && id[0] != 'B')) {
                        cout << " Invalid ID prefix. Car ID must start with 'C', Bike with 'B'. Try again.\n";
                        continue;
                    }

                    // Check for uniqueness
                    if (!isUniqueID(vehicles, id)) {
                        cout << " Vehicle ID already exists. Try again.\n";
                        continue;
                    }

                    break;  // Valid ID
                }

                cout << "Enter Brand: ";
                cin.ignore(); // Clears leftover newline character from previous input
                getline(cin, brand); // Reads the full brand name including spaces
                cout << "Enter Rent per Day: ";
                cin >> rent;

                if (typeChoice == 1) {
                    int seats;
                    cout << "Enter Number of Seats: ";
                    cin >> seats;
                    vehicles.push_back(new Car(id, brand, rent, seats));
                } else if (typeChoice == 2) {
                    bool carrier;
                    cout << "Has Carrier (1 for Yes, 0 for No): ";
                    cin >> carrier;
                    vehicles.push_back(new Bike(id, brand, rent, carrier));
                }

                FileManager::saveVehiclesToFile(vehicles, "vehicles.txt");
                cout << " Vehicle added successfully.\n";
                break;
            }

            case 2: {
                cout << "\n Cars:\n";
                for (const auto& v : vehicles) {
                    if (Car* car = dynamic_cast<Car*>(v)) {
                        cout << car->getID() << " | " << car->getBrand()
                             << " | ₹" << car->getRentPerDay()
                             << " | " << (car->getAvailability() ? "Available" : "Rented")
                             << " | Seats: " << car->getSeats() << endl;
                    }
                }

                cout << "\n Bikes:\n";
                for (const auto& v : vehicles) {
                    if (Bike* bike = dynamic_cast<Bike*>(v)) {
                        cout << bike->getID() << " | " << bike->getBrand()
                             << " | ₹" << bike->getRentPerDay()
                             << " | " << (bike->getAvailability() ? "Available" : "Rented")
                             << " | Carrier: " << (bike->hasCarrierFn() ? "Yes" : "No") << endl;
                    }
                }
                break;
            }

            case 3: {
                ifstream logFile("rental_history.txt");
                if (!logFile) {
                    cout << "No rental history found.\n";
                    break;
                }

                string line;
                cout << "\n--- Rental History ---\n";
                while (getline(logFile, line)) {
                   stringstream ss(line);
                   string name, phone, id, datetime, days, action;

                   getline(ss, name, ',');
                   getline(ss, phone, ',');
                   getline(ss, id, ',');
                   getline(ss, datetime, ',');
                   getline(ss, days, ',');
                   getline(ss, action, ',');

                   cout << "Customer: " << name << ", Phone: " << phone <<", Vehicle ID: " << id
                        << ", Date: " << datetime << ", Days: " << days
                        << ", Action: " << action << "\n";
                }

                logFile.close();
                break;
            } 
            case 0:
                cout << "Exiting Admin Menu.\n";
                break;
                
            default:
                cout << " Invalid choice. Please try again.\n";
                cin.clear(); // clear error flag // clears the error state if a non-numeric input was entered.
                cin.ignore(10000, '\n'); // discard invalid input // s5kips leftover input, preventing infinite loops.
        }

    } while (choice != 0);
}

//DAY 5 CUSTOMER MENU
// Customer Menu
void customerMenu(vector<Vehicle*>& vehicles) {
    string customerName, phone;
    cin.ignore(); 
    cout << "\nEnter your name: ";
    getline(cin, customerName);
    cout << "Enter your phone number: ";
    getline(cin, phone);
    
    Customer cust(customerName, phone); //Pass phone and name to constructor
    loadCurrentRental(cust);  // ✅ Loads from file if exists

    int choice;
    do {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. View Available Vehicles\n2. Rent Vehicle\n3. Return Vehicle\n0. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n======================== Cars ========================\n";
                for (const auto& v : vehicles) {
                    if (Car* car = dynamic_cast<Car*>(v)) {
                        cout << car->getID() << " | " << car->getBrand()
                             << " | ₹" << car->getRentPerDay()
                             << " | Seats: " << car->getSeats() 
                             << " | " << (car->getAvailability() ? "✅ Available" : "❌ Rented")<< endl;
                    }
                }
                cout << "\n======================== Bikes =======================\n";
                for (const auto& v : vehicles) {
                    if (Bike* bike = dynamic_cast<Bike*>(v)) {
                        cout << bike->getID() << " | " << bike->getBrand()
                             << " | ₹" << bike->getRentPerDay()
                             << " | Carrier: " << (bike->hasCarrierFn() ? "Yes" : "No") 
                             << " | " << (bike->getAvailability() ? "✅ Available" : "❌ Rented")<< endl;
                             
                    }
                }
                break;
            }

            case 2: {
                if (cust.hasRented()) {
                    cout << "⚠️ You already rented vehicle ID: " << cust.getRentedVehicleID() << endl;
                    cout << "Please return the current vehicle before renting another.\n";
                    break;  // Make sure this exists to prevent infinite input
                }


                string rentID;
                int days;
                cout << "Enter Vehicle ID to Rent: ";
                cin >> rentID;

                bool found = false;
                for (auto& v : vehicles) {
                    if (v->getID() == rentID && v->getAvailability()) {
                        cout << "Enter number of days: ";
                        cin >> days;
                        int totalRent = v->calculateRent(days);
                        cout << " Vehicle rented! Total Rent: ₹" << totalRent << endl;
                        v->setAvailability(false);
                        cust.rentVehicle(rentID, days);
                        FileManager::saveVehiclesToFile(vehicles, "vehicles.txt");
                        // Log the rental
                        logRentalHistory(cust.getName(), cust.getPhone(), rentID, days, "Rented");
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Vehicle not found or unavailable.\n";
                }

                break;
            }
            
             case 3: {
                if (!cust.hasRented()) {
                cout << "No rented vehicle to return.\n";
                break;
                }

                string rentedID = cust.getRentedVehicleID();
                int actualDays;
                cout << "Enter number of days you kept the vehicle: ";
                cin >> actualDays;

                for (auto& v : vehicles) {
                if (v->getID() == rentedID) {
                v->setAvailability(true);  // Make available first
                generateFinalBill(cust, v, actualDays); // 🟡 Use the function here
            
                // Save updated vehicle state
                FileManager::saveVehiclesToFile(vehicles, "vehicles.txt");
                break;
                }
                }
                break;
                }
  

            case 0:
                cout << "Exiting Customer Menu.\n";
                break;

            default:
                cout << " Invalid choice. Please try again.\n";
                cin.clear(); // clear error flag
                cin.ignore(10000, '\n'); // discard invalid input
        }
    } while (choice != 0);
}


// Main for testing
int main() {
    vector<Vehicle*> vehicles;

    // Load vehicles from file
    FileManager::loadVehiclesFromFile(vehicles, "vehicles.txt");

    // 🔄 Mark rented vehicles as unavailable based on current rentals
    updateVehicleAvailabilityFromCurrentRentals(vehicles);

    //DAY 5
    int userType;
    while (true) { //DAY 6 To ensure that invalid input doesn't exit the program, but instead returns to the same menu
    cout << "Login as:\n1. Admin\n2. Customer\n0. Exit\nEnter choice: ";
    cin >> userType;

    switch (userType) {
        case 1:
            adminMenu(vehicles);
            break; 
        case 2:
            customerMenu(vehicles);
            break; 
        case 0:
            cout << "Exiting program.\n";
            for (auto v : vehicles)
            delete v;
            return 0;
        default:
            cout << " Invalid choice. Please enter 1 or 2.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            break;
    }
}

    //DAY 4
    //adminMenu(vehicles);

    //DAY 3
    // // If no vehicles loaded, add sample
    // if(vehicles.empty()){
    // vehicles.push_back(new Car("C101", "Honda City", 1200, 5));//new Car(...) and new Bike(...) dynamically allocate objects and return a pointer.Since Car and Bike are derived from Vehicle, the vector<Vehicle*> can hold them.This is an example of upcasting — storing derived class objects in base class pointers.
    // vehicles.push_back(new Bike("B201", "Yamaha", 500, true));
    // }

    // //DAY 2
    // //This loop prints details of each vehicle and calculates rent for 3 days.
    // for (auto v : vehicles) {
    //     v->displayDetails();//Even though v is of type Vehicle*, the correct overridden function in Car or Bike is called at runtime — this is runtime polymorphism in action.
    //     cout << "Rent for 3 days: " << v->calculateRent(3) << "\n\n";
    // }

    // Save to file
    FileManager::saveVehiclesToFile(vehicles, "vehicles.txt");

    //Day 6 cleared and added in case 0
    // // Clean up
    // for (auto v : vehicles)
    //     delete v;

    return 0;
}

// Inheritance - Car and Bike inherit from Vehicle
// Polymorphism	- Base class pointer (Vehicle*) calls derived class methods (Car, Bike)
// Virtual Functions - displayDetails() and calculateRent() behave polymorphically
// Dynamic Allocation - Objects are created using new
// Vectors & Pointers - vector<Vehicle*> holds heterogeneous vehicle objects
// Memory Management - delete used to prevent memory leaks

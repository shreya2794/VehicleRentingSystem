![GitHub Repo stars](https://img.shields.io/github/stars/shreya2794/VehicleRentingSystem?style=social)
![GitHub forks](https://img.shields.io/github/forks/shreya2794/VehicleRentingSystem?style=social)
![GitHub last commit](https://img.shields.io/github/last-commit/shreya2794/VehicleRentingSystem)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)

## Vehicle Rental System (C++ | OOP)

This is a console-based C++ project that simulates a simple vehicle rental system using Object-Oriented Programming concepts. The system allows managing different types of vehicles with essential details like brand, model, registration number, rent, and availability.

### Day 1: Project Setup & Base Vehicle Class

#### ✅ What’s Implemented:
- Project initialized with Git
- Base class `Vehicle` created with:
  - Attributes: brand, model, registration number, rent per day, availability
  - Constructor (parameterized)
  - Display method
  - Getters and setters
- Code tested in Visual Studio Code
- Files added:
  - `main.cpp`
  - `.vscode/` configuration files

#### OOP Concepts Used:
- **Encapsulation** (private data members with public methods)
- **Constructor Overloading**
- **Getters and Setters**

### Day 2 : Progress: Inheritance, Polymorphism & Virtual Functions, MIT License and badge

#### ✅ Features Added
- Created base class `Vehicle` with:
  - Protected attributes: `vehicleID`, `brand`, `rentPerDay`, `isAvailable`
  - Virtual functions: `displayDetails()` and `calculateRent(int days)`
  - Constructor overloading and virtual destructor
- Implemented two derived classes:
  - `Car` (with additional attribute: `numSeats`)
  - `Bike` (with additional attribute: `hasCarrier`)
- Used **polymorphism** to dynamically call overridden methods through `Vehicle*` pointers
- Managed objects using `vector<Vehicle*>` and cleaned memory with `delete`
- Files Modified
 - `main.cpp`: All class definitions and logic implemented here
 - `.vscode/`: VS Code configuration files (auto-generated)

#### Concepts Used
- **Inheritance**: `Car` and `Bike` classes inherit from `Vehicle`
- **Polymorphism**: Runtime method dispatch using virtual functions
- **Dynamic Memory Allocation**: Created objects using `new`
- **Virtual Destructor**: Ensures proper cleanup of derived objects
- **Encapsulation**: Controlled access to class members using getters/setters
- **Initialization List**: Used in constructors for clean attribute initialization
- **Forward Declaration**: Introduced for planning future expansion (e.g., `Customer` class)

### Day 3: File Handling & Data Persistence

#### ✅ What Was Added
- **FileManager class** to manage all file-related operations (save/load).
- Vehicle data is now stored in `vehicles.txt` to retain entries across runs.
- Used `dynamic_cast` to detect the correct derived type (Car/Bike) when saving/loading.
- Files added
 - `vehicles.txt`

#### OOP Concepts Used
- **Inheritance**: `Car` and `Bike` inherit from `Vehicle`
- **Polymorphism**: `displayDetails()` and `calculateRent()` overridden
- **Encapsulation**: Getter/setter methods manage access
- **Separation of Concerns**: FileManager handles file logic separately
- **Dynamic Casting**: Used for identifying object type when saving to file
- **Abstraction**: File I/O logic hidden inside `FileManager`

### Day 4: Admin Module – Add/View Vehicles

#### ✅ Features Implemented:
1. **Admin Menu (Switch-Case Based):**
   - Option to **Add** or **View** all vehicles.
   - Easy-to-navigate menu-driven interface.
2. **Add Vehicle:**
   - User must input a unique ID starting with `C` (for Car) or `B` (for Bike).
   - Rejects duplicate or invalid IDs.
   - Stores vehicle brand, rent per day, number of seats (Car), or carrier info (Bike).
3. **View Vehicles:**
   - Displays **all cars** first followed by **all bikes**.
   - Each vehicle shown in a **single line** with relevant information.
4. **FileManager Integration:**
   - `vehicles.txt` used to store and retrieve vehicle records.
   - Fully supports persistent data storage using `saveVehiclesToFile()` and `loadVehiclesFromFile()`.
5. **Files Modified:**
  - `main.cpp` (Admin module, vehicle input/output)
  - `FileManager` class (load/save enhancements)

#### OOP Concepts Applied:
- **Abstraction:** Admin functionality is abstracted inside `adminMenu()` function.
- **Inheritance:** `Car` and `Bike` inherit from base class `Vehicle`.
- **Polymorphism:** Display and rent calculation methods are overridden in child classes.
- **Separation of Concerns:** File handling separated via the `FileManager` class.

### Day 5: Customer Module: View/Search/Rent/Return Vehicles

#### ✅ Features Implemented:
- Created `Customer` class to manage individual customer actions
- Customer functionality added:
  - View all vehicles with **availability status**
  - Rent a vehicle by ID
  - Return a rented vehicle
- Vehicle availability updates saved to `vehicles.txt`
- Files Modified:
  - `main.cpp` (all logic)
  - `vehicles.txt` (auto-updated for availability) 

#### OOP Concepts Applied:
- Inheritance (`Car` and `Bike` inherit from `Vehicle`)
- Polymorphism (`displayDetails()` and `calculateRent()` are overridden)
- Encapsulation (used in `Customer` and `Vehicle` classes)
- Dynamic memory allocation (`new` and `delete`)

### Day 6 Rental History

#### ✅ Features Implemented:

1. Customer Enhancements:
- Added phone number field to `Customer` class.
- Captured both **name** and **phone number** when a customer logs in.
- Used `getline()` for proper input of full names and phone numbers.
2. Rental Tracking Improvements:
- Rental entries now include **customer name, phone number, vehicle ID, date, days, action**.
- On return, the system reads `current_rentals.txt` to check if the customer has a pending rental.
- Vehicle availability is updated based on file tracking.
3. Menu Flow Enhancements:
- Main login menu loops until valid input (Admin/Customer/Exit).
- After Admin or Customer menu exits, control returns to login menu.
- Handled invalid input using `cin.clear()` and `cin.ignore()`.
4. Files Modified:
- `main.cpp`
- `Customer.h / Customer.cpp`
- `FileManager.h / FileManager.cpp`
- `rental_history.txt` (updated format)
- `vehicles.txt` (availability flags updated)
- `current_rentals.txt`(added new)

#### OOP Concepts Applied:
- Class encapsulation (`Customer`, `Vehicle`, `Car`, `Bike`, `FileManager`)
- Polymorphism using `Vehicle*` with `dynamic_cast`
- Constructor overloading (`Customer` with name + phone)
- Separation of concerns in file handling and UI

#### 📝 License
This project is licensed under the [MIT License](LICENSE)


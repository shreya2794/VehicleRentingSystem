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

### OOP Concepts Used:
- **Encapsulation** (private data members with public methods)
- **Constructor Overloading**
- **Getters and Setters**

### Day 2 : MIT License and badge
###         Progress: Inheritance, Polymorphism & Virtual Functions

Today, we implemented **Object-Oriented Programming (OOP)** principles such as **Inheritance**, **Polymorphism**, and **Virtual Functions** to enhance the structure of our Vehicle Rental System.

### ✅ Features Added
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


### 🔁 Concepts Used
- **Inheritance**: `Car` and `Bike` classes inherit from `Vehicle`
- **Polymorphism**: Runtime method dispatch using virtual functions
- **Dynamic Memory Allocation**: Created objects using `new`
- **Virtual Destructor**: Ensures proper cleanup of derived objects
- **Encapsulation**: Controlled access to class members using getters/setters
- **Initialization List**: Used in constructors for clean attribute initialization
- **Forward Declaration**: Introduced for planning future expansion (e.g., `Customer` class)

#### 📝 License
This project is licensed under the [MIT License](LICENSE).


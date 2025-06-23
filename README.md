![GitHub Repo stars](https://img.shields.io/github/stars/shreya2794/VehicleRentingSystem?style=social)
![GitHub forks](https://img.shields.io/github/forks/shreya2794/VehicleRentingSystem?style=social)
![GitHub last commit](https://img.shields.io/github/last-commit/shreya2794/VehicleRentingSystem)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)

# 🚗 Vehicle Rental System (C++ Project)

A modular and object-oriented **Vehicle Rental System** built in C++. It allows customers to rent or return vehicles (cars/bikes), and admins to manage fleet inventory and view rental history. The system uses OOP concepts like inheritance, polymorphism, encapsulation, abstraction, and file handling for persistent data.

---

## 🧠 OOP Principles Used

- **Encapsulation** - All classes keep their data private and expose behavior through public methods (`getID()`, `rentVehicle()`, etc.) 
- **Abstraction** - Users interact with simple admin/customer menus without knowing internal logic; file I/O, billing, and rental logic are abstracted into dedicated classes 
- **Inheritance** - `Car` and `Bike` inherit from base class `Vehicle` 
- **Polymorphism** - Vehicle objects are accessed via base class pointers; virtual functions enable runtime behavior (`calculateRent()`, `displayDetails()`) 
- **Classes & Objects** - Real-world entities like Vehicle, Customer, Billing, and FileManager are modeled as classes 

---

## 🧩 Key Features

### 👤 Customer
- View available vehicles
- Rent vehicle (with unique ID and duration)
- Return rented vehicle and get a final bill
- Early return → half-day penalty
- Late return → extra full-day charges
- Rental automatically saved in `current_rentals.txt`
- System Reset Function → Admins can reset all system data (vehicles, rentals, bills, logs) to start fresh for testing or new deployment.

### 👩‍💼 Admin
- Add new cars or bikes with unique IDs
- View all registered vehicles with status
- View complete rental history from `rental_history.txt`

---

## 🔁 Project Flow Summary

1. Admin loads vehicle data
2. Vehicles are saved to and read from `vehicles.txt`
3. Customers rent/return vehicles → triggers:
   - Update availability
   - Log rental to `rental_history.txt`
   - Track active rentals in `current_rentals.txt`
   - Generate final bill in `bill_log.txt`

---

## 📁 File Handling

- `vehicles.txt` - Stores all registered vehicles with brand, rent/day, availability 
- `current_rentals.txt` - Tracks active customer rentals (used to auto-update availability) 
- `rental_history.txt` - Logs every rent/return with date, bill, fees, and penalties 
- `bill_log.txt` - Stores formatted customer bills (printout-style) 

---

## 📦 Class Structure Overview

- `Vehicle` (Base class)
  - `Car` (Seats info)
  - `Bike` (Carrier info)
- `Customer` (Tracks user info, rental status)
- `AdminInterface` / `CustomerInterface` (User menus)
- `RentalManager` (Handles rental file operations)
- `FileManager` (Load/save vehicles from/to file)
- `Billing` (Calculate final bill and log charges)

---

## 🧾 Billing Logic

- **Base Rent** = rent per day × total days used
- **Late Fee** = ₹rent/day × number of extra days
- **Early Return Penalty** = ₹rent/day ÷ 2 (half-day charge)
- 💾 All bills saved to `bill_log.txt`

---

## 🧪 Final Testing Checklist ✅

- [x] Admin can add cars and bikes with validation
- [x] Duplicated vehicle IDs are rejected
- [x] Customer can rent only if not already renting
- [x] Vehicle availability updates automatically
- [x] Final bill generated with accurate fees
- [x] Rental and return logs are persistent
- [x] Invalid inputs are safely handled
- [x] No memory leaks (manual `delete` on exit)

---

## 🛠 Technologies Used

- Language: **C++**
- Features: **Object-Oriented Programming, File I/O, CLI**
- IDE: VS Code / Code::Blocks / Terminal
- Platform: Windows / Linux

---

## ▶️ How to Run

1. Clone or download the project
2. Open terminal or command prompt
3. Compile using:
   ```bash
   g++ main.cpp -o rental
   ./rental
   ```
4. Follow on-screen menus for Admin or Customer

💡 **Note for Windows Users:**
If you're on Windows, after compiling with:

```bash
g++ main.cpp -o rental
```

Run the program using:
```bash
rental
```
or
```bash
rental.exe
```
(You do not need `./` like on Linux/macOS.)

---

## 👩‍💻 Developer

**Shreya Dandale**  
B.Tech in Electronics & Telecommunication, JSPM RSCOE Pune (2026)  
🎯 Passionate about C++, Web Development, and Software Engineering  
🌐 [GitHub](https://github.com/) • [LinkedIn](https://linkedin.com/) *(Add your links here)*

---

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

---



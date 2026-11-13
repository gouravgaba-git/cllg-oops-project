
#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Route Management
class Route {
private:
    int routeId;
    string source, destination;

public:
    Route(int id, string src, string dest) {
        routeId = id;
        source = src;
        destination = dest;
    }

    int getId() {
        return routeId;
    }

    string getSource() {
        return source;
    }

    string getDestination() {
        return destination;
    }

    void display() {
        cout << "Route ID: " << routeId
             << " | " << source
             << " to " << destination << endl;
    }
};

// Bus Management
class Bus {
private:
    int busId;
    int capacity;
    int availableSeats;
    int routeId;

public:
    Bus(int id, int cap, int rid) {
        busId = id;
        capacity = cap;
        availableSeats = cap;
        routeId = rid;
    }

    int getId() {
        return busId;
    }

    int getRouteId() {
        return routeId;
    }

    int getAvailableSeats() {
        return availableSeats;
    }

    bool bookSeat() {
        if (availableSeats > 0) {
            availableSeats--;
            return true;
        }
        return false;
    }

    void display() {
        cout << "Bus ID: " << busId
             << " | Capacity: " << capacity
             << " | Available Seats: " << availableSeats
             << " | Route ID: " << routeId << endl;
    }
};

// Passenger Management
class Passenger {
private:
    int passengerId;
    string name;
    string phone;

public:
    Passenger(int id, string n, string p) {
        passengerId = id;
        name = n;
        phone = p;
    }

    int getId() {
        return passengerId;
    }

    void display() {
        cout << "Passenger ID: " << passengerId
             << " | Name: " << name
             << " | Phone: " << phone << endl;
    }
};

// Ticket Booking
class Booking {
private:
    int ticketId;
    int passengerId;
    int busId;

public:
    Booking(int tid, int pid, int bid) {
        ticketId = tid;
        passengerId = pid;
        busId = bid;
    }

    void display() {
        cout << "Ticket ID: " << ticketId
             << " | Passenger ID: " << passengerId
             << " | Bus ID: " << busId << endl;
    }
};

// Global collections
vector<Route> routes;
vector<Bus> buses;
vector<Passenger> passengers;
vector<Booking> bookings;

int nextRouteId = 1;
int nextBusId = 101;
int nextPassengerId = 1;
int nextTicketId = 1001;

// Input helper functions
int readInt(string message) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readString(string message) {
    string value;
    cout << message;
    getline(cin, value);
    return value;
}

// Find records by ID
Route* findRoute(int id) {
    for (auto &r : routes) {
        if (r.getId() == id)
            return &r;
    }
    return nullptr;
}

Bus* findBus(int id) {
    for (auto &b : buses) {
        if (b.getId() == id)
            return &b;
    }
    return nullptr;
}

Passenger* findPassenger(int id) {
    for (auto &p : passengers) {
        if (p.getId() == id)
            return &p;
    }
    return nullptr;
}

// Add a route
void addRoute() {
    string source = readString("Enter source: ");
    string destination = readString("Enter destination: ");

    routes.emplace_back(nextRouteId++, source, destination);

    cout << "Route added successfully!\n";
}

// Display routes
void displayRoutes() {
    if (routes.empty()) {
        cout << "No routes available.\n";
        return;
    }

    cout << "\n--- ROUTE DETAILS ---\n";
    for (auto &r : routes)
        r.display();
}

// Add a bus
void addBus() {
    if (routes.empty()) {
        cout << "Add a route first!\n";
        return;
    }

    displayRoutes();

    int rid = readInt("Enter Route ID: ");
    if (findRoute(rid) == nullptr) {
        cout << "Invalid Route ID!\n";
        return;
    }

    int capacity = readInt("Enter bus capacity: ");

    if (capacity <= 0) {
        cout << "Capacity must be positive.\n";
        return;
    }

    buses.emplace_back(nextBusId++, capacity, rid);

    cout << "Bus added successfully!\n";
}

// Display buses
void displayBuses() {
    if (buses.empty()) {
        cout << "No buses available.\n";
        return;
    }

    cout << "\n--- BUS DETAILS ---\n";

    for (auto &b : buses) {
        b.display();

        Route* r = findRoute(b.getRouteId());

        if (r != nullptr) {
            cout << "Route: " << r->getSource()
                 << " to " << r->getDestination() << endl;
        }
    }
}

// Add passenger
void addPassenger() {
    string name = readString("Enter passenger name: ");
    string phone = readString("Enter phone number: ");

    passengers.emplace_back(nextPassengerId++, name, phone);

    cout << "Passenger added successfully!\n";
}

// Display passengers
void displayPassengers() {
    if (passengers.empty()) {
        cout << "No passengers registered.\n";
        return;
    }

    cout << "\n--- PASSENGER DETAILS ---\n";

    for (auto &p : passengers)
        p.display();
}

// Book a ticket
void bookTicket() {
    if (passengers.empty() || buses.empty()) {
        cout << "Add passengers and buses before booking.\n";
        return;
    }

    displayPassengers();
    int pid = readInt("Enter Passenger ID: ");

    Passenger* p = findPassenger(pid);

    if (p == nullptr) {
        cout << "Passenger not found!\n";
        return;
    }

    displayBuses();
    int bid = readInt("Enter Bus ID: ");

    Bus* b = findBus(bid);

    if (b == nullptr) {
        cout << "Bus not found!\n";
        return;
    }

    if (b->bookSeat()) {
        bookings.emplace_back(nextTicketId++, pid, bid);

        cout << "\nTicket booked successfully!\n";
        cout << "Passenger: " << pid << endl;
        cout << "Bus: " << bid << endl;
        cout << "Remaining Seats: "
             << b->getAvailableSeats() << endl;
    }
    else {
        cout << "Sorry! No seats available.\n";
    }
}

// Display all bookings
void displayBookings() {
    if (bookings.empty()) {
        cout << "No bookings found.\n";
        return;
    }

    cout << "\n--- BOOKING DETAILS ---\n";

    for (auto &booking : bookings)
        booking.display();
}

// Main menu
int main() {
    int choice;

    do {
        cout << "\n================================\n";
        cout << " PUBLIC TRANSPORT MANAGEMENT\n";
        cout << "================================\n";
        cout << "1. Add Route\n";
        cout << "2. Display Routes\n";
        cout << "3. Add Bus\n";
        cout << "4. Display Buses\n";
        cout << "5. Add Passenger\n";
        cout << "6. Display Passengers\n";
        cout << "7. Book Ticket\n";
        cout << "8. Display Bookings\n";
        cout << "0. Exit\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addRoute();
                break;

            case 2:
                displayRoutes();
                break;

            case 3:
                addBus();
                break;

            case 4:
                displayBuses();
                break;

            case 5:
                addPassenger();
                break;

            case 6:
                displayPassengers();
                break;

            case 7:
                bookTicket();
                break;

            case 8:
                displayBookings();
                break;

            case 0:
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}

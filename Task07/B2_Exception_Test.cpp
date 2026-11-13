#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class ClaimError : public runtime_error {
public:
    ClaimError(const string& message) : runtime_error(message) {}
};

void checkCharge(double amount) {
    if (amount < 0)
        throw runtime_error("Negative bill amount");
    cout << "Valid bill amount: " << amount << endl;
}

void processClaim(double claim, double limit) {
    if (claim > limit)
        throw ClaimError("Claim exceeds coverage limit");
    cout << "Claim approved: " << claim << endl;
}

void checkPackage(string package) {
    if (package != "Basic" && package != "Premium")
        throw runtime_error("Unknown package");
    cout << "Package accepted: " << package << endl;
}

int main() {
    // Test 1: Negative charge
    try {
        checkCharge(-500);
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Test 2: Claim above limit
    try {
        processClaim(5000, 3000);
    }
    catch (const ClaimError& e) {
        cout << "Claim Error: " << e.what() << endl;
    }

    // Test 3: Unknown package
    try {
        checkPackage("Gold");
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Test 4: Invalid numeric input
    try {
        double amount = stod("abc");
        cout << amount << endl;
    }
    catch (const exception& e) {
        cout << "Input Error: " << e.what() << endl;
    }

    // Test 5: Memory allocation error simulation
    try {
        throw bad_alloc();
    }
    catch (const bad_alloc& e) {
        cout << "Memory Error: Allocation failed" << endl;
    }

    // Test 6: Catch all
    try {
        throw 10;
    }
    catch (...) {
        cout << "Unknown error caught" << endl;
    }

    // Test 7: Rethrowing an exception
    try {
        try {
            throw runtime_error("Billing failure");
        }
        catch (const exception& e) {
            cout << "Logged: " << e.what() << endl;
            throw;
        }
    }
    catch (const exception& e) {
        cout << "Handled again: " << e.what() << endl;
    }

    return 0;
}
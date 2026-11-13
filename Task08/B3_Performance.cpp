
#include <iostream>
#include <vector>
#include <variant>
#include <chrono>
#include <stdexcept>
using namespace std;
using namespace chrono;

struct Bill {
    virtual double total() const = 0;
    virtual ~Bill() = default;
};

struct OP : Bill {
    double total() const override { return 500; }
};

struct IP : Bill {
    double total() const override { return 2000; }
};

struct Day : Bill {
    double total() const override { return 1000; }
};

struct Emergency : Bill {
    double total() const override { return 3000; }
};

struct VOP { double total() const { return 500; } };
struct VIP { double total() const { return 2000; } };
struct VDay { double total() const { return 1000; } };
struct VEmergency { double total() const { return 3000; } };

using VariantBill = variant<VOP, VIP, VDay, VEmergency>;

double returnCodeTest(int value) {
    if (value < 0) return -1;
    return value * 2.0;
}

double exceptionTest(int value) {
    if (value < 0)
        throw runtime_error("Invalid value");
    return value * 2.0;
}

int main() {
    OP op;
    IP ip;
    Day day;
    Emergency emergency;

    Bill* bills[] = {&op, &ip, &day, &emergency};

    vector<VariantBill> variants = {
        VOP{}, VIP{}, VDay{}, VEmergency{}
    };

    vector<int> sizes = {1000, 1000000, 10000000};

    cout << "--- Virtual vs Switch ---\n";

    for (int n : sizes) {
        vector<int> types(n);

        for (int i = 0; i < n; i++)
            types[i] = i % 4;

        double virtualSum = 0;
        auto start = steady_clock::now();

        for (int i = 0; i < n; i++)
            virtualSum += bills[types[i]]->total();

        auto end = steady_clock::now();
        auto virtualTime =
            duration_cast<microseconds>(end - start).count();

        double switchSum = 0;
        start = steady_clock::now();

        for (int i = 0; i < n; i++) {
            switch (types[i]) {
                case 0: switchSum += 500; break;
                case 1: switchSum += 2000; break;
                case 2: switchSum += 1000; break;
                case 3: switchSum += 3000; break;
            }
        }

        end = steady_clock::now();
        auto switchTime =
            duration_cast<microseconds>(end - start).count();

        cout << n << " bills: Virtual = " << virtualTime
             << " us, Switch = " << switchTime
             << " us, Checksum = " << virtualSum
             << ", " << switchSum << '\n';
    }

    cout << "\n--- Variant Test ---\n";

    long long variantSum = 0;
    auto start = steady_clock::now();

    for (int i = 0; i < 10000000; i++) {
        variantSum += visit([](const auto& bill) {
            return static_cast<int>(bill.total());
        }, variants[i % 4]);
    }

    auto end = steady_clock::now();

    cout << "Variant 10 million bills = "
         << duration_cast<microseconds>(end - start).count()
         << " us, Checksum = " << variantSum << '\n';

    cout << "\n--- Exceptions vs Return Codes ---\n";

    for (int rate : {0, 1, 50}) {
        long long returnSum = 0;
        int count = 1000000;

        start = steady_clock::now();

        for (int i = 0; i < count; i++) {
            int value = (i % 100 < rate) ? -1 : 10;
            double result = returnCodeTest(value);

            if (result >= 0)
                returnSum += static_cast<int>(result);
        }

        end = steady_clock::now();
        auto returnTime =
            duration_cast<microseconds>(end - start).count();

        long long exceptionSum = 0;
        start = steady_clock::now();

        for (int i = 0; i < count; i++) {
            int value = (i % 100 < rate) ? -1 : 10;

            try {
                exceptionSum += static_cast<int>(exceptionTest(value));
            }
            catch (const exception&) {
            }
        }

        end = steady_clock::now();
        auto exceptionTime =
            duration_cast<microseconds>(end - start).count();

        cout << rate << "% invalid: Return Code = "
             << returnTime << " us, Exception = "
             << exceptionTime << " us\n";

        cout << "Return Checksum = " << returnSum
             << ", Exception Checksum = " << exceptionSum << '\n';
    }

    return 0;
}

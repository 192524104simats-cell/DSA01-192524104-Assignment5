#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Bill {
public:
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual string type() const = 0;
};

class OutPatientBill : public Bill {
public:
    double total() const override { return 500; }
    string type() const override { return "OutPatient"; }
};

class InPatientBill : public Bill {
public:
    double total() const override { return 2000; }
    string type() const override { return "InPatient"; }
};

class DayCareBill : public Bill {
public:
    double total() const override { return 1000; }
    string type() const override { return "DayCare"; }
};

class EmergencyBill : public Bill {
public:
    double total() const override { return 3000; }
    string type() const override { return "Emergency"; }
};

class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        return bill.total();
    }
};

class Insurance : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        return bill.total() * 0.80;
    }
};

class GovernmentScheme : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        if (bill.type() == "OutPatient") return 400;
        if (bill.type() == "InPatient") return 1500;
        if (bill.type() == "DayCare") return 800;
        return 2500;
    }
};

int main() {
    vector<Bill*> bills = {
        new OutPatientBill(),
        new InPatientBill(),
        new DayCareBill(),
        new EmergencyBill()
    };

    SelfPay self;
    Insurance insurance;
    GovernmentScheme government;

    vector<Payer*> payers = {&self, &insurance, &government};

    for (Bill* bill : bills) {
        cout << "\n" << bill->type()
             << " Bill = " << bill->total() << endl;

        for (Payer* payer : payers) {
            double covered = payer->amountCovered(*bill);
            cout << "Covered = " << covered
                 << ", Patient Pays = " << bill->total() - covered
                 << endl;
        }
    }

    for (Bill* bill : bills) {
        delete bill;
    }

    return 0;
}
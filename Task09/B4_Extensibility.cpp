#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Bill {
public:
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual string type() const = 0;
};

class OutPatient : public Bill {
public:
    double total() const override { return 500; }
    string type() const override { return "OutPatient"; }
};

class InPatient : public Bill {
public:
    double total() const override { return 2000; }
    string type() const override { return "InPatient"; }
};

// New bill type added without modifying existing classes
class Maternity : public Bill {
public:
    double total() const override { return 5000; }
    string type() const override { return "Maternity"; }
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

// New payer type added without modifying existing classes
class CorporatePayer : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        return bill.total() * 0.90;
    }
};

int main() {
    OutPatient op;
    InPatient ip;
    Maternity maternity;

    SelfPay self;
    Insurance insurance;
    CorporatePayer corporate;

    vector<Bill*> bills = {&op, &ip, &maternity};
    vector<Payer*> payers = {&self, &insurance, &corporate};

    for (Bill* bill : bills) {
        cout << "\n" << bill->type()
             << " Bill = " << bill->total() << endl;

        for (Payer* payer : payers) {
            double covered = payer->amountCovered(*bill);

            cout << "Covered = " << covered
                 << ", Patient Pays = "
                 << bill->total() - covered << endl;
        }
    }

    return 0;
}
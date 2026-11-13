# TASK A3 – DESIGN WITH ABSTRACT CLASSES

## A3.1 – Payer Interface

An abstract class named `Payer` is created to represent different payment methods.

It contains a pure virtual function:

`amountCovered(const Bill&)`

### Derived Classes

**1. SelfPay**
- The patient pays the entire bill.
- Amount covered = Total bill amount.

**2. Insurance**
- Has a cover limit and co-payment percentage.
- Insurance pays the covered amount after considering the patient's co-payment.

Formula:

Insurance payment = Minimum of (Bill amount × (1 − Co-payment percentage / 100)) and Cover limit.

**3. GovernmentScheme**
- Pays according to fixed package rates.
- Uses the package rate for the particular bill type.

### Class Diagram

```text
             <<Abstract>>
                 Payer
          ---------------------
          + amountCovered()
             {pure virtual}
                 |
       -----------+------------
       |          |            |
    SelfPay   Insurance   GovernmentScheme
```

## A3.2 – Extension

A new payer called `CorporateTieUp` can be added by inheriting the `Payer` class.

It implements `amountCovered()` according to the corporate agreement.

No existing payer class needs to be modified.

Example:

```cpp
class CorporateTieUp : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        return bill.total() * 0.80;
    }
};
```

This demonstrates extensibility through runtime polymorphism.

## Alternative Concept – Function Pointers or std::function

Instead of using an abstract Payer class, payment policies can be stored as function pointers or `std::function` objects.

Example:

```cpp
std::function<double(double)> policy =
    [](double amount) {
        return amount * 0.80;
    };
```

The policy is selected at runtime and applied to the bill amount.

### Complexity Analysis

| Factor | Abstract Payer | std::function |
|---|---|---|
| Time per call | O(1) | O(1) |
| Space | Object data + vptr | Callable storage |
| Cover limit | Stored in derived object | Stored in captured data |
| Extension | Add derived class | Add new function |

**Conclusion:**

Both approaches provide runtime selection. The abstract Payer class is suitable when different payers have their own data and behaviour. `std::function` is useful for storing flexible payment policies.
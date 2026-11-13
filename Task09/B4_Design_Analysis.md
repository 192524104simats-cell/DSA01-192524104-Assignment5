# B4 – Extensibility and Production Design

## 1. Adding a New Bill Type

A new `Maternity` class was added by inheriting from the existing `Bill` class.

It implements:
- `total()` – returns the bill amount.
- `type()` – returns the bill type.

Existing bill classes were not modified.

## 2. Adding a New Payer Type

A new `CorporatePayer` class was added by inheriting from `Payer`.

It covers 90% of the bill amount.

Existing payer classes were not modified.

## 3. Test Results

| Bill Type | Amount | SelfPay | Insurance (80%) | Corporate (90%) |
|---|---:|---:|---:|---:|
| OutPatient | 500 | 500 | 400 | 450 |
| InPatient | 2000 | 2000 | 1600 | 1800 |
| Maternity | 5000 | 5000 | 4000 | 4500 |

All nine bill-payer combinations produced the expected results.

## 4. Memory Safety

Both `Bill` and `Payer` have virtual destructors. The program uses stack-allocated objects and non-owning pointers in its vectors.

AddressSanitizer testing could not be completed because the current MinGW compiler installation could not find the `libasan` library. Therefore, sanitizer success is not claimed.

## 5. Production Design Decision

For a system serving 15 hospitals, with two new bill types and three new payers added every year, and processing 200,000 bills per day, runtime polymorphism is a suitable design.

Reasons:
- New bill and payer classes can be added independently.
- Existing classes need not be modified.
- Virtual functions provide a common interface.
- The design is easier to maintain and extend.

For hospital-specific payment rules, a configurable rules or plugin system can be introduced.

## 6. Final Conclusion

Runtime polymorphism provides flexibility and extensibility for the hospital billing system. New bill types and payer types can be introduced without changing existing classes. This makes the design suitable for a growing billing application.
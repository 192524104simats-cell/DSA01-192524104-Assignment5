# TASK A1 – DESIGN THE POLYMORPHIC BILL HIERARCHY

## A1.1 – Identify the Common Interface

A hospital billing system contains different types of bills. All bills share common information and operations.

**Common Data:**
- Patient name
- Bill ID
- Bill date

**Common Operations:**
1. `total()` – Calculates the total bill amount.
2. `type()` – Returns the type of bill.
3. `print()` – Displays the bill details.

The `total()` and `type()` functions are declared as virtual functions. The `total()` function is pure virtual because every bill calculates its amount differently.

## A1.2 – Design the Hierarchy

An abstract base class named `Bill` is created.

Derived classes:
1. OutPatientBill – Consultation and test charges.
2. InPatientBill – Room charges, procedures and medicines.
3. DayCareBill – Fixed package charges.
4. EmergencyBill – Base charge and time-based charges.

**UML Class Diagram**

```text
                 <<Abstract>>
                     Bill
             ---------------------
             - patientName
             - billID
             ---------------------
             + total() : double
                 {pure virtual}
             + type() : string
                 {virtual}
             + print() : void
                 {virtual}
             + ~Bill()
                 {virtual}
                     |
          ------------+------------
          |           |            |
          |           |            |
   OutPatientBill InPatientBill DayCareBill
          |
          |             EmergencyBill
          
```

**Function Details:**

- `total()` – Pure virtual function.
- `type()` – Virtual function.
- `print()` – Virtual function or common display function.
- `~Bill()` – Virtual destructor.
- Derived classes override `total()` and `type()`.

Each derived class calculates its bill differently.

## A1.3 – Process All Bills Together

An array of base-class pointers is used to store different types of bills.

### Pseudocode

```text
ALGORITHM CalculateDailyTotal

BEGIN
    DECLARE bills AS ARRAY OF Bill POINTERS
    DECLARE sum AS REAL
    SET sum = 0

    FOR EACH bill IN bills DO
        DISPLAY bill.type()
        DISPLAY bill.total()
        SET sum = sum + bill.total()
    END FOR

    DISPLAY "Daily Total = ", sum
END

```

## Alternative Concept – Structure with Switch

Instead of using an abstract base class, all bills can be represented using one structure with a type field.

A switch statement can calculate the bill based on its type.

**Pseudocode:**

```text
FUNCTION total(bill)

BEGIN
    SWITCH bill.type

        CASE OUTPATIENT:
            RETURN consultation + tests

        CASE INPATIENT:
            RETURN roomCharges + procedures + medicines

        CASE DAYCARE:
            RETURN packagePrice

        CASE EMERGENCY:
            RETURN baseCharge + timeCharges

        DEFAULT:
            RETURN 0

    END SWITCH
END
```

### Complexity Analysis

| Operation | Polymorphism | Switch Method |
|---|---|---|
| Calculate n bills | O(n) | O(n) |
| Time per bill | O(1) | O(1) |
| Space per bill | Data + vptr | Data + type field |
| Adding a new bill | Add a derived class | Modify switch statement |

**Conclusion:**

Both approaches require O(n) time to calculate n bills. However, runtime polymorphism is more flexible because new bill types can be added without modifying existing billing code. Therefore, the polymorphic approach is preferred for the hospital billing system.
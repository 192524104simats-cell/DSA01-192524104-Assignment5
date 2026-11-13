# TASK A2 – UNDERSTAND RUNTIME BINDING

## A2.1 – Early and Late Binding

**Early Binding:**

Early binding happens at compile time. The function call is decided by the compiler based on the declared type.

**Late Binding:**

Late binding happens at runtime. When a virtual function is called through a base-class pointer, the derived-class function is executed based on the actual object.

Example:

```cpp
Bill* b = new OutPatientBill();
b->total();
```

Here, the derived class's `total()` function is executed through runtime polymorphism.

## A2.2 – Virtual Table (Vtable)

A vtable is a compiler-generated table containing pointers to virtual functions.

Example:

```text
Bill Vtable
----------------
total() = 0
type() = Bill

OutPatientBill Vtable
----------------
total() = OutPatientBill::total()
type() = OutPatientBill::type()

InPatientBill Vtable
----------------
total() = InPatientBill::total()
type() = InPatientBill::type()
```

**How b->total() works:**

1. A base-class pointer stores the address of a derived-class object.
2. The object has access to its class's virtual function table.
3. The virtual call finds the correct function.
4. The derived-class `total()` function executes.

## A2.3 – Virtual Destructor

A virtual destructor ensures that the derived-class destructor is called when a derived object is deleted using a base-class pointer.

Without a virtual destructor, deleting a derived object through a base pointer causes undefined behaviour.

Therefore, the base class must have a virtual destructor.

## Alternative Concept – dynamic_cast

If total() is not virtual, the program can use dynamic_cast to identify the actual derived object and call its function.

Example pseudocode:

```text
FOR EACH bill
    IF bill is OutPatientBill
        calculate outpatient total
    ELSE IF bill is InPatientBill
        calculate inpatient total
    END IF
END FOR
```

### Complexity Analysis

| Factor | Virtual Function | dynamic_cast |
|---|---|---|
| Time per bill | O(1) | Up to O(k) |
| Space | Vtable pointer per object | No virtual dispatch requirement |
| Extension | Easy | Requires additional checks |

Here, k represents the number of bill types.

**Conclusion:**

Virtual functions provide simpler and more efficient runtime selection when many different bill types are processed through a common interface.
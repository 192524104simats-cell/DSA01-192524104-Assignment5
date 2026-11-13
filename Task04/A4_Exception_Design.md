# A4 – Exception Handling Design

## 1. Possible Billing Errors

The billing system may face the following errors:

| Error | Example |
|---|---|
| Invalid charge | Negative bill amount |
| Invalid patient data | Empty patient name |
| Invalid payer | Unknown payer type |
| Invalid claim | Claim amount exceeds allowed limit |
| Invalid input | Text entered instead of a number |
| Memory allocation failure | Memory unavailable |

## 2. Exception Hierarchy

All custom exceptions are derived from `std::exception`.

```text
std::exception
      |
   BillingError
      |
  --------------
  |      |     |
Invalid Invalid Claim
Charge  Input  Error
```

- `BillingError`: Base class for billing-related errors.
- `InvalidCharge`: Used for negative charges.
- `InvalidInput`: Used for invalid user input.
- `ClaimError`: Used for invalid insurance claims.

## 3. Functions That May Throw

The following functions may throw exceptions:

- `calculateTotal()` – if the bill amount is invalid.
- `processClaim()` – if the claim is invalid.
- `readInput()` – if the input cannot be converted.
- Memory allocation – may throw `std::bad_alloc`.

## 4. Functions That Should Be noexcept

Functions that are guaranteed not to throw can be marked `noexcept`.

Examples:
- Simple getter functions.
- Functions that return stored values without risky operations.

## 5. Why Destructors Should Not Throw

Destructors are called automatically when objects are destroyed. If a destructor throws during stack unwinding, the program may terminate. Therefore, destructors should not throw exceptions.

## 6. Exception Handling vs Return Codes

| Exception Handling | Return Codes |
|---|---|
| Uses `try`, `throw`, and `catch` | Uses status values |
| Separates error handling from normal code | Requires checking return values |
| Useful for unexpected errors | Useful for expected errors |
| Can make control flow harder to
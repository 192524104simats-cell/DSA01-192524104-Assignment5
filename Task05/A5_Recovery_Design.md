# A5 – Exception Recovery Design

## 1. Catch, Log and Rethrow

When an error occurs, the program should catch the exception, record the error and rethrow it if the current function cannot handle it.

Example:

```cpp
try {
    processBill();
}
catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    throw;
}
```

## 2. Recovery Strategy

- Catch known billing errors.
- Display a clear error message.
- Record the error in a log.
- Allow the user to correct invalid input.
- Continue processing other bills when safe.
- Stop processing if the error cannot be recovered.

## 3. RAII and Stack Unwinding

RAII means Resource Acquisition Is Initialization.

It connects resource management to object lifetime. Resources are automatically released when objects are destroyed.

Stack unwinding occurs when an exception leaves a scope. Local objects are destroyed automatically while the program moves to a matching catch block.

## 4. RAII Example

```cpp
#include <iostream>
#include <memory>
using namespace std;

int main() {
    try {
        unique_ptr<int> bill(new int(500));
        cout << "Bill Amount = " << *bill << endl;
        throw runtime_error("Billing error");
    }
    catch (const exception& e) {

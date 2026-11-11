# Task03 - Constructors and Member Classes

## Purpose
This task implements the required C++ concept using a small example connected to the assignment question.

## Design notes
- Data is kept inside the class where it belongs.
- Constructors initialise members directly.
- Where a resource is allocated manually, its matching destructor releases it.
- Derived classes override the required functions and use `override`.
- Input checks are kept close to the operation that can fail.

## Complexity
The examples use fixed-size object operations unless a loop is shown. A loop over `n` objects is O(n); a single calculation, lookup in the fixed examples, or virtual function call is O(1). Dynamic copying of `n` strings or array elements is O(n) time and O(n) additional space.

## Build and run
```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o run
./run
```

## Result
The program was compiled and run. The output is saved in `sample_output.txt`, and a terminal-style capture of that run is saved in `evidence/01_compile_and_run.png`.

## Limitations
The program is an assignment demonstration, not a production billing, payroll, booking or rental system. Real systems would need persistent storage, stronger validation and more complete business rules.

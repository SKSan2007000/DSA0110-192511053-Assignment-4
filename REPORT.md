
# ASSIGNMENT 4 – CO4
## DESIGNING REUSABLE CLASS HIERARCHIES

**Course Code:** DSA0110  
**Course Name:** Object-Oriented Programming with C++  
**Submitted by:** B. Santhosh Kumar  
**Register Number:** 192511053  
**GitHub Repository:** https://github.com/SKSan2007000/DSA01-192511053-Assignment4  
**Compiler:** g++ 13, C++17  
**Submission Date:** 11 November 2026

---

# TASK 1 – CLASS DESIGN REVIEW

### 1.1 Design problems
The original payroll classes repeat `name`, `id` and `basic`; expose data publicly; use inconsistent names (`name`/`nm`, `id`/`code`); contain an unused `da` field; repeat the 0.42 allowance as a magic number; and cannot be processed through one common collection.

### 1.2 Repaired hierarchy
`Staff` stores common fields and declares `virtual double pay() const = 0`. `Professor`, `LabAssistant` and `GuestFaculty` implement their own pay rule. A `vector<Staff*>` demonstrates processing all staff in one loop. The base destructor is virtual so deleting a derived object through a base pointer is safe.

### 1.3 Design defence
A new staff category can derive from `Staff` and implement `pay()`. Existing payroll code can continue to call `pay()` through a `Staff*`; it does not need a new switch branch.

### Alternative
A single `Staff` with a type field and switch also takes O(1) time per pay calculation. However, adding a category changes the central switch and may require adding more fields that are unused for other categories. The hierarchy keeps category-specific data in the relevant derived class.

---

# TASK 2 – FROM REQUIREMENT TO HIERARCHY

### Relationships
`Student` is-a `Person`; `Staff` is-a `Person`; `TeachingAssistant` is-a both `Student` and `Staff`; `ResearchScholar` can derive from `Student` and add fellowship data. These form hierarchical, multiple and hybrid inheritance.

### Diamond problem
If `Student` and `Staff` each inherit `Person` normally, a `TeachingAssistant` contains two `Person` subobjects. Accessing a common member such as `name` becomes ambiguous. Declaring both paths as `virtual public Person` makes the most-derived object share one `Person` subobject. The most-derived `TeachingAssistant` constructor initialises that virtual base.

### Access table
| Person member | Public inheritance | Protected inheritance | Private inheritance |
|---|---|---|---|
| public | public | protected | private |
| protected | protected | protected | private |
| private | not directly accessible | not directly accessible | not directly accessible |

### Predicted output
```text
Person Student Staff TA
```
`Person` is constructed once because it is a virtual base. Construction order is virtual bases first, then direct bases in declaration order, then members, then the derived constructor body.

### Composition alternative
A `TeachingAssistant` containing separate `Student` and `Staff` members has two `Person` subobjects. Composition is suitable when the object owns two separate components rather than being both types. It avoids inheritance ambiguity but accessing the person's data requires selecting the relevant member.

---

# TASK 3 – CONSTRUCTORS IN DERIVED CLASSES AND MEMBER CLASSES

### Initialisation design
`Person` owns an `Address` member. `Student` publicly derives from `Person`, adds a registration number and a `Course` member object, and initialises the base and members through its initializer list. A virtual base must be initialised by the most-derived constructor; intermediate constructors' virtual-base initialisers are ignored when a more-derived object is built.

### Construction and destruction
Construction order is virtual base classes, direct base classes, data members in declaration order, then the constructor body. Destruction is the reverse: derived destructor body, members in reverse declaration order, then base classes in reverse order.

### Predicted output for the supplied Car example
```text
Vehicle Engine Car | ~Car ~Engine ~Vehicle
```
`Vehicle` is constructed before the `Engine` member and `Car` body. Destruction reverses that order.

### Complete-code result
```text
192311001 Kavya (19) Salem-636001
```
The `Student` constructor initialises `Person(n,a)`, then `regNo`, then `home(c,p)` in declaration order.

### Alternative
A dynamically allocated `Address*` adds allocation and deallocation work and requires correct copy-constructor, assignment and destructor behaviour. A direct `Address` member is simpler and automatically follows the containing object's lifetime. A vector or value member is preferable unless independent dynamic lifetime is actually needed.

---

# TASK 4 – POINTERS TO DERIVED CLASSES: FORENSICS

### Defects
The non-virtual `rate()` is statically bound through `Account*`, so the senior rate is not selected. Deleting a derived object through a base pointer without a virtual base destructor is undefined behaviour. Copying a `SeniorAccount` into an `Account` object causes object slicing; derived data and behaviour are lost.

### Repair
The corrected example declares `rate()` virtual, uses `override`, declares a virtual destructor and stores objects as `unique_ptr<Account>`. The senior account's dynamically allocated history is released by its destructor.

### Predicted output for the supplied program
```text
3.5 4 3.5
```
`p->rate()` calls the non-virtual base function; `p->vrate()` calls the overridden derived function at runtime; `copy.vrate()` calls the base implementation because `copy` is a sliced `Account` object.

### Prevention
Use `override` on intended overrides and make a polymorphic base destructor virtual. Prefer smart pointers and avoid storing derived objects by value in a base-class container.

### Alternative
`vector<unique_ptr<Account>>` takes O(n) total processing time for n accounts and stores one pointer per element plus each object. It prevents leaks caused by forgetting `delete`, while virtual dispatch still selects the derived implementation. It cannot prevent incorrect non-virtual functions or object slicing if values are copied elsewhere.

---

# TASK 5 – POINTERS TO OBJECTS AND THE this POINTER

### Four ways
A local `Cart` can be used directly by its name. A pointer uses `->`. A reference is an alias to an existing object. A dynamically allocated object uses `new` and must be released with `delete`, though smart pointers are safer.

### this pointer
`this` is the address of the current object. `*this` refers to the current object itself. Returning `Cart&` from `add()` and `setDiscount()` allows method chaining. `this->discount` distinguishes the data member from the parameter with the same name.

### Complete-code output
```text
324.00
Highest cart: 324
```
The cart total is `(60 + 120 + 180) * 0.90 = 324`.

### If add returned Cart by value
Each call would return a copy. The chained next call would operate on that temporary copy rather than the original cart, so changes may not remain in `c`. Returning `Cart&` refers to the same object.

### Alternative
A `vector<Cart>` stores objects directly and finds the highest total in O(n), like an array of pointers. It avoids separate allocations and pointer ownership. However, vector growth can invalidate pointers and references to its elements. An array of pointers stores one pointer per slot and keeps separately allocated cart addresses stable, but requires ownership management.

---

# TASK 6 – VEHICLE RENTAL FLEET DESIGN CHALLENGE

### Requirements and design
Every vehicle has a registration number, daily rate and rental state. Each vehicle calculates its own charge. Bicycle, two-wheeler, car and electric car derive from an abstract `Vehicle`. A virtual `charge(days)` function provides runtime polymorphism. The fleet is stored as `vector<unique_ptr<Vehicle>>`.

### Rental and return pseudocode
```text
RENT(vehicle)
    IF vehicle is already rented
        RETURN failure
    SET rented = true
    RETURN success

RETURN(vehicle, lateDays)
    SET rented = false
    lateCharge = lateDays * lateRate
    RETURN lateCharge
```

### Implementation demonstration
The implementation rents and lists one bicycle, two-wheeler, car, electric car and an added electric bus. The electric bus is a new derived class; the fleet loop does not need to change. Each class implements `charge()`.

### Complexity and alternative
The virtual call and a switch statement are both O(1) per charge calculation. A single `Vehicle` with a type code requires a switch and may carry unused fields. The hierarchy stores only relevant fields in each class and makes adding a new vehicle type local to the new class. The base pointer has a small vtable-related overhead, but the design is easier to extend.

---

## Overall conclusion
Inheritance is useful when objects share a genuine is-a relationship and need a common interface. Composition is useful for contained parts such as `Address`. Virtual functions support runtime selection, virtual destructors support safe cleanup, and smart pointers reduce manual memory errors. The examples use small classes so that construction, access and object lifetime can be followed clearly.

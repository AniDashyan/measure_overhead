# Measuring Overhead of Security Features
##  Overview

This project benchmarks the **performance overhead** introduced by common **compiler-based security features**, such as stack protection and fortified memory operations. It measures the time taken by:

- Function calls in a tight loop
- Dynamic memory allocations (`malloc`/`free`)

The goal is to compare execution time with and without security features like `-fstack-protector-strong` and `-D_FORTIFY_SOURCE=2`.

## Build & Run
```bash
# Clone the repo
git clone https://github.com/AniDashyan/measure_overhead
cd measure_overhead

# Build with security flags enabled
cmake -S . -B build -DENABLE_SECURITY_FLAGS=ON
cmake --build build

# OR build without security flags
cmake -S . -B build -DENABLE_SECURITY_FLAGS=OFF
cmake --build build

# Run the executable
./build/benchmark  # Linux/macOS
.\build\benchmark.exe  # Windows
```

---

## Example Output

###  With Security Flags (`-fstack-protector-strong`, `-D_FORTIFY_SOURCE=2`)

```
Function call time: 0.962453 seconds
Malloc/Free time: 0.153870 seconds
```

### Without Security Flags

```
Function call time: 0.813744 seconds
Malloc/Free time: 0.121653 seconds
```

---

##  How Does It Work?

The benchmark runs two performance tests:

1. **Function Call Loop**:
   A trivial function is called in a tight loop (100 million iterations). Stack protector flags introduce additional checks (e.g., canary values) on function entry/exit, which can slightly increase execution time.

2. **Memory Allocation Loop**:
   A smaller loop repeatedly calls `malloc` and `free`. Fortify source adds runtime checks to detect memory misuse, which can affect performance depending on how memory is managed.

###  Why It Matters

* **Stack protection** (`-fstack-protector-strong`, `/GS`) prevents stack smashing by inserting a guard value (canary) to detect overflows.
* **FORTIFY\_SOURCE** adds lightweight runtime checks to standard library functions like `memcpy`, `strcpy`, etc.
* These features **significantly improve security**, but may **slightly reduce performance**—especially in hot code paths or constrained environments.

This project quantifies that cost.

# LBYARCH-MP2: Distance Kernel in C and x86-64 Assembly

This project implements a kernel to compute the Euclidean distances between points using both a C version and an x86-64 assembly version. The input vectors `X1`, `X2`, `Y1`, `Y2` contain `n` double-precision floating-point numbers. The output vector `Z` contains the computed distances.

## Files
- `x64.asm` — x86-64 assembly kernel
- `CAssembly.c` — C program containing:
  - C kernel implementation
  - Benchmark loop
  - Correctness check
  - Call to `x64` assembly kernel

## How to Run

### 1. Assemble the x86-64 kernel
```bash
nasm -f win64 x64.asm -o x64.obj
```
### 2. Compile the C program with the kernel object file
```bash
gcc CAssembly.c x64.obj -o test.exe
```
### 3. Execute the compiled program
```bash
.\test.exe
```

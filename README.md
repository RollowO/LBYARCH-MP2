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
### 1. Open directory/ location of the folder in terminal
```bash
cd (LOCATION/LOCATION)
```
### 2. Assemble the x86-64 kernel
```bash
nasm -f win64 x64.asm -o x64.obj
```
### 3. Compile the C program with the kernel object file
```bash
gcc CAssembly.c x64.obj -o test.exe
```
### 4. Execute the compiled program
```bash
.\test.exe
```


### Results & Screenshots
<img width="632" height="107" alt="image" src="https://github.com/user-attachments/assets/88398c4e-5e7b-42b1-abf9-dc08624039c4" />

The Photo above contains the C correctness check and the performance of the kernels. From the results seen above, theres clearly a massive difference between the cycle C takes and x64 sasm takes.

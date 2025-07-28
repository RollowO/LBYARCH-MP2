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
<img width="696" height="151" alt="image" src="https://github.com/user-attachments/assets/7d549f7e-b143-4276-aa91-ba6d157c37c4" />

The Photo above contains the C correctness check and the performance of the kernels. From the results seen above, theres clearly a massive difference between the cycle C takes and x64 sasm takes.
From the results above, C kernel took 79187542210 cycles while x86-x64 only took 31124452345 cycles for the vector size 2^27 and 30 runs for each kernel. 

C kernel took more than double the cycles x86-x64 took in the results.
<img width="856" height="224" alt="image" src="https://github.com/user-attachments/assets/c31bbfc0-9e91-4502-a126-db8218aac161" />

In the main C file, it contains the correctness check and checks all of the results, if theres a mismatch then it will say so.

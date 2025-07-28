#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <x86intrin.h>  // for __rdtsc

void euclidean_c(const double *X1, const double *X2,
                 const double *Y1, const double *Y2,
                 double *Z, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        double dx = X2[i] - X1[i];
        double dy = Y2[i] - Y1[i];
        Z[i] = sqrt(dx * dx + dy * dy);
    }
}
void x64(double *Z, const double *X1, const double *X2,
         const double *Y1, const double *Y2, int n);  // 'int' if your ASM uses 32-bit n

int main() {
    size_t n = 1UL << 27;  // 2^27 = 134,217,728

    // Allocate aligned memory
    double *X1 = _aligned_malloc(n * sizeof(double), 32);
    double *X2 = _aligned_malloc(n * sizeof(double), 32);
    double *Y1 = _aligned_malloc(n * sizeof(double), 32);
    double *Y2 = _aligned_malloc(n * sizeof(double), 32);
    double *Z1 = _aligned_malloc(n * sizeof(double), 32);  // C result
    double *Z2 = _aligned_malloc(n * sizeof(double), 32);  // ASM result

    if (!X1 || !X2 || !Y1 || !Y2 || !Z1 || !Z2) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize input
    for (size_t i = 0; i < n; ++i) {
        X1[i] = 1.0 * i;
        X2[i] = 2.0 * i;
        Y1[i] = 0.5 * i;
        Y2[i] = 1.5 * i;
    }

    // -----------------------
    // Benchmark C version
    // -----------------------
    uint64_t total_cycles_c = 0;
    for (int run = 0; run < 30; ++run) {
        uint64_t start = __rdtsc();
        euclidean_c(X1, X2, Y1, Y2, Z1, n);
        uint64_t end = __rdtsc();
        total_cycles_c += (end - start);
    }

    // -----------------------
    // Benchmark Assembly version
    // -----------------------
    uint64_t total_cycles_asm = 0;
    for (int run = 0; run < 30; ++run) {
        uint64_t start = __rdtsc();
        x64(Z2, X1, X2, Y1, Y2, (int)n);  // Use (int)n if your ASM uses 32-bit int
        uint64_t end = __rdtsc();
        total_cycles_asm += (end - start);
    }

    // -----------------------
    // Verify correctness
    // -----------------------
    int mismatch = 0;
    for (size_t i = 0; i < n; ++i) {
        if (fabs(Z1[i] - Z2[i]) > 1e-9) {
            printf("Mismatch at i = %zu: C = %f, ASM = %f\n", i, Z1[i], Z2[i]);
            mismatch = 1;
            break;
        }
    }

    // -----------------------
    // Print results
    // -----------------------
    printf("Total cycles for each kernel:\n");
    printf("  C version:    %llu cycles\n", total_cycles_c);
    printf("  x64 version:  %llu cycles\n", total_cycles_asm);
    printf("Average CPU cycles over 30 runs (n = %zu):\n", n);
    printf("  C version:    %llu cycles\n", total_cycles_c / 30);
    printf("  x64 version:  %llu cycles\n", total_cycles_asm / 30);
    printf("Sample C: Z[0] = %f, Z[1] = %f\n", Z1[0], Z1[1]);
    printf("Sample Asm: Z[0] = %f, Z[1] = %f\n", Z2[0], Z2[1]);

    if (!mismatch) {
        printf("Outputs match.\n");
    }

    _aligned_free(X1);
    _aligned_free(X2);
    _aligned_free(Y1);
    _aligned_free(Y2);
    _aligned_free(Z1);
    _aligned_free(Z2);

    return 0;
}
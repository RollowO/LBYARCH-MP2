#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <x86intrin.h>  // For __rdtsc

// Prototypes
void x64(double* Z, const double* X1, const double* X2,
         const double* Y1, const double* Y2, int n);

void euclidean_c(const double *X1, const double *X2,
                 const double *Y1, const double *Y2,
                 double *Z, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        double dx = X2[i] - X1[i];
        double dy = Y2[i] - Y1[i];
        Z[i] = sqrt(dx * dx + dy * dy);
    }
}

int main() {
    size_t n = 4;
    double X1[] = {1.5, 4.0, 3.5, 2.0};
    double X2[] = {3.0, 2.5, 2.5, 1.0};
    double Y1[] = {4.0, 3.0, 3.5, 3.0};
    double Y2[] = {2.0, 2.5, 1.0, 1.5};
    double Z_asm[4] = {0};
    double Z_c[4] = {0};

    uint64_t total_cycles_asm = 0;
    uint64_t total_cycles_c = 0;

    // Benchmark ASM
    for (int i = 0; i < 30; ++i) {
        uint64_t start = __rdtsc();
        x64(Z_asm, X1, X2, Y1, Y2, (int)n);
        uint64_t end = __rdtsc();
        total_cycles_asm += (end - start);
    }

    // Benchmark C
    for (int i = 0; i < 30; ++i) {
        uint64_t start = __rdtsc();
        euclidean_c(X1, X2, Y1, Y2, Z_c, n);
        uint64_t end = __rdtsc();
        total_cycles_c += (end - start);
    }

    printf("Average CPU cycles over 30 runs (n = %zu):\n", n);
    printf("  Assembly : %llu cycles\n", total_cycles_asm / 30);
    printf("  C version: %llu cycles\n", total_cycles_c / 30);

    // Verify correctness
    printf("\nResults:\n");
    for (int i = 0; i < (int)n; ++i) {
        printf("Z_asm[%d] = %f\tZ_c[%d] = %f\n", i, Z_asm[i], i, Z_c[i]);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Set to 0 to use normal-speed C code (FAST)
#define SLOW_C 0

extern void imgCvtGrayIntToFloat(int *intPixels, float *floatPixels, int height, int width);

// Optional slow float conversion (not used when SLOW_C is 0)
#if SLOW_C
float toFloatSlow(int val) {
    volatile float f = (float)val;
    f = f * 1.0000001f;  // dummy multiply
    f = f / 1.0000001f;  // undo dummy multiply
    return f / 255.0f;
}
#endif

void imgCvtGrayIntToFloat_C(int *intPixels, float *floatPixels, int height, int width) {
#if SLOW_C
    for (int i = 0; i < height * width; i++) {
        floatPixels[i] = toFloatSlow(intPixels[i]);
    }
#else
    for (int i = 0; i < height * width; i++) {
        floatPixels[i] = (float)intPixels[i] / 255.0f;
    }
#endif
}

void initializeImage(int *imgPixels, int size) {
    for (int i = 0; i < size; i++) {
        imgPixels[i] = i % 256;
    }
}

int main() {
    int height = 1000, width = 1000;
    int totalPixels = height * width;

    int *imgPixels = malloc(sizeof(int) * totalPixels);
    float *floatPixelsC = malloc(sizeof(float) * totalPixels);
    float *floatPixelsASM = malloc(sizeof(float) * totalPixels);

    if (!imgPixels || !floatPixelsC || !floatPixelsASM) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    initializeImage(imgPixels, totalPixels);

    clock_t start_c, end_c;
    clock_t start_asm, end_asm;
    double totalTimeC = 0.0, totalTimeASM = 0.0;
    int iterations = 30;
    int error_flag = 0;

    for (int i = 0; i < iterations; i++) {
        // C version
        start_c = clock();
        imgCvtGrayIntToFloat_C(imgPixels, floatPixelsC, height, width);
        end_c = clock();
        totalTimeC += ((double)(end_c - start_c)) / CLOCKS_PER_SEC;

        // ASM version
        start_asm = clock();
        imgCvtGrayIntToFloat(imgPixels, floatPixelsASM, height, width);
        end_asm = clock();
        totalTimeASM += ((double)(end_asm - start_asm)) / CLOCKS_PER_SEC;

        // Check correctness
        for (int j = 0; j < totalPixels; j++) {
            if (fabs(floatPixelsC[j] - floatPixelsASM[j]) > 1e-6f) {
                printf("Mismatch at index %d: C = %f, ASM = %f\n", j, floatPixelsC[j], floatPixelsASM[j]);
                error_flag = 1;
                break;
            }
        }

        if (error_flag) break;
    }

    printf("\nERROR CHECKING:\n");
    if (!error_flag) {
        printf("  Result: All outputs match across all iterations. ✅\n\n");
    } else {
        printf("  Result: Mismatch found between C and ASM outputs. ❌\n\n");
    }

    double avgTimeC = totalTimeC / iterations;
    double avgTimeASM = totalTimeASM / iterations;

    printf("AVERAGE EXECUTION TIMES (over %d iterations):\n", iterations);
    printf("  C Version     : %.8f seconds\n", avgTimeC);
    printf("  Assembly      : %.8f seconds\n", avgTimeASM);
    if (avgTimeASM > 0.0) {
        printf("  Speedup (C/ASM): %.2fx faster\n", avgTimeC / avgTimeASM);
    }

    free(imgPixels);
    free(floatPixelsC);
    free(floatPixelsASM);

    return 0;
}

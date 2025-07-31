#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define HEIGHT 100
#define WIDTH 100
#define ITERATIONS 30
#define EPSILON 1e-6

extern void imgCvtGrayInttoFloat(int *intPixels, float *floatPixels, int height, int width);

// Reference C version
void imgCvtGrayInttoFloat_C(int *intPixels, float *floatPixels, int height, int width) {
    int total = height * width;
    int i;
    for (i = 0; i < total; i++) {
        floatPixels[i] = (float)intPixels[i] / 255.0f;
    }
}

int main() {
    srand(time(NULL));  

    int i, j;
    int *intPixels = malloc(sizeof(int) * HEIGHT * WIDTH);
    float *floatPixelsC = malloc(sizeof(float) * HEIGHT * WIDTH);
    float *floatPixelsASM = malloc(sizeof(float) * HEIGHT * WIDTH);

    for (i = 0; i < HEIGHT * WIDTH; i++) {
        intPixels[i] = rand() % 256;
    }

    imgCvtGrayInttoFloat_C(intPixels, floatPixelsC, HEIGHT, WIDTH);
    imgCvtGrayInttoFloat(intPixels, floatPixelsASM, HEIGHT, WIDTH);

    int sampleH = 5, sampleW = 5;
    printf("Sample of Input Image (intPixels):\n");
    for (i = 0; i < sampleH; i++) {
        for (j = 0; j < sampleW; j++) {
            printf("%3d ", intPixels[i * WIDTH + j]);
        }
        printf("\n");
    }

    printf("\nC Version Output (floatPixelsC):\n");
    for (i = 0; i < sampleH; i++) {
        for (j = 0; j < sampleW; j++) {
            printf("%.3f ", floatPixelsC[i * WIDTH + j]);
        }
        printf("\n");
    }

    printf("\nASM Version Output (floatPixelsASM):\n");
    for (i = 0; i < sampleH; i++) {
        for (j = 0; j < sampleW; j++) {
            printf("%.3f ", floatPixelsASM[i * WIDTH + j]);
        }
        printf("\n");
    }

    // === ERROR CHECK ===
    int correct = 1;
    for (i = 0; i < HEIGHT * WIDTH; i++) {
        if (fabs(floatPixelsASM[i] - floatPixelsC[i]) > EPSILON) {
            correct = 0;
            printf("\nMismatch at index %d: C=%.6f, ASM=%.6f\n", i, floatPixelsC[i], floatPixelsASM[i]);
            break;
        }
    }

    printf("\nERROR CHECKING:\n");
    if (correct) {
        printf("  Result: All outputs match.\n");
    } else {
        printf("  Result: ERROR - Outputs do not match!\n");
    }

    // === PERFORMANCE TEST ===
    double time_c = 0.0, time_asm = 0.0;
    clock_t start, end;

    for (i = 0; i < ITERATIONS; i++) {
        start = clock();
        imgCvtGrayInttoFloat_C(intPixels, floatPixelsC, HEIGHT, WIDTH);
        end = clock();
        time_c += (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        imgCvtGrayInttoFloat(intPixels, floatPixelsASM, HEIGHT, WIDTH);
        end = clock();
        time_asm += (double)(end - start) / CLOCKS_PER_SEC;
    }

    time_c /= ITERATIONS;
    time_asm /= ITERATIONS;

    printf("\nAVERAGE EXECUTION TIMES (over %d iterations):\n", ITERATIONS);
    printf("  C Version     : %.8f seconds\n", time_c);
    printf("  Assembly      : %.8f seconds\n", time_asm);

    if (time_asm > 0.0)
        printf("  Speedup (C/ASM): %.2fx faster\n", time_c / time_asm);
    else
        printf("  Speedup (C/ASM): N/A (assembly time too fast to measure)\n");

    // Cleanup
    free(intPixels);
    free(floatPixelsC);
    free(floatPixelsASM);

    return 0;
}


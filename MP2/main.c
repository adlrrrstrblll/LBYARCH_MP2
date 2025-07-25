#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define ITERATIONS 30
#define EPSILON 1e-6

extern void imgCvtGrayIntToFloat(int *intPixels, float *floatPixels, int height, int width);

// Reference C version 
void imgCvtGrayIntToFloat_C(int *intPixels, float *floatPixels, int height, int width) {
    int total = height * width;
	int i;
    for (i = 0; i < total; i++) {
        floatPixels[i] = (float)intPixels[i] / 255.0f;
    }
}

void printFloatImage(float *img, int height, int width) {
	int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%.2f ", img[i * width + j]);
        }
        printf("\n");
    }
}

void printIntImage(int *img, int height, int width) {
    int i, j;
	for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%d ", img[i * width + j]);
        }
        printf("\n");
    }
}

int main() {
	int i, j;
    int height = 3;
    int width = 4;
    int intPixels[3][4] = {
        {64, 89, 114, 84},
        {140, 166, 191, 84},
        {216, 242, 38, 84}
    };

    float floatPixelsASM[3][4] = {0};
    float floatPixelsC[3][4] = {0};

    printf("Original Input Image:\n");
    printIntImage(&intPixels[0][0], height, width);

    // Run C version
    imgCvtGrayIntToFloat_C(&intPixels[0][0], &floatPixelsC[0][0], height, width);

    // Run ASM version
    imgCvtGrayIntToFloat(&intPixels[0][0], &floatPixelsASM[0][0], height, width);

    printf("\nConverted Image (ASM Version):\n");
    printFloatImage(&floatPixelsASM[0][0], height, width);

    int correct = 1;
    for (i = 0; i < height * width; i++) {
        if (fabs(floatPixelsASM[0][i] - floatPixelsC[0][i]) > EPSILON) {
            correct = 0;
            break;
        }
    }

    printf("\nERROR CHECKING:\n");
    if (correct) {
        printf("  Result: All outputs match across all iterations.");
    } else {
        printf("  Result: ERROR - Outputs do not match!\n");
    }

    // Performance Test Loop
    double time_c = 0.0, time_asm = 0.0;
    clock_t start, end;

    for (i = 0; i < ITERATIONS; i++) {
        // C version
        start = clock();
        imgCvtGrayIntToFloat_C(&intPixels[0][0], &floatPixelsC[0][0], height, width);
        end = clock();
        time_c += (double)(end - start) / CLOCKS_PER_SEC;

        // ASM version
        start = clock();
        imgCvtGrayIntToFloat(&intPixels[0][0], &floatPixelsASM[0][0], height, width);
        end = clock();
        time_asm += (double)(end - start) / CLOCKS_PER_SEC;
    }

    time_c /= ITERATIONS;
    time_asm /= ITERATIONS;
    double speedup = time_c / time_asm;

    // Report Summary
    printf("\nAVERAGE EXECUTION TIMES (over %d iterations):\n", ITERATIONS);
    printf("  C Version     : %.8f seconds\n", time_c);
    printf("  Assembly      : %.8f seconds\n", time_asm);
        if (time_asm > 0.0) {
        double speedup = time_c / time_asm;
        printf("  Speedup (C/ASM): %.2fx faster\n", speedup);
    } else {
        printf("  Speedup (C/ASM): N/A (assembly time too fast to measure accurately)\n");
    }

    return 0;
}

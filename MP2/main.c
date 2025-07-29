#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define ITERATIONS 30
#define EPSILON 1e-6

extern void imgCvtGrayIntToFloat(int *intPixels, float *floatPixels, int height, int width);

void printArr(float *img, int height, int width){
	int i, j;

	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			printf("%.2f ", img[i * width + j]); 
		}
		printf("\n"); 
	}
}

void printIntImage(int *img, int height, int width) {
	int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%d ", *(img + i * width + j));
        }
        printf("\n");
    }
}

int main(){
	int height = 3;
	int width = 4;
	int imgPixels[3][4] = {
		{64,89,114,84},
		{140,166,191,84},
		{216,242,38,84}
	};
	float floatPixels[3][4] = {0}; 

	printf("Original Input Image:\n");
	printIntImage(&imgPixels[0][0], height, width);

	clock_t start, end;
	double cpu_time_used;

	start = clock();
        imgCvtGrayIntToFloat(&imgPixels[0][0], &floatPixels[0][0], height, width);
        end = clock();

	printf("\nPrinting the Converted Image:\n");
	printArr(&floatPixels[0][0], height, width);

	printf("\nExecution time: %f seconds\n", cpu_time_used);

	return 0;
}

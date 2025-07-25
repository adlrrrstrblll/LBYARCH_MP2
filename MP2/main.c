#include <stdio.h>

extern void imgCvtGrayIntToFloat(int *intPixels, float *floatPixels, int height, int width);

void printArr(float *img, int height, int width){
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			printf("%.2f ", img[i * width + j]); 
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

	imgCvtGrayIntToFloat(&imgPixels[0][0], &floatPixels[0][0], height, width);

	printf("Printing the Converted Image:\n");
	printArr(&floatPixels[0][0], height, width);

	return 0;
}

//Rizea Adelina-Maria 314CA
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
image grayscale(image imagine)
//functia calculeaza noile valori ale pixelilor dupa formula
//si le pune in matrice
{
	int red, green, blue;
	if (imagine.type[1] == '5' || imagine.type[1] == '2') {
		printf("Grayscale filter not available\n");
		return imagine;
	}
	printf("Grayscale filter applied\n");
	for (int i = imagine.selectedy1; i < imagine.selectedy2; i++) {
		int n = imagine.selectedx1 * 3;
		int m = 3 * imagine.selectedx2;
		for (int j = n; j < m; j += 3) {
			red = (int)imagine.img[i][j];
			green = (int)imagine.img[i][j + 1];
			blue = (int)imagine.img[i][j + 2];
			double gray = (double)(red + green + blue) / 3.0;
			int aux = (int)gray;
			if (gray - aux > 0.5)
				gray = aux + 1;
			else
				gray = aux;
			imagine.img[i][j] = (unsigned char)gray;
			imagine.img[i][j + 1] = (unsigned char)gray;
			imagine.img[i][j + 2] = (unsigned char)gray;
			}
		}
	return imagine;
}

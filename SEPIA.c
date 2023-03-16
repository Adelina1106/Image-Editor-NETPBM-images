//Rizea Adelina-Maria 314CA
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
image sepia(image imagine)
{
	double red, green, blue;
	if (imagine.type[1] == '5' || imagine.type[1] == '2') {
		printf("Sepia filter not available\n");
		return imagine;
	}
	printf("Sepia filter applied\n");
	for (int i = imagine.selectedy1; i < imagine.selectedy2; i++) {
		int n = imagine.selectedx1 * 3;
		int m = 3 * imagine.selectedx2;
		for (int j = n; j < m; j += 3) {
			double color1, color2, color3;
			color1 = 0.393 * (int)imagine.img[i][j];
			color2 = 0.769 * (int)imagine.img[i][j + 1];
			color3 = 0.189 * (int)imagine.img[i][j + 2];
			red = color1 + color2 + color3;
			color1 = 0.349 * (int)imagine.img[i][j];
			color2 = 0.686 * (int)(int)imagine.img[i][j + 1];
			color3 = 0.168 * (int)imagine.img[i][j + 2];
			green = color1 + color2 + color3;
			color1 = 0.272 * (int)imagine.img[i][j];
			color2 = 0.534 * (int)(int)imagine.img[i][j + 1];
			color3 = 0.131 * (int)imagine.img[i][j + 2];
			blue = color1 + color2 + color3;
			//calculez noile valori ale pixelilor
			int aux = (int)red;
			if (red - aux > 0.5)
				red = aux + 1;
			else
				red = aux;
			if (red > 255)
				red = 255;
			aux = (int)green;
			if (green - aux > 0.5)
				green = aux + 1;
			else
				green = aux;
			if (green > 255)
				green = 255;
			aux = (int)blue;
			if (blue - aux > 0.5)
				blue = aux + 1;
			else
				blue = aux;
			if (blue > 255)
				blue = 255;
			imagine.img[i][j] = (unsigned char)red;
			imagine.img[i][j + 1] = (unsigned char)green;
			imagine.img[i][j + 2] = (unsigned char)blue;
			}
		}
		//verific daca noile valori depajesc valoarea maxima si rotunjesc
	return imagine;
}

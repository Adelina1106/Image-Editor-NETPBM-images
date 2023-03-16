//Rizea Adelina-Maria 314CA
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char **loadp2(FILE *filename, int x, int y)
//functie pentru alocarea memoriei necesare pentru o imagine de tip P2
{
	unsigned char **image;
	int aux;
	image = (unsigned char **)malloc(y * sizeof(unsigned char *));
	if (!image) {
		fprintf(stderr, "Problema alocare dinamica");
		exit(-1);
	}
	for (int i = 0; i < y; i++) {
		image[i] = (unsigned char *)malloc(x * sizeof(unsigned char));
		if (!image[i]) {
			free(image);
			fprintf(stderr, "Problema alocare dinamica");
			exit(-1);
		}
		for (int j = 0; j < x; j++) {
			fscanf(filename, "%d ", &aux);
			image[i][j] = (unsigned char)aux;
		}
		fscanf(filename, "\n");
	}
	//citesc pixelii imaginii si ii pun in matrice
	return image;
}

unsigned char **loadp3(FILE *filename, int x, int y)
//functie pentru alocarea memoriei necesare pentru o imagine de tip P3
{
	unsigned char **image = NULL;
	int red, green, blue;
	image = (unsigned char **)malloc(y * sizeof(unsigned char *));
	if (!image) {
		fprintf(stderr, "Problema alocare dinamica");
		exit(-1);
	}
	for (int i = 0; i < y; i++) {
		image[i] = malloc(3 * x * sizeof(unsigned char));
		if (!image[i]) {
			free(image);
			fprintf(stderr, "Problema alocare dinamica");
			exit(-1);
		}
		for (int j = 0; j < 3 * x; j += 3) {
			{
				fscanf(filename, "%d %d %d ", &red, &green, &blue);
				image[i][j] = (unsigned char)red;
				image[i][j + 1] = (unsigned char)green;
				image[i][j + 2] = (unsigned char)blue;
			}
		} //citesc text pixelii imaginii si ii pun in matrice, retinand
			//cele 3 culori(rosu, verde, albastru) pe cate o coloana
	}
	return image;
}

unsigned char **loadp5(FILE *filename, int x, int y)
//functie pentru alocarea memoriei necesare pentru o imagine de tip P5
{
	unsigned char **image = NULL;
	image = (unsigned char **)malloc(y * sizeof(int *));
	if (!image) {
		fprintf(stderr, "Problema alocare dinamica");
		exit(-1);
	}
	for (int i = 0; i < y; i++) {
		image[i] = malloc(x * sizeof(unsigned char));
		if (!image[i]) {
			free(image);
			fprintf(stderr, "Problema alocare dinamica");
			exit(-1);
		}
		for (int j = 0; j < x; j++)
			fread(&image[i][j], sizeof(unsigned char), 1, filename);
	}
	return image;
}

unsigned char **loadp6(FILE *filename, int x, int y)
//functie pentru alocarea memoriei necesare pentru o imagine de tip P6
{
	unsigned char **image = NULL;

	image = (unsigned char **)malloc(y * sizeof(unsigned char *));
	if (!image) {
		fprintf(stderr, "Problema alocare dinamica");
		exit(-1);
	}
	for (int i = 0; i < y; i++) {
		image[i] = malloc(3 * x * sizeof(unsigned char));
		if (!image[i]) {
			free(image);
			fprintf(stderr, "Problema alocare dinamica");
			exit(-1);
		}
		for (int j = 0; j < 3 * x; j += 3) {
			fread(&image[i][j], sizeof(unsigned char), 1, filename);
			fread(&image[i][j + 1], sizeof(unsigned char), 1, filename);
			fread(&image[i][j + 2], sizeof(unsigned char), 1, filename);
			}
			//citesc binar pixelii imaginii si ii pun in matrice, retinand
			//cele 3 culori(rosu, verde, albastru) pe cate o coloana
	}
	return image;
}

FILE *open(char *file, char *mode)
//functie ce returneaza fisierul dat deschis
{
	FILE *in = fopen(file, mode);
	if (!in)
		printf("Failed to load %s\n", file);
	else
		printf("Loaded %s\n", file);
	return in;
}

void comment(FILE *input)
{
	char c = fgetc(input);
	while (c == '#') {
		char line[512];
		fgets(line, sizeof(line), input);
		c = fgetc(input);
	}

	fseek(input, -1, SEEK_CUR);
}

image load(char *filename)
//citesc din fisierul deschis tipul, dimensiunile si valoarea maxima
//a unei imagini, retinandu-le intr-o structura ce retine informatii
//despre imagini
{
	char type[3];
	image imagine = {0};
	int x, y;
	int max_value;
	FILE *input = open(filename, "rb");

	if (!input) {
		imagine.load = 0;
		return imagine;
	}
	imagine.load = 1;
	fread(&type, sizeof(unsigned char), 2, input);
	if (type[1] == '6') {
		imagine.type[0] = 'P';
		imagine.type[1] = '6';
		comment(input);
		fscanf(input, "%d %d\n", &x, &y);
		comment(input);
		fscanf(input, "%d\n", &max_value);
		imagine.x = x;
		imagine.y = y;
		imagine.selectedx2 = imagine.x;
		imagine.selectedy2 = imagine.y;
		imagine.selectedx1 = 0;
		imagine.selectedy1 = 0;
		imagine.img = loadp6(input, imagine.x, imagine.y);
	} else if (type[1] == '5') {
		imagine.type[0] = 'P';
		imagine.type[1] = '5';
		comment(input);
		fscanf(input, "%d %d\n", &imagine.x, &imagine.y);
		comment(input);
		fscanf(input, "%d\n", &max_value);
		imagine.selectedx2 = imagine.x;
		imagine.selectedy2 = imagine.y;
		imagine.selectedx1 = 0;
		imagine.selectedy1 = 0;
		imagine.img = loadp5(input, imagine.x, imagine.y);
	} else if (type[1] == '3') {
		fclose(input);
		input = fopen(filename, "rt");
		fgets(type, sizeof(type), input);
		imagine.type[0] = 'P';
		imagine.type[1] = '3';
		comment(input);
		fscanf(input, "%d %d\n", &imagine.x, &imagine.y);
		imagine.selectedx2 = imagine.x;
		imagine.selectedy2 = imagine.y;
		imagine.selectedx1 = 0;
		imagine.selectedy1 = 0;
		fscanf(input, "%d\n", &max_value);
		imagine.img = loadp3(input, imagine.x, imagine.y);
	} else if (type[1] == '2') {
		fclose(input);
		input = fopen(filename, "rt");
		fgets(type, sizeof(type), input);
		imagine.type[0] = 'P';
		imagine.type[1] = '2';
		comment(input);
		fscanf(input, "%d %d\n", &imagine.x, &imagine.y);
		imagine.selectedx2 = imagine.x;
		imagine.selectedy2 = imagine.y;
		imagine.selectedx1 = 0;
		imagine.selectedy1 = 0;
		comment(input);
		fscanf(input, "%d\n", &max_value);
		imagine.img = loadp2(input, imagine.x, imagine.y);
	}
	fclose(input);
	return imagine;
}

//Rizea Adelina-Maria 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

unsigned char **alloc_matrix(unsigned char **crop, int n, int m)
{
	//functie pentru alocarea dinamica a unei matrici
	crop = (unsigned char **)malloc(n * sizeof(unsigned char *));
	if (!crop) {
		fprintf(stderr, "Problema alocare dinamica");
		exit(-1);
	}
	for (int i = 0; i < n; i++) {
		crop[i] = (unsigned char *)malloc(m * sizeof(unsigned char));
		if (!crop[i]) {
			free(crop);
			fprintf(stderr, "Problema alocare dinamica");
			exit(-1);
		}
	}
	return crop;
}

void free_matrix(unsigned char **rotate, int n)
{
	for (int i = 0; i < n; i++)
		free(rotate[i]);
	free(rotate);
}

int main(void)
{
	char line[512], line1[512] = "null";
	int ok = 0;
	char *command = "null";
	FILE *filename = NULL;
	image imagine = {0};
	unsigned char **rotate = NULL, **crop = NULL;
	imagine.load = 0;
	while (ok == 0) {
		fgets(line, sizeof(line), stdin);
		for (int i = 0; i < (int)strlen(line); i++)
			line1[i] = line[i];
		command = strtok(line, " ");
		if (strcmp(command, "EXIT") == 0 || strcmp(command, "EXIT\n") == 0) {
			if (imagine.load == 1) {
				if (filename)
					fclose(filename);
				if (imagine.load == 1) {
					free_matrix(imagine.img, imagine.y);
					imagine.load = 0;
				}
		//la intalnirea comenzii EXIT verificam daca a fost vreo imagine
		//incarcata pentru a elibera memoria alocata
				return 0;
			}
			printf("No image loaded\n");
			return 0;
		}
		if ((imagine.load == 1 || strcmp(command, "LOAD") == 0)) {
			if (strcmp(command, "LOAD") == 0) {
				command = strtok(NULL, " ");
				command[strlen(command) - 1] = '\0';
				if (imagine.load == 1)
					free_matrix(imagine.img, imagine.y);
				imagine = load(command);
			} else if (strcmp(command, "SELECT") == 0) {
				imagine = SELECT_commands(imagine, line1, command);
			} else if (strcmp(command, "ROTATE") == 0) {
				imagine = ROTATE_commands(imagine, command, rotate);
				if (rotate != 0)
					free_matrix(rotate, imagine.x);
			} else if (strcmp(command, "GRAYSCALE\n") == 0) {
				imagine = grayscale(imagine);
			} else if (strcmp(command, "SEPIA\n") == 0) {
				imagine = sepia(imagine);
			} else if (strcmp(command, "SAVE") == 0) {
				SAVE_commands(command, imagine);
			} else if (strcmp(command, "CROP\n") == 0) {
				int n = imagine.selectedy2 - imagine.selectedy1;
				int m = imagine.selectedx2 - imagine.selectedx1;
				printf("Image cropped\n");
				if (imagine.type[1] == '2' || imagine.type[1] == '5') {
					crop = alloc_matrix(crop, n, m);
					crop_ascii(&imagine, crop);
				} else {
					crop = alloc_matrix(crop, n, 3 * m);
					crop_P3_P6(&imagine, crop);
				}
				if (crop != 0)
					free_matrix(crop, n);
			} else {
				printf("Invalid command\n");
			}
		} else {
			printf("No image loaded\n");
		}
	}
	return 0;
}

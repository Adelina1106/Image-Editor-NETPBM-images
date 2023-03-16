//Rizea Adelina-Maria 314CA
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save(image *imagine, char *filename)
//functie pentru scrierea binara a matricii imaginii incarcate
{
	FILE *nou = fopen(filename, "wb");
	if (imagine->type[1] == '3' || imagine->type[1] == '6') {
		fprintf(nou, "P6\n");
		fprintf(nou, "%d ", imagine->x);
		fprintf(nou, "%d\n", imagine->y);
		fprintf(nou, "255\n");
		for (int i = 0; i < imagine->y; i++)
			for (int j = 0; j < 3 * imagine->x; j += 3) {
				fwrite(&imagine->img[i][j], sizeof(unsigned char), 1, nou);
				fwrite(&imagine->img[i][j + 1], sizeof(unsigned char), 1, nou);
				fwrite(&imagine->img[i][j + 2], sizeof(unsigned char), 1, nou);
			}
	} else if (imagine->type[1] == '5' || imagine->type[1] == '2') {
		fprintf(nou, "P5\n");
		fprintf(nou, "%d ", imagine->x);
		fprintf(nou, "%d\n", imagine->y);
		fprintf(nou, "255\n");
		for (int i = 0; i < imagine->y; i++)
			for (int j = 0; j < imagine->x; j++)
				fwrite(&imagine->img[i][j], sizeof(unsigned char), 1, nou);
	}
	fclose(nou);
}

void save_ascii(image *imagine, char *filename)
//functie pentru scrierea text a matricii imaginii incarcate
{
	FILE *nou = fopen(filename, "wt");
	if (imagine->type[1] == '3' || imagine->type[1] == '6') {
		fprintf(nou, "P3\n");
		fprintf(nou, "%d ", imagine->x);
		fprintf(nou, "%d\n", imagine->y);
		fprintf(nou, "255\n");
		for (int i = 0; i < imagine->y; i++) {
			for (int j = 0; j < 3 * imagine->x; j += 3) {
				fprintf(nou, "%d ", imagine->img[i][j]);
				fprintf(nou, "%d ", (int)imagine->img[i][j + 1]);
				if (j + 2 == imagine->x * 3 - 1)
					fprintf(nou, "%d\n", (int)imagine->img[i][j + 2]);
				else
					fprintf(nou, "%d ", (int)imagine->img[i][j + 2]);
			}
		}
	} else if (imagine->type[1] == '5' || imagine->type[1] == '2') {
		fprintf(nou, "P2\n");
		fprintf(nou, "%d ", imagine->x);
		fprintf(nou, "%d\n", imagine->y);
		fprintf(nou, "255\n");
		for (int i = 0; i < imagine->y; i++)
			for (int j = 0; j < imagine->x; j++) {
				if (j == imagine->x - 1)
					fprintf(nou, "%d\n", (int)imagine->img[i][j]);
				else
					fprintf(nou, "%d ", (int)imagine->img[i][j]);
			}
	}

	fclose(nou);
}

void SAVE_commands(char *command, image imagine)
//functie pentru interpretarea comenzii date
{
	command = strtok(NULL, " ");
	if (command[strlen(command) - 1] == '\n') {
		command[strlen(command) - 1] = '\0';
		printf("Saved %s\n", command);
		save(&imagine, command);
	} else {
		char *command1 = command;
		command = strtok(NULL, " ");
		if (strcmp(command, "ascii\n") == 0) {
			printf("Saved %s\n", command1);
			save_ascii(&imagine, command1);
		} else {
			if (command1[strlen(command1) - 2] == 'm')
				command1[strlen(command1) - 1] = '\0';
			printf("Saved %s\n", command1);
			save(&imagine, command1);
		}
	}
}

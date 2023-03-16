//Rizea Adelina-Maria 314CA
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

image SELECT(image imagine, char *line)
//functie pentru retinerea valorilor selectate
{
	int count = 0;
	for (int i = 0; line[i] != '\n'; i++)
		if (line[i] == ' ')
			count++;
	if (count != 4) {
		printf("Invalid command\n");
		return imagine;
	}
	int aux, x2, y1, y2, x1;
	char *command = NULL;
	command = strtok(line, " ");
	command = strtok(NULL, " ");
	x1 = atoi(command);
	command = strtok(NULL, " ");
	y1 = atoi(command);
	command = strtok(NULL, " ");
	x2 = atoi(command);
	command = strtok(NULL, " ");
	command[strlen(command) - 1] = '\0';

	y2 = atoi(command);
	if (y2 == 0 && (command[0] < '0' || command[0] > '9')) {
		printf("Invalid command\n");
		return imagine;
	}
	if (x1 > x2) {
		aux = x1;
		x1 = x2;
		x2 = aux;
	}
	if (y1 > y2) {
		aux = y1;
		y1 = y2;
		y2 = aux;
	}
	int relatie1 = 0, relatie2 = 0;
	if (x1 < 0 || x1 > imagine.x || x2 < 0 || x2 > imagine.x || y1 < 0)
		relatie1 = 1;
	if (y1 > imagine.y || y2 < 0 || y2 > imagine.y || x1 == x2 || y1 == y2)
		relatie2 = 1;
	if (relatie1 == 1 || relatie2 == 1) {
		printf("Invalid set of coordinates\n");
		return imagine;
	}
	//verific daca valorile date sunt valide
	imagine.selectedx1 = x1;
	imagine.selectedy1 = y1;
	imagine.selectedx2 = x2;
	imagine.selectedy2 = y2;
	printf("Selected %d %d ", imagine.selectedx1, imagine.selectedy1);
	printf("%d %d\n", imagine.selectedx2, imagine.selectedy2);
	return imagine;
}

image SELECT_commands(image imagine, char *line1, char *command)
{
	command = strtok(NULL, " ");
	command[strlen(command) - 1] = '\0';
	if (command[0] == 'A' && command[1] == 'L' && command[1] == 'L') {
		imagine.selectedx1 = 0;
		imagine.selectedy1 = 0;
		imagine.selectedx2 = imagine.x;
		imagine.selectedy2 = imagine.y;
		printf("Selected ALL\n");
	//verific daca trebuie selectata toata imaginea
	} else {
		imagine = SELECT(imagine, line1);
	}
	return imagine;
}

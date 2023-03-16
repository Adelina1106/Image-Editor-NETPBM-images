//Rizea Adelina-Maria 314CA
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crop_ascii(image *imagine, unsigned char **crop)
//functie pentru decuparea imaginilor P2 sau P5
{
	int relatie1 = 0, relatie2 = 0;
	if (imagine->selectedx2 - imagine->selectedx1 == imagine->x)
		relatie1 = 1;
	if (imagine->selectedy2 - imagine->selectedy1 == imagine->y)
		relatie2 = 1;
	if (relatie1 && relatie2) {
		imagine->selectedx1 = 0;
		imagine->selectedy1 = 0;
		imagine->selectedx2 = imagine->x;
		imagine->selectedy2 = imagine->y;
	//verific daca dimensiunile date reprezinta intreaga matrice,
	//caz in care modific doar valorile selectate
	} else {
		int m = imagine->selectedx2 - imagine->selectedx1;
		int n = imagine->selectedy2 - imagine->selectedy1;
		imagine->x = m;
		int auxy = imagine->y;
		imagine->y = n;
		int linie, coloana;
		linie = 0;
		coloana = 0;
		for (int i = imagine->selectedy1; i < imagine->selectedy2; i++) {
			coloana = 0;
			for (int j = imagine->selectedx1; j < imagine->selectedx2; j++) {
				crop[linie][coloana] = imagine->img[i][j];
				coloana++;
			}
			linie++;
		}
		//copiez zona ce trebuie decupata intr-o noua matrice
		if (imagine->img) {
			for (int i = 0; i < auxy; i++)
				free(imagine->img[i]);
			free(imagine->img);
		}
		imagine->img = (unsigned char **)malloc(n * sizeof(unsigned char *));
		for (int i = 0; i < n; i++)
			imagine->img[i] = malloc(m * sizeof(unsigned char));
		//eliberez memoria alocata pentru matricea imaginii si aloc pentru
		//noile dimensiuni
		linie = 0;
		for (int i = 0; i < n; i++) {
			coloana = 0;
			for (int j = 0; j < m; j++) {
				imagine->img[i][j] = crop[i][j];
				coloana++;
			}
			linie++;
		}
		imagine->selectedx1 = 0;
		imagine->selectedy1 = 0;
		imagine->selectedx2 = imagine->x;
		imagine->selectedy2 = imagine->y;
	}
}

void crop_P3_P6(image *imagine, unsigned char **crop)
//functie pentru decuparea imaginilor P3 sau P6
{
	int n, m;

	m = imagine->selectedx2 - imagine->selectedx1;
	n = imagine->selectedy2 - imagine->selectedy1;
	imagine->x = m;
	int auxy = imagine->y;
	imagine->y = n;
	int linie, coloana;
	linie = 0;
	coloana = 0;
	for (int i = imagine->selectedy1; i < imagine->selectedy2; i++) {
		coloana = 0;
		int lin = 3 * imagine->selectedx1;
		int col = 3 * imagine->selectedx2;
		for (int j = lin; j < col; j += 3) {
			crop[linie][coloana] = imagine->img[i][j];
			crop[linie][coloana + 1] = imagine->img[i][j + 1];
			crop[linie][coloana + 2] = imagine->img[i][j + 2];
			coloana += 3;
		}
		linie++;
	}
	if (imagine->img) {
		for (int i = 0; i < auxy; i++)
			free(imagine->img[i]);
		free(imagine->img);
	}
	imagine->img = (unsigned char **)malloc(n * sizeof(unsigned char *));
	for (int i = 0; i < n; i++)
		imagine->img[i] = malloc(3 * m * sizeof(unsigned char));
	//eliberez memoria alocata pentru matricea imaginii si aloc pentru
	//noile dimensiuni, avand 3 coloane( corespunzatoare culorilor
	//rosu, verde, albastru) pentru fiecare pixel
	linie = 0;
	for (int i = 0; i < n; i++) {
		coloana = 0;
		for (int j = 0; j < 3 * m; j += 3) {
			imagine->img[i][j] = crop[i][j];
			imagine->img[i][j + 1] = crop[i][j + 1];
			imagine->img[i][j + 2] = crop[i][j + 2];
			coloana += 3;
		}
		linie++;
	}
	imagine->selectedx1 = 0;
	imagine->selectedy1 = 0;
	imagine->selectedx2 = imagine->x;
	imagine->selectedy2 = imagine->y;
}

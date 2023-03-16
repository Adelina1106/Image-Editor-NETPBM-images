//Rizea Adelina-Maria 314CA
#include "utils.h"

image ROTATE(image imagine)
{
//functie pentru rotirea unei zone selectate dintr-o imagine P2 sau P5
	int n;
	n = imagine.selectedx2 - imagine.selectedx1;
	int linie, coloana;
	unsigned char **rotate = NULL;

	rotate = (unsigned char **)malloc(n * sizeof(unsigned char *));
	if (!rotate) {
		fprintf(stderr, "Problema alocare dinamica");
		exit(-1);
	}
	for (int i = 0; i < n; i++) {
		rotate[i] = malloc(n * sizeof(unsigned char *));
		if (!rotate[i]) {
			free(rotate);
			fprintf(stderr, "Problema alocare dinamica");
			exit(-1);
		}
	}
	linie = 0;
	coloana = 0;
	for (int i = imagine.selectedy1; i < imagine.selectedy2; i++) {
		coloana = 0;
		for (int j = imagine.selectedx1; j < imagine.selectedx2; j++) {
			rotate[linie][coloana] = imagine.img[i][j];
			coloana++;
		}
		linie++;
	}
	//copiez zona ce trebuie rotita in noua matrice alocata
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < (n + 1) / 2; j++) {
			unsigned char aux = rotate[i][j];

			rotate[i][j] = rotate[n - 1 - j][i];
			rotate[n - 1 - j][i] = rotate[n - 1 - i][n - 1 - j];
			rotate[n - 1 - i][n - 1 - j] = rotate[j][n - 1 - i];
			rotate[j][n - 1 - i] = aux;
		}
	//interschimb elementele pentru a obtine transpusa
	linie = 0;
	coloana = 0;
	for (int i = imagine.selectedy1; i < imagine.selectedy2; i++) {
		coloana = 0;
		for (int j = imagine.selectedx1; j < imagine.selectedx2; j++) {
			imagine.img[i][j] = rotate[linie][coloana];
			coloana++;
		}
		linie++;
	}
	for (int i = 0; i < n; i++)
		free(rotate[i]);
	free(rotate);
	//copiez noua matrice in zona corespunzatoare din vechea matrice
	//si eliberez memoria alocata
	return imagine;
}

image ROTATE_P3_P6(image imagine)
{
//functie pentru rotirea unei zone selectate dintr-o imagine P3 sau P6
	int n;
	n = imagine.selectedx2 - imagine.selectedx1;
	int linie, coloana;
	pixels **rotate = NULL;

	rotate = (pixels **)malloc(n * sizeof(pixels *));
	if (!rotate) {
		fprintf(stderr, "Problema alocare dinamica");
		exit(-1);
	}
	for (int i = 0; i < n; i++) {
		rotate[i] = malloc(n * sizeof(pixels *));
		if (!rotate[i]) {
			free(rotate);
			fprintf(stderr, "Problema alocare dinamica");
			exit(-1);
		}
	}
	linie = 0;
	coloana = 0;
	for (int i = imagine.selectedy1; i < imagine.selectedy2; i++) {
		coloana = 0;
		int j;
		for (j = imagine.selectedx1 * 3; j < 3 * imagine.selectedx2; j += 3) {
			rotate[linie][coloana].red = imagine.img[i][j];
			rotate[linie][coloana].green = imagine.img[i][j + 1];
			rotate[linie][coloana].blue = imagine.img[i][j + 2];
			coloana++;
		}
		linie++;
	}
	//aloc o noua matrice struct cu cate 3 culori pentru fiecare element
	// si copiez zona ce trebuie rotita in aceasta
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < (n + 1) / 2; j++) {
			unsigned char aux = rotate[i][j].red;

			rotate[i][j].red = rotate[n - 1 - j][i].red;
			rotate[n - 1 - j][i].red = rotate[n - 1 - i][n - 1 - j].red;
			rotate[n - 1 - i][n - 1 - j].red = rotate[j][n - 1 - i].red;
			rotate[j][n - 1 - i].red = aux;

			aux = rotate[i][j].green;

			rotate[i][j].green = rotate[n - 1 - j][i].green;
			rotate[n - 1 - j][i].green = rotate[n - 1 - i][n - 1 - j].green;
			rotate[n - 1 - i][n - 1 - j].green = rotate[j][n - 1 - i].green;
			rotate[j][n - 1 - i].green = aux;

			aux = rotate[i][j].blue;

			rotate[i][j].blue = rotate[n - 1 - j][i].blue;
			rotate[n - 1 - j][i].blue = rotate[n - 1 - i][n - 1 - j].blue;
			rotate[n - 1 - i][n - 1 - j].blue = rotate[j][n - 1 - i].blue;
			rotate[j][n - 1 - i].blue = aux;
		}
	/// interschimb valorile pentru a obtine matricea transpusa
	linie = 0;
	for (int i = imagine.selectedy1; i < imagine.selectedy2; i++) {
		coloana = 0;
		int n = imagine.selectedx1 * 3;
		int m = 3 * imagine.selectedx2;
		for (int j = n; j < m; j += 3) {
			imagine.img[i][j] = rotate[linie][coloana].red;
			imagine.img[i][j + 1] = rotate[linie][coloana].green;
			imagine.img[i][j + 2] = rotate[linie][coloana].blue;
			coloana++;
		}
		linie++;
	}
	for (int i = 0; i < n; i++)
		free(rotate[i]);
	free(rotate);
	//eliberez memoria alocata matricii folosite
	return imagine;
}

image ROTATE_ALL(image imagine, unsigned char **rotate)
//functie pentru rotirea unei intregi imagini de tip P2 sau P5
{
	int aux = imagine.y;
	imagine.y = imagine.x;
	imagine.x = aux;
	int linie, coloana;

	rotate = (unsigned char **)malloc(imagine.x * sizeof(unsigned char *));
	if (!rotate) {
		fprintf(stderr, "Problema alocare dinamica");
		exit(-1);
	}
	for (int i = 0; i < imagine.x; i++) {
		rotate[i] = (unsigned char *)malloc(imagine.y * sizeof(unsigned char));
		if (!rotate[i]) {
			free(rotate);
			fprintf(stderr, "Problema alocare dinamica");
			exit(-1);
		}
	}
	linie = 0;
	coloana = 0;
	for (int i = 0; i < imagine.x; i++) {
		coloana = 0;
		for (int j = 0; j < imagine.y; j++) {
			rotate[linie][coloana] = imagine.img[i][j];
			coloana++;
		}
		linie++;
	}
	for (int i = 0; i < imagine.x; i++)
		free(imagine.img[i]);
	free(imagine.img);
	imagine.img = (unsigned char **)malloc(imagine.y * sizeof(unsigned char *));
	for (int i = 0; i < imagine.y; i++)
		imagine.img[i] = malloc(imagine.x * sizeof(unsigned char));
	//aloc o noua matrice si eliberez memoria alocata pentru matricea imaginii
	//pentru a o aloca cu noile dimensiuni
	linie = imagine.y - 1;
	coloana = 0;
	for (int i = 0; i < imagine.y; i++) {
		linie = imagine.x - 1;
		for (int j = 0; j < imagine.x; j++) {
			imagine.img[i][j] = rotate[linie][coloana];
			linie--;
		}
		coloana++;
	}
	//iau elementele din noua matrice astfel incat sa obtin transpusa
	imagine.selectedx1 = 0;
	imagine.selectedy1 = 0;
	imagine.selectedy2 = imagine.y;
	imagine.selectedx2 = imagine.x;
	for (int i = 0; i < imagine.x; i++)
		free(rotate[i]);
	free(rotate);
	return imagine;
}

image ROTATE_ALL_P3_P6(image imagine)
//functie pentru rotirea unei intregi imagini de tip P6 sau P3
{
	int aux = imagine.y;
	imagine.y = imagine.x;
	imagine.x = aux;
	int linie, coloana;
	unsigned char **rotate = NULL;

	rotate = (unsigned char **)malloc(imagine.x * sizeof(unsigned char *));
	if (!rotate) {
		fprintf(stderr, "Problema alocare dinamica");
		exit(-1);
	}
	for (int i = 0; i < imagine.x; i++) {
		rotate[i] = malloc(3 * imagine.y * sizeof(unsigned char *));
		if (!rotate[i]) {
			free(rotate);
			fprintf(stderr, "Problema alocare dinamica");
			exit(-1);
		}
	}
	linie = 0;
	coloana = 0;
	for (int i = 0; i < imagine.x; i++) {
		coloana = 0;
		for (int j = 0; j < 3 * imagine.y; j += 3) {
			rotate[linie][coloana] = imagine.img[i][j];
			rotate[linie][coloana + 1] = imagine.img[i][j + 1];
			rotate[linie][coloana + 2] = imagine.img[i][j + 2];
			coloana += 3;
		}
		linie++;
	}
	//aloc o noua matrice in care copiez elementele si eliberez
	 //memoria alocata pentru matricea imaginii pentru a o aloca cu
	//noile dimensiuni
	for (int i = 0; i < imagine.x; i++)
		free(imagine.img[i]);
	free(imagine.img);
	imagine.img = (unsigned char **)malloc(imagine.y * sizeof(unsigned char *));
	for (int i = 0; i < imagine.y; i++)
		imagine.img[i] = malloc(3 * imagine.x * sizeof(unsigned char));

	linie = imagine.y - 1;
	coloana = 0;
	for (int i = 0; i < imagine.y; i++) {
		linie = imagine.x - 1;
		for (int j = 0; j < 3 * imagine.x; j += 3) {
			imagine.img[i][j] = rotate[linie][coloana];
			imagine.img[i][j + 1] = rotate[linie][coloana + 1];
			imagine.img[i][j + 2] = rotate[linie][coloana + 2];
			linie--;
		}
		coloana += 3;
	}
	imagine.selectedx1 = 0;
	imagine.selectedy1 = 0;
	imagine.selectedy2 = imagine.y;
	imagine.selectedx2 = imagine.x;
	for (int i = 0; i < imagine.x; i++)
		free(rotate[i]);
	free(rotate);
	return imagine;
	//parcurg matricea astfel incat sa obtin transpusa, avand
	//pentru fiecare element cate o culoare pe o coloana
}

image ROTATE_commands(image imagine, char *command, unsigned char **rotate)
//verific caul in care ma aflu rotind imaginea de un numar de ori dat de grad
{
	command = strtok(NULL, " ");
	int grad = atoi(command), ok1 = 0;
	if (grad != 180 && grad != -180 && grad != 90 && grad != -90 && grad != 270)
		ok1 = 1;
	if (ok1 == 1 && grad != -270 && grad != 0 && grad != 360 && grad != -360) {
		printf("Unsupported rotation angle\n");
		return imagine;
	}
	int x_nou = imagine.selectedx2 - imagine.selectedx1;
	int y_nou = imagine.selectedy2 - imagine.selectedy1;
	if (x_nou == y_nou) {
		if (grad == 90 || grad == -270) {
			printf("Rotated %d\n", grad);
			if (imagine.type[1] == '2' || imagine.type[1] == '5')
				imagine = ROTATE(imagine);
			else
				imagine = ROTATE_P3_P6(imagine);
		} else if (grad == 180 || grad == -180) {
			printf("Rotated %d\n", grad);
			if (imagine.type[1] == '2' || imagine.type[1] == '5') {
				imagine = ROTATE(imagine);
				imagine = ROTATE(imagine);
			} else {
				imagine = ROTATE_P3_P6(imagine);
				imagine = ROTATE_P3_P6(imagine);
		}
		} else if (grad == -90 || grad == 270) {
			printf("Rotated %d\n", grad);
			if (imagine.type[1] == '2' || imagine.type[1] == '5') {
				imagine = ROTATE(imagine);
				imagine = ROTATE(imagine);
				imagine = ROTATE(imagine);
			} else {
				imagine = ROTATE_P3_P6(imagine);
				imagine = ROTATE_P3_P6(imagine);
				imagine = ROTATE_P3_P6(imagine);
			}
		} else if (grad == 0 || grad == 360 || grad == -360) {
			printf("Rotated %d\n", grad);
			}
	} else if (x_nou == imagine.x && y_nou == imagine.y) {
		if (grad == 90 || grad == -270) {
			printf("Rotated %d\n", grad);
		if (imagine.type[1] == '2' || imagine.type[1] == '5')
			imagine = ROTATE_ALL(imagine, rotate);
		else
			imagine = ROTATE_ALL_P3_P6(imagine);
	}
		if (grad == 180 || grad == -180) {
			printf("Rotated %d\n", grad);
			if (imagine.type[1] == '2' || imagine.type[1] == '5') {
				imagine = ROTATE_ALL(imagine, rotate);
				imagine = ROTATE_ALL(imagine, rotate);
			} else {
				imagine = ROTATE_ALL_P3_P6(imagine);
				imagine = ROTATE_ALL_P3_P6(imagine);
			}
		}
		if (grad == -90 || grad == 270) {
			printf("Rotated %d\n", grad);
			if (imagine.type[1] == '2' || imagine.type[1] == '5') {
				imagine = ROTATE_ALL(imagine, rotate);
				imagine = ROTATE_ALL(imagine, rotate);
				imagine = ROTATE_ALL(imagine, rotate);
			} else {
				imagine = ROTATE_ALL_P3_P6(imagine);
				imagine = ROTATE_ALL_P3_P6(imagine);
				imagine = ROTATE_ALL_P3_P6(imagine);
			}
		} else if (grad == 0 || grad == 360 || grad == -360) {
			printf("Rotated %d\n", grad);
		}
	} else {
		printf("The selection must be square\n");
	}
	return imagine;
}

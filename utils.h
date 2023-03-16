
#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//strcuctura care retine informatiile despre imaginea incarcata
typedef struct{
	int x, y;
	unsigned char **img;
	int selectedx1, selectedx2, selectedy1, selectedy2;
	char type[3];
	int load;

} image;

typedef struct{
	unsigned char red, green, blue;
} pixels;

unsigned char **alloc_matrix(unsigned char **crop, int n, int m);
void comment(FILE *input);
void free_matrix(unsigned char **rotate, int n);
unsigned char **loadp2(FILE *filename, int x, int y);
unsigned char **loadp3(FILE *filename, int x, int y);
unsigned char **loadp5(FILE *filename, int x, int y);
unsigned char **loadp6(FILE *filename, int x, int y);
FILE *open(char *file, char *mode);
image load(char *filename);
image SELECT(image imagine, char *line);
void save(image *imagine, char *filename);
void save_ascii(image *imagine, char *filename);
image ROTATE(image imagine);
image ROTATE_P3_P6(image imagine);
image ROTATE_ALL(image imagine, unsigned char **rotate);
image ROTATE_ALL_P3_P6(image imagine);
image grayscale(image imagine);
void crop_ascii(image *imagine, unsigned char **crop);
void crop_P3_P6(image *imagine, unsigned char **crop);
image sepia(image imagine);
image ROTATE_commands(image imagine, char *command, unsigned char **rotate);
void SAVE_commands(char *command, image imagine);
image SELECT_commands(image imagine, char *line1, char *command);

#endif

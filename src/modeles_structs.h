#ifndef MODELES_STRUCTS_H
#define MODELES_STRUCTS_H
#include "3d.h"

typedef struct {	// utilis� dans les fichiers de data
	int p[3];	// les trois num�ros de point dans la liste de point de l'objet
	pixel color;
	double lissratio;	// pour le lissage de cette face.
} facelight;

#endif

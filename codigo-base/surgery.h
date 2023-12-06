#include <allegro5/allegro.h>

struct surgeryFirst {
	ALLEGRO_BITMAP* bitmap;
	float x;
	float y;
	float buffer;
	bool ativo;
} vectors[8], congrats, dnaGameover;

struct box {
	int x;
	int y;
	double a;
	double buffer;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_BITMAP* frame1;
} doctor, dna, instru;
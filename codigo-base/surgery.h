#include <allegro5/allegro.h>

struct surgeryFirst {
	ALLEGRO_BITMAP* bitmap;
	float x;
	float y;
	float buffer;
	bool ativo;
} vectors[8], dnaGameover;

struct box {
	int x;
	int y;
	double buffer;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_BITMAP* frame1;
	ALLEGRO_BITMAP* frame2;
	ALLEGRO_BITMAP* frame3;
} doctor, dna;
#include <allegro5/allegro.h>

struct surgeryFirst {
	ALLEGRO_BITMAP* bitmap;
	int x;
	int y;
} syringe, syringeJuice;
struct surgerySecond {
	ALLEGRO_BITMAP* bitmapIdle;
	ALLEGRO_BITMAP* bitmapIngame;
	ALLEGRO_BITMAP* bitmapEnd;
	int x;
	int y;
}bloodBag;
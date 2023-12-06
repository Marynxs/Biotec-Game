#include <allegro5/allegro.h>

struct qwer {
	ALLEGRO_BITMAP* idle;
	ALLEGRO_BITMAP* pressed;
	int x;
	int y;
	int points;
	double buffer;
	bool screen;
	bool key;
} buttons[4];


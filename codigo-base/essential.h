#include <allegro5/allegro.h>

struct menuItem {
	float x;
	float y;
	float a;
	ALLEGRO_BITMAP* bitmap;
	float buffer;
} iconGame, startButton, menuBg, points[3];

struct pngTransparent {
	ALLEGRO_BITMAP* bitmap;
} blackpng, yellowpng, pinkpng, bluepng, greenpng;

struct mouseCursor{
	int x;
	int y;
	ALLEGRO_BITMAP* idle;
	ALLEGRO_BITMAP* clicked;
} mouse, surgeryMouse;

struct textBox {
	int x;
	int y;
	int buffer;
	char text[100];
	ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* textBitmap;
	ALLEGRO_BITMAP* bitmap;
}textBox;
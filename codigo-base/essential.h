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

void insertionSort(int arr[], int n) {
	int i, chave, j; //O(1)

	for (i = 1; i < n; i++) { //O(N)
		chave = arr[i]; //O(N)
		j = i - 1; //O(N)

		while (j >= 0 && arr[j] < chave) { //O(N)²
			arr[j + 1] = arr[j]; //O(N)²
			j = j - 1; //O(N)²
		}
		arr[j + 1] = chave; //O(N)²
	}
}